#include <iostream>

#include "Command.hpp"
#include "CommandRegistry.hpp"
#include "utils/ParseArgs.hpp"

class Version : public Command {
public:
	std::string name() const override { return "version"; }
	std::string description() const override { return "Show the version"; }

	std::vector<CommandArgument> arguments() const override {
		return {};	// Version command doesn't take any arguments
	}

	std::vector<std::string> usage() const override {
		return {
			"version"  // Simple usage - just the command name
		};
	}

	int execute(const std::vector<CommandLineArgument> &) override {
		std::cout << "Xported CLI version 1.0.0\n";	 // Replace with actual version
		return 0;									 // Success
	}
};

// Auto-register the command
namespace {
	struct Registrar {
		Registrar() {
			CommandRegistry::instance().registerCommand(
				std::make_unique<Version>());
		}
	} autoRegister;
};	// namespace