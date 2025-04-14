#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "Command.hpp"
#include "CommandRegistry.hpp"
#include "utils/FindInit.hpp"

class Init : public Command {
public:
	std::string name() const override { return "init"; }
	std::string description() const override { return "Initialize a new xported directory"; }

	std::vector<CommandArgument> arguments() const override {
		return {
			{"--force", "Overwrite existing files if they exist.", false, ""},
			{"<directory>", "The directory to initialize the directory in.", false, ""}};
	}

	std::vector<std::string> usage() const override {
		return {
			"xported-cli init [--force]",
			"xported-cli init <directory>",
			"xported-cli init <directory> --force",
			"xported-cli init",
		};
	}

	int execute(const std::vector<CommandLineArgument> &args) override {
		// Get directory argument from args if provided. It should be the first positional argument.
		std::string directory;
		if (!args.empty() && args[0].type == "positional") {
			directory = args[0].value;

			// Check if the argument is a relative or absolute path
			if (std::filesystem::path(directory).is_relative()) {
				// If it's a relative path, convert it to an absolute path
				directory = std::filesystem::absolute(directory).string();
			} else {
				// If it's an absolute path, just use it as is
				directory = std::filesystem::path(directory).string();
			};
		} else {
			// If no directory is provided, use the current working directory
			directory = std::filesystem::current_path().string();
		};

		// Check if the directory valid
		if (directory.empty()) {
			std::cerr << "Error: Directory is empty.\n";
			std::cerr << "Usage: xported-cli init <directory>\n";
			return 1;
		} else if (!std::filesystem::is_directory(directory)) {
			std::cerr << "Error: Path is not a directory.\n";
			std::cerr << "Usage: xported-cli init <directory>\n";
			return 1;
		};

		// Use regex to check if the directory name contains invalid characters
		std::regex invalidChars("[^a-zA-Z0-9_\\-\\./ ]");
		if (std::regex_search(directory, invalidChars)) {
			std::cerr << "Error: Directory name contains invalid characters.\n";
			std::cerr << "Usage: xported-cli init <directory>\n";
			return 1;
		};

		// Check if --force option is provided
		bool force = false;
		for (const auto &arg : args) {
			if (arg.type == "flag" && arg.name == "force") {
				force = true;
				break;
			};
		};

		// Find the initialization file in the given directory or its parent directories
		std::string initFile = FindInit(directory);
		if (!initFile.empty() && !force) {
			std::cerr << "Error: Initialization file already exists in " << initFile << ".\n";
			std::cerr << "If you want to overwrite it, use the --force option.\n";
			std::cerr << "Usage: xported-cli init <directory> --force\n";
			return 1;
		};

		// Create the initialization file in the specified directory
		std::ofstream outFile(directory + "/.xported");
		if (!outFile) {
			std::cerr << "Error: Could not create initialization file in the directory.\n";
			std::cerr << "Usage: xported-cli init <directory>\n";
			return 1;
		};
		outFile << "# .xported" << std::endl
				<< "# This file is used to store the configuration for the xported CLI." << std::endl
				<< "" << std::endl
				<< "schema = \"v1\" # The schema version of the configuration file." << std::endl
				<< "" << std::endl
				<< "[owner]" << std::endl
				<< "name = \"Your Name\"" << std::endl
				<< "email = \"example@email.com\"" << std::endl
				<< "" << std::endl
				<< "[[contributors]]" << std::endl
				<< "name = \"Contributor Name\"" << std::endl
				<< "email = \"contributor@email.com\"" << std::endl
				<< "" << std::endl
				<< "[access.http]" << std::endl
				<< "enabled = true" << std::endl
				<< "port = 8080" << std::endl;

		outFile.close();
		std::cout << "Initialization file created successfully in " << directory << ".\n";
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