#include "clio/Input.h"

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

	/* for std::string clio::single_word (default) and clio::full_line parsers are provided */
	// auto login = input.get_value<std::string>("Enter your login", clio::single_word);

	return 0;
} catch (clio::RuntimeError& e) {
	std::cout << "Input error: " << e.what() << std::endl;
	return 1;
}
