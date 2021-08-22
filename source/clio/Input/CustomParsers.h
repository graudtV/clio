#pragma once

#include <string>

namespace clio {
namespace detail {

/* Parses one non-empty word */
template <class String, class Skipper, class Iterator = typename String::const_iterator>
struct SingleWordParser : public boost::spirit::qi::grammar<Iterator, Skipper> {
	SingleWordParser() : SingleWordParser::base_type(start) {
		using boost::spirit::qi::lexeme;
		using boost::spirit::qi::char_;

		start %= lexeme[+char_];
	}

	boost::spirit::qi::rule<Iterator, String(), Skipper> start;
};

} // detail namespace end

using single_word = detail::SingleWordParser<
	std::string, boost::spirit::qi::space_type
>;

template <class String, class Skipper>
struct ParserHint<detail::SingleWordParser<String, Skipper>> {
	static constexpr auto help_message() {
		return "Expected single non-empty word";
	}
};

} // clio namespace end