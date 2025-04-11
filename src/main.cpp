#include <iostream>
#include <vector>

#include "CommandRegistry.hpp"

int main(int argc, char *argv[]) {
	// Get the singleton instance of CommandRegistry
	auto &registry = CommandRegistry::instance();
	std::vector<std::string> args(argv + 1, argv + argc);

	// Check if the command is registered

	// Default to "help" if no command is provided
	if (args.empty()) {
		if (auto *helpCmd = registry.getCommand("help")) {
			helpCmd->execute({});
		};
		return 1;
	};

	// Check if the command is registered
	const std::string commandName = args[0];
	if (auto *cmd = registry.getCommand(commandName)) {
		cmd->execute(args);
	} else {
		std::cerr << "Error: Unknown command '" << commandName << "'\n";
		return 1;
	};

	return 0;
}