#pragma once

#include "ParserError.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace clio {
namespace detail {

/* Parses one non-empty word */
template <class String, class Skipper, class Iterator = typename String::const_iterator>
struct FullLineParser : public boost::spirit::qi::grammar<Iterator, String(), Skipper> {
	FullLineParser() : FullLineParser::base_type(start) {
		using boost::spirit::qi::no_skip;
		using boost::spirit::qi::char_;

		start %= no_skip[*char_];
	}
	boost::spirit::qi::rule<Iterator, String(), Skipper> start;
};

} // detail namespace end

using full_line_type = detail::FullLineParser<
	std::string, boost::spirit::qi::space_type
>;

inline full_line_type full_line;

} // clio namespace end