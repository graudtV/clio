#pragma once

#include <clio/Errors.h>

namespace clio {

/* ParserSyntaxError should be thrown from custom parsers
 * to indicate that syntax/semantic error occured. It enables
 * the invoker of parser to handle and print error in unified manner */
class ParserError : public RuntimeError {
public:
	ParserError(const char *descr) : RuntimeError(descr) {}
	ParserError(const std::string& descr) : RuntimeError(descr) {}
};

} // clio namespace end