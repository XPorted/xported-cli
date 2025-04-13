#include <iostream>
#include <vector>

#include "CommandRegistry.hpp"
#include "utils/ParseArgs.hpp"

int main(int argc, char *argv[]) {
	// Get the singleton instance of CommandRegistry
	auto &registry = CommandRegistry::instance();
	std::vector<std::string> args(argv + 1, argv + argc);

	// Parse command-line arguments
	auto parsedArgs = ParseArgs(argc, argv);

	// Get the first positional argument as the command
	CommandLineArgument commandArg;
	if (!args.empty()) {
		commandArg = parsedArgs[0];
		if (commandArg.type != "positional") {
			std::cerr << "Invalid command format.\n";
			std::cerr << "Usage: xported-cli <command> [options]\n";
			std::cerr << "Use 'xported-cli help' for more information.\n";
			return 1; // Error code for invalid command format
		};
	} else {
		std::cerr << "No command provided.\n";
		std::cerr << "Use 'xported-cli help' for more information.\n";
		return 1; // Error code for no command
	};

	// Check if the command exists in the registry
	Command *cmd = registry.getCommand(commandArg.name);
	if (cmd) {
		// Remove the command name from parsedArgs
		parsedArgs.erase(parsedArgs.begin());
		// Execute the command with the remaining arguments
		// Note: The command's execute method should handle its own argument parsing
		int result = cmd->execute(parsedArgs);
		if (result != 0) {
			std::cerr << "Command execution failed with error code: " << result << "\n";
			return result;
		};
	} else {
		std::cerr << "Command '" << commandArg.name << "' not found.\n";
		return 1; // Error code for command not found
	};

	// Clear the registry
	registry.clear();
	return 0; // Success
}