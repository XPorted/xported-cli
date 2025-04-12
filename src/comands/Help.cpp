#include <algorithm>
#include <iostream>

#include "Command.hpp"
#include "CommandRegistry.hpp"

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

	int execute(const std::vector<std::string> &args) override {
		auto &registry = CommandRegistry::instance();

		// Check if a specific command is requested
		auto it = std::find_if(args.begin(), args.end(), [](const std::string &arg) {
			return arg.rfind("--command=", 0) == 0;	 // Check if argument starts with "--command="
		});

		if (it != args.end()) {
			// Extract the command name
			std::string commandName = it->substr(10);  // Remove "--command="
			auto command = registry.getCommand(commandName);
			if (command) {
				std::cout << commandName << ": " << command->description() << "\n";

				// Show command arguments
				auto cmdArgs = command->arguments();
				if (!cmdArgs.empty()) {
					std::cout << "\nArguments:\n";
					for (const auto &arg : cmdArgs) {
						std::cout << "  --" << arg.name;
						if (!arg.required)
							std::cout << " (optional, default: " << (arg.defaultValue.empty() ? "none" : arg.defaultValue) << ")";
						std::cout << ": " << arg.description << "\n";
					};
				};

				// Show usage examples
				auto usageExamples = command->usage();
				if (!usageExamples.empty()) {
					std::cout << "\nUsage:\n";
					for (const auto &example : usageExamples) {
						std::cout << "  " << example << "\n";
					};
				};
				
				return 0; // Success
			} else {
				std::cout << "Command '" << commandName << "' not found.\n";
				return 1; // Error - command not found
			};
		} else {
			// Show all commands
			std::cout << "Available commands:\n";
			for (const auto &[name, cmd] : registry.allCommands()) {
				std::cout << "  " << name << ": " << cmd->description() << "\n";
			};
			std::cout << "\nUse 'help --command=<command>' for more information about a specific command.\n";
			return 0; // Success
		};
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