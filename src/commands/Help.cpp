#include <algorithm>
#include <iostream>

#include "Command.hpp"
#include "CommandRegistry.hpp"
#include "utils/ParseArgs.hpp"

class Help : public Command {
public:
	std::string name() const override { return "help"; }
	std::string description() const override {
		return "Show this help message or details about a specific command";
	}

	std::vector<CommandArgument> arguments() const override {
		return {
			{"command", "Show help for a specific command", false, ""}};
	}

	std::vector<std::string> usage() const override {
		return {
			"xported-cli help",						// Show help for all commands
			"xported-cli help --command=<command>"	// Show help for a specific command
		};
	}

	int execute(const std::vector<CommandLineArgument> &args) override {
		if (args.empty()) {
			// Show help for all commands
			std::cout << "Available commands:\n";
			for (const auto &[name, command] : CommandRegistry::instance().allCommands()) {
				std::cout << "  " << name << ": " << command->description() << "\n";
			};
			std::cout << "\nUse 'xported-cli help --command=<command>' for more information on a specific command.\n";
		} else {
			// Show help for a specific command
			auto it = std::find_if(args.begin(), args.end(),
								   [](const CommandLineArgument &arg) { return arg.name == "command"; });
			if (it != args.end()) {
				const std::string commandName = it->value;
				Command *command = CommandRegistry::instance().getCommand(commandName);
				if (command) {
					std::cout << command->name() << ": " << command->description() << "\n";
					std::cout << "Arguments:\n";
					for (const auto &arg : command->arguments()) {
						std::cout << "  " << arg.name << ": " << arg.description;
						if (!arg.defaultValue.empty()) {
							std::cout << " (default: " << arg.defaultValue << ")";
						};
						std::cout << "\n";
					};
					std::cout << "Usage:\n";
					for (const auto &usage : command->usage()) {
						std::cout << "  " << usage << "\n";
					};
				} else {
					std::cerr << "Error: Command '" << commandName
							  << "' not found.\n";
					return 1;  // Error code for command not found
				};
			} else {
				// Default to showing general help information
				std::cout << "Available commands:\n";
				for (const auto &[name, command] : CommandRegistry::instance().allCommands()) {
					std::cout << "  " << name << ": " << command->description() << "\n";
				};
				std::cout << "\nUse 'xported-cli help --command=<command>' for more information on a specific command.\n";
				return 0;  // Success
			};
		};
		return 0;  // Success
	}
};

// Auto-register the command
namespace {
	struct Registrar {
		Registrar() {
			CommandRegistry::instance().registerCommand(std::make_unique<Help>());
		}
	} autoRegister;
};	// namespace