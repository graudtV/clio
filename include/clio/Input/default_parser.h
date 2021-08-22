#pragma once

#include <boost/spirit/include/qi.hpp>

namespace clio {

/* retrieves boost::spirit parser type corresponding to type T
 * if such parser exists */
template <class T> struct default_parser;

template <class T> using default_parser_t = typename default_parser<T>::type;

template <class T, class = void>
struct default_parser_exists : public std::false_type {};

template <class T>
struct default_parser_exists<T,
	std::void_t<default_parser<T>>
> : public std::true_type {};

/******* unsigned integer parsers *******/

template <> struct default_parser<unsigned short> {
	using type = boost::spirit::ushort_type;

	static constexpr auto error_hint() {
		return "expected unsigned integer (unsigned short)";
	}
};

template <> struct default_parser<unsigned int> {
	using type = boost::spirit::uint_type;

	static constexpr auto error_hint() {
		return "expected unsigned integer (unsigned int)";
	}
};

template <> struct default_parser<unsigned long> {
	using type = boost::spirit::ulong_type;

	static constexpr auto error_hint() {
		return "expected unsigned integer (unsigned long)";
	}
};

template <> struct default_parser<unsigned long long> {
	using type = boost::spirit::ulong_long_type;

	static constexpr auto error_hint() {
		return "expected unsigned integer (unsigned long long)";
	}
};

/******* signed integer parsers *******/

template <> struct default_parser<short> {
	using type = boost::spirit::short_type;

	static constexpr auto error_hint() {
		return "expected signed integer (signed short)";
	}
};

template <> struct default_parser<int> {
	using type = boost::spirit::int_type;

	static constexpr auto error_hint() {
		return "expected signed integer (signed int)";
	}
};

template <> struct default_parser<long> {
	using type = boost::spirit::long_type;

	static constexpr auto error_hint() {
		return "expected signed integer (signed long)";
	}
};

template <> struct default_parser<long long> {
	using type = boost::spirit::long_long_type;

	static constexpr auto error_hint() {
		return "expected signed integer (signed long long)";
	}
};

/******* floating point parsers *******/

template <> struct default_parser<float> {
	using type = boost::spirit::float_type;

	static constexpr auto error_hint() {
		return "expected floating point number (float)";
	}
};

template <> struct default_parser<double> {
	using type = boost::spirit::double_type;

	static constexpr auto error_hint() {
		return "expected floating point number (double)";
	}
};

template <> struct default_parser<long double> {
	using type = boost::spirit::long_double_type;

	static constexpr auto error_hint() {
		return "expected floating point number (long double)";
	}
};

/******* bool parser *******/

template <> struct default_parser<bool> {
	using type = boost::spirit::bool_type;

	static constexpr auto error_hint() {
		return "expected boolean value";
	}
};

} // clio namespace end