#include <clio/Input/platform.h>

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
# error "Windows is not supported. Fuck you."
#endif

#include <unistd.h>

namespace clio {

void cls(std::ostream& os /* = std::cout */) {
	os << "\e[2J\e[H";
}

bool get_password(std::string& result) {
	if (char *str = getpass("")) {
		result = str;
		return true;
	}
	return false;
}

} // clio namespace end