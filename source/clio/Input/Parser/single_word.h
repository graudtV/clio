#pragma once

#include "ParserError.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace clio {
namespace detail {

/* Parses one non-empty word */
template <class String, class Skipper, class Iterator = typename String::const_iterator>
struct SingleWordParser : public boost::spirit::qi::grammar<Iterator, String(), Skipper> {
	SingleWordParser() : SingleWordParser::base_type(start) {
		using boost::spirit::qi::lexeme;
		using boost::spirit::qi::char_;
		using boost::spirit::qi::space;
		using boost::spirit::qi::eoi;
		using boost::spirit::qi::on_error;
		using boost::spirit::qi::fail;

		start %= lexeme[+(char_ - space)] > eoi;
		on_error<fail>(start,
			boost::phoenix::throw_(ParserError("expected single word"))
		);
	}

	boost::spirit::qi::rule<Iterator, String(), Skipper> start;
};

} // detail namespace end

using single_word_type = detail::SingleWordParser<
	std::string, boost::spirit::qi::space_type
>;

inline single_word_type single_word;

} // clio namespace end