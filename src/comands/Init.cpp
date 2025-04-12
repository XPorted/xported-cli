#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Command.hpp"
#include "CommandRegistry.hpp"

/**
 * # xported.toml
 * This file is used to store the configuration for the xported CLI.
 *
 * Configuration options:
 * schema = "v1" # The schema version of the configuration file.
 *
 * [owner]
 * name = "Your Name"
 * email = "example@email.com"
 *
 * [[contributors]]
 * name = "Contributor Name"
 * email = "contributor@email.com"
 *
 * [files]
 * includes = ["*.txt", "src/*.js", "main.cpp"]
 * excludes = ["*.log", "*.tmp"]
 *
 * [access.http]
 * enabled = true
 * port = 8080
 */

class Init : public Command {
public:
	std::string name() const override { return "init"; }
	std::string description() const override { return "Initialize a new xported directory"; }

	std::vector<CommandArgument> arguments() const override {
		return {
			{"--force", "Overwrite existing files if they exist."},
			{"<directory>", "The directory to initialize the directory in."}};
	}

	std::vector<std::string> usage() const override {
		return {
			"xported-cli init [--force]",
			"xported-cli init <directory>",
			"xported-cli init <directory> --force",
			"xported-cli init",
		};
	}

	int execute(const std::vector<std::string>& args) override {
		bool force = false;
		std::filesystem::path targetDir;  // Will be set to the first non-flag argument
		bool dirSpecified = false;

		// Start from index 0, but skip "init" as the command name
		size_t startIdx = 0;
		if (!args.empty() && args[0] == "init") {
			startIdx = 1;
		};

		for (size_t i = startIdx; i < args.size(); ++i) {
			const auto& arg = args[i];
			if (arg == "--force") {
				force = true;
			} else if (arg[0] != '-' && !dirSpecified) {
				// Take the first non-flag argument as the target directory
				targetDir = arg;
				dirSpecified = true;
			};
		};

		// If no directory was specified, use the current directory
		if (!dirSpecified) {
			targetDir = std::filesystem::current_path();
		};

		// Create the directory if it doesn't exist
		if (!std::filesystem::exists(targetDir)) {
			if (!std::filesystem::create_directories(targetDir)) {
				std::cout << "Error: Unable to create directory " << targetDir << std::endl;
				return 1;
			};
			std::cout << "Created directory: " << targetDir << std::endl;
		};

		std::filesystem::path configPath = targetDir / "xported.toml";
		if (std::filesystem::exists(configPath) && !force) {
			std::cout << "Error: " << configPath << " already exists. Use --force to overwrite." << std::endl;
			return 1;
		};

		std::ofstream configFile(configPath);
		if (!configFile.is_open()) {
			std::cout << "Error: Unable to create " << configPath << std::endl;
			return 1;
		};

		// Write the default configuration to the file
		configFile << "# xported.toml\n"
				   << "# Configuration for xported CLI\n\n"
				   << "schema = \"v1\"\n\n"
				   << "[owner]\n"
				   << "name = \"Your Name\"\n"
				   << "email = \"example@email.com\"\n\n"
				   << "[[contributors]]\n"
				   << "name = \"Contributor Name\"\n"
				   << "email = \"contributor@email.com\"\n\n"
				   << "[files]\n"
				   << "includes = [\"*.txt\", \"src/*.js\", \"main.cpp\"]\n"
				   << "excludes = [\"*.log\", \"*.tmp\"]\n\n"
				   << "[access.http]\n"
				   << "enabled = true\n"
				   << "port = 8080\n";

		configFile.close();

		std::cout << "Initialized new xported directory in "
				  << std::filesystem::absolute(targetDir) << std::endl;
		std::cout << "Configuration saved to " << configPath << std::endl;

		return 0;
	}
};

// Auto-register the command
namespace {
	struct Registrar {
		Registrar() {
			CommandRegistry::instance().registerCommand(
				std::make_unique<Init>());
		}
	} autoRegister;
};	// namespace