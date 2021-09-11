#include "CmdlineInput.h"

namespace clio {

CmdlineInput& CmdlineInput::set_attempts(unsigned attempts /* != 0 */) {
	assert(attempts > 0 && "number of attempts must be > 0");
	m_nattempts = attempts;
	return *this;
}

CmdlineInput& CmdlineInput::hide_input_symbols(bool enable /* = true */) {
	m_hide_input_symbols = enable;
	return *this;
}

void CmdlineInput::print_value_prompt(std::string_view prompt) {
	std::cout << prompt << ": ";
	std::cout.flush();
	if (!std::cout)
		throw IOError("stdout is broken");
}

bool CmdlineInput::read_input(std::string& result) {
	if (m_hide_input_symbols)
		return get_password(result);
	return static_cast<bool>(std::getline(std::cin, result));
}

void CmdlineInput::report_error(std::string_view descr) {
	std::cerr << std::endl;
	if (!descr.empty())
		std::cerr << "Error: " << descr << std::endl;
}

} // clio namespace end