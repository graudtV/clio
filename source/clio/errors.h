#pragma once

#include <stdexcept>

namespace clio {

/* base class for all clio errors */
class RuntimeError : public std::runtime_error {
public:
	RuntimeError(const char *descr) : std::runtime_error(descr) {}
	RuntimeError(const std::string& descr) : std::runtime_error(descr) {}
};

} // clio namespace end