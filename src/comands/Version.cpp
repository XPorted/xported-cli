#include <iostream>

#include "Command.hpp"
#include "CommandRegistry.hpp"

class VersionCommand : public Command {
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

	int execute(const std::vector<std::string> &) override {
		std::cout << "xported-cli v0.1.0\n";
		return 0;	// Success
	}
};

// Auto-register the command
namespace {
	struct Registrar {
		Registrar() {
			CommandRegistry::instance().registerCommand(
				std::make_unique<VersionCommand>());
		}
	} autoRegister;
};	// namespace