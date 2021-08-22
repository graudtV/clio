#include <clio/Input.h>

int main() try {
	clio::CmdlineInput input;

	/* Gets any value, which fits in unsigned short */
	auto port = input.get_value<unsigned short>("Enter port (from 0 to 65535)");
	
	/* Gets any value which fits in int and makes user check */
	auto option = input.get_value<int>("Enter option from 1 to 10",
		[](int option) { return option >= 1 && option <= 10; }, // verify
		"option must be from 1 to 10" // error hint
	);

	/* Parses input with custom parser */
	// auto ip = input.get_value<std::string>("Enter server IP", clio::ip_v4);

	/* for std::string you need to specify parser manually. Fortunately,
	 * two parsers are already provided:
	 * clio::full_line gets full line, including all spaces. Line may be empty
	 * clio::single_word expects single non-empty word */
	auto name = input.get_value<std::string>("Enter your name and surname", clio::full_line);
	auto login = input.get_value<std::string>("Enter your login", clio::single_word);

	/* One can hide symbols to enter passwords */
	input.hide_input_symbols();
	auto password = input.get_value<std::string>("Enter password (your input will be shown afterwards)", clio::single_word);

	std::cout << std::endl;
	std::cout << "You entered:" << std::endl
		<< "  port: " << port << std::endl
		<< "  option: " << option << std::endl
		// << "  ip: " << ip << std::endl
		<< "  login: '" << login << "'" << std::endl
		<< "  name: '" << name << "'" << std::endl
		<< "  password: '" << password << "'" << std::endl
		;
	return 0;
} catch (clio::RuntimeError& e) {
	std::cout << "Input error: " << e.what() << std::endl;
	return 1;
}
