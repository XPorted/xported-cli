#include "utils/ParseArgs.hpp"

#include <string>
#include <vector>

std::vector<CommandLineArgument> ParseArgs(int argc, char *argv[]) {
	std::vector<CommandLineArgument> args;

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];

		CommandLineArgument cmdArg;
		cmdArg.name = arg;
		cmdArg.type = "flag";  // Default type is "flag"
		if (arg.find("--") == 0) {
			// This is a flag argument
			cmdArg.name = arg.substr(2);  // Remove "--"
			size_t equalPos = cmdArg.name.find('=');
			if (equalPos != std::string::npos) {
				cmdArg.value = cmdArg.name.substr(equalPos + 1);
				cmdArg.name = cmdArg.name.substr(0, equalPos);
			};
		} else {
			// This is a positional argument
			cmdArg.type = "positional";	 // Change type to "positional"
			cmdArg.value = arg;			 // Set the value to the argument
		};
		args.push_back(cmdArg);
	};

	return args;
}