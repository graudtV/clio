#pragma once

#include <clio/Errors.h>
#include <type_traits>
#include <string_view>

namespace clio {

template <class Function, class T, class = void>
struct is_valid_verifier : public std::false_type {};

template <class Function, class T>
struct is_valid_verifier<Function, T, std::enable_if_t<
	std::is_convertible<std::invoke_result_t<Function, T>, bool>::value
>> : public std::true_type {};

class CmdlineInput {
public:
	class AttemptsLimitError;
	class IOError;

	/* Sets number of attempts to try parsing each input value
	 * After all attempts are exhausted, AttemptsLimitError exception is thrown
	 * Default: attempts = 3 */
	CmdlineInput& set_attempts(unsigned attempts /* != 0 */);

	/* Stop processing input by sending IOError if eof was received.
	 * Default: exit = false */
	CmdlineInput& exit_on_eof(bool exit = true);

	/* Hide symbols during entering (with stars or even not print at all)
	 * It is useful for entering passwords
	 * Default: enable = false */
	CmdlineInput& hide_input_symbols(bool enable = true);

	/* Uses default parser. On error prints default hint for this parser */
	template <class T>
	T get_value(std::string_view prompt);

	/*  Uses default parser, applies verifier to parsed value.
	 * If parser fails, prints default hint for this parser
	 * If parser succeed, but verifier returns false, prints
	 * verification_error_hint if it is not empty
	 *  verifier should be a functor which is invokable
	 * with single argument T and which result is convertible to bool,
	 * for example bool (const T&) or bool (T)
	 *
	 *  Usage Note. One can either print error hint from verifier or use
	 * verification_error_hint argument. If verifier makes some simple checks,
	 * probably the latter alternative is better, because in this case
	 * verifier is not responsible for handling errors, so it can be reused
	 * easier in client code. Also client code becomes more short and explicit
	 *  On the other hand, if you do some complex checks and want to
	 * report errors more precisely, depending on what exactly is wrong,
	 * you should use the former alternative or even think about writing
	 * you own parser (but it will require some knowledge in boost::spirit)
	 * The latter one should report errors by throwing clio::ParserError to
	 * bear the unified error printing format (do not print messages in stderr by yourself)
	 */
	template <class T, class Function,
		std::enable_if_t<is_valid_verifier<Function, T>::value, int> = 0>
	T get_value(std::string_view prompt, Function&& verifier, std::string_view verification_error_hint = "");

	/* Allows specifying parser manually. Some predefined parsers
	 * are provided, but one can use any suitable boost::spirit::qi parser */
	template <class T, class Parser,
		std::enable_if_t<!is_valid_verifier<Parser, T>::value, int> = 0>
	T get_value(std::string_view prompt, Parser&& parser);

	/* Same as the previous one, but with verifier */
	template <class T, class Parser, class Function,
		std::enable_if_t<is_valid_verifier<Function, T>::value, int> = 0>
	T get_value(std::string_view prompt, Parser&& parser, Function&& verifier, std::string_view verification_error_hint = "");

private:
	unsigned m_nattempts = 3;
	bool m_exit_on_eof = false;
	bool m_hide_input_symbols = false;

	template <class T, class Parser, class Function>
	T get_value_impl(std::string_view prompt, Parser&& parser, Function&& verifier,
		std::string_view parser_error_hint, std::string_view verification_error_hint);

	template <class T, class Parser, class Function>
	bool try_parse(T& result, std::string& input, Parser& parser, Function& verifier,
		std::string_view parser_error_hint, std::string_view verification_error_hint);

	void print_value_prompt(std::string_view prompt);
	bool read_input(std::string& result);
	void report_error(std::string_view descr);
};

class CmdlineInput::AttemptsLimitError : public RuntimeError {
public:
	AttemptsLimitError() : RuntimeError("number of input attempts exceeded") {}
};

class CmdlineInput::IOError : public RuntimeError {
public:
	IOError(const char *descr) : RuntimeError(descr) {}
};

} // clio namespace end

#include "CmdlineInputImpl.h"