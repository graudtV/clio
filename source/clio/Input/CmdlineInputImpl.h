#pragma once

#include "default_parser.h"
#include "Parser/ParserError.h"
#include "platform.h"
#include <cassert>

namespace clio {

struct no_verifier_t {} no_verifier;

template <class T>
constexpr void assert_default_parser_exists() {
	static_assert(default_parser_exists<T>::value,
		"Cannot parse selected value type because no default parser exists "
		"Please use other type or specify parser manually");	
}

inline CmdlineInput&
CmdlineInput::set_attempts(unsigned attempts /* != 0 */) {
	assert(attempts > 0 && "number of attempts must be > 0");
	m_nattempts = attempts;
	return *this;
}

inline CmdlineInput&
CmdlineInput::exit_on_eof(bool exit /* = true */) {
	m_exit_on_eof = exit;
	return *this;
}

inline CmdlineInput&
CmdlineInput::hide_input_symbols(bool enable /* = true */) {
	m_hide_input_symbols = enable;
	return *this;
}

template <class T>
T CmdlineInput::get_value(std::string_view prompt) {
	assert_default_parser_exists<T>();
	return get_value_impl<T>(prompt, default_parser_t<T>{}, no_verifier,
		default_parser<T>::error_hint(), "");
}

template <class T, class Function,
	std::enable_if_t<is_valid_verifier<Function, T>::value, int> /* = 0 */>
T CmdlineInput::get_value(std::string_view prompt, Function&& verifier, std::string_view verification_error_hint /* = "" */) {
	assert_default_parser_exists<T>();
	return get_value_impl<T>(prompt, default_parser_t<T>{}, std::forward<Function>(verifier),
		default_parser<T>::error_hint(), verification_error_hint);
}

template <class T, class Parser,
	std::enable_if_t<!is_valid_verifier<Parser, T>::value, int> /* = 0 */>
T CmdlineInput::get_value(std::string_view prompt, Parser&& parser) {
	return get_value_impl<T>(prompt, std::forward<Parser>(parser), no_verifier,
		"", "");
}

template <class T, class Parser, class Function,
	std::enable_if_t<is_valid_verifier<Function, T>::value, int> /* = 0 */>
T CmdlineInput::get_value(std::string_view prompt, Parser&& parser, Function&& verifier,  std::string_view verification_error_hint /* = "" */) {
	return get_value_impl<T>(prompt, std::forward<Parser>(parser), std::forward<Function>(verifier),
		"", verification_error_hint);
}

template <class T, class Parser, class Function>
T CmdlineInput::get_value_impl(std::string_view prompt, Parser&& parser, Function&& verifier,
	std::string_view parser_error_hint, std::string_view verification_error_hint)
{
	std::string input;
	
	for (unsigned i = 0; i < m_nattempts; ++i) {
		T result{}; // don't move it above. result should be cleared after each iteration
		print_value_prompt(prompt);
		bool ok = read_input(input);
		if (!ok && m_exit_on_eof)
			throw IOError("EOF received");
		if (ok && try_parse(result, input, parser, verifier, parser_error_hint, verification_error_hint))
			return result;
		std::cout << std::endl;
		input.clear();
	}
	throw AttemptsLimitError();
}

template <class T, class Parser, class Function>
bool CmdlineInput::try_parse(T& result, std::string& input, Parser& parser, Function& verifier,
	std::string_view parser_error_hint, std::string_view verification_error_hint)
{
	auto fst = input.cbegin();
	auto last = input.cend();
	bool ok;
	try {
	 ok = boost::spirit::qi::phrase_parse(fst, last, parser, boost::spirit::qi::space, result);
	} catch (ParserError& e) {
		report_error(e.what());
		return false;
	}
	if (!ok || fst != last) {
		report_error(parser_error_hint);
		return false;		
	}
	if constexpr (!std::is_same<Function, no_verifier_t>::value) {
		ok = static_cast<bool>(verifier(result));
		if (!ok && !verification_error_hint.empty())
			std::cerr << std::endl << "Error: " << verification_error_hint << std::endl;
		return ok;
	}
	return true;
}

inline void
CmdlineInput::print_value_prompt(std::string_view prompt) {
	std::cout << prompt << ": ";
	std::cout.flush();
	if (!std::cout)
		throw IOError("stdout is broken");
}

inline bool
CmdlineInput::read_input(std::string& result) {
	if (m_hide_input_symbols)
		return get_password(result);
	return static_cast<bool>(std::getline(std::cin, result));
}

void CmdlineInput::report_error(std::string_view descr) {
	std::cerr << std::endl;
	if (!descr.empty())
		std::cerr << "Error: " << descr << std::endl;
}

} // clio namespace end