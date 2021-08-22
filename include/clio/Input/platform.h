/* some platform dependent features */

#pragma once

#include <iostream>

namespace clio {

void cls(std::ostream& os = std::cout);
bool get_password(std::string& result);

} // clio namespace end