#pragma once

#include "default_parser.h"
#include "Parser/ParserError.h"
#include "platform.h"
#include <cassert>

namespace clio {

template <class T>
constexpr void assert_default_parser_exists() {
	static_assert(default_parser_exists<T>::value,
		"Cannot parse selected value type because no default parser exists "
		"Please use other type or specify parser manually");	
}

template <class T>
T CmdlineInput::get_value(std::string_view prompt) {
	assert_default_parser_exists<T>();
	return get_value_impl<T>(prompt, default_parser_t<T>{}, no_verifier_t{},
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
	return get_value_impl<T>(prompt, std::forward<Parser>(parser), no_verifier_t{},
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
		if (!read_input(input))
			throw IOError("EOF received");
		if (try_parse(result, input, parser, verifier, parser_error_hint, verification_error_hint))
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
	if constexpr (!std::is_same_v<std::remove_reference_t<Function>, no_verifier_t>) {
		ok = static_cast<bool>(verifier(result));
		if (!ok && !verification_error_hint.empty())
			std::cerr << std::endl << "Error: " << verification_error_hint << std::endl;
		return ok;
	}
	return true;
}

} // clio namespace end