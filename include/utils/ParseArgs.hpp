#pragma once
#include <string>
#include <vector>

/**
 * @brief Represents a command argument with its properties
 */
struct CommandLineArgument {
	std::string name;		   // Name of the argument
	std::string type;		   // Type of the argument (e.g., "positional", "flag")
	std::string value;		   // If type is "flag", this is the flag value,
							   // otherwise it's the positional argument name
};

std::vector<CommandLineArgument> ParseArgs(int argc, char *argv[]);