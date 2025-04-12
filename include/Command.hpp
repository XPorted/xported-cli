#pragma once
#include <string>
#include <vector>

/**
 * @brief Represents a command argument with its properties
 */
struct CommandArgument {
	std::string name;		   // Name of the argument
	std::string description;   // Description of the argument
	bool required;			   // Whether this argument is required
	std::string defaultValue;  // Default value (if not required)
};

/**
 * @class Command
 * @brief Abstract base class for commands.
 *
 * This class defines the interface for all commands in the application.
 * Derived classes must implement the `name`, `description`, and `execute` methods.
 *
 * The `name` method should return the name of the command, which is used to identify it.
 *
 * The `description` method should return a brief description of the command's functionality.
 *
 * The `execute` method is where the command's logic is implemented. It takes a vector of strings as arguments, which can be used to pass parameters to the command.
 *
 * Example usage:
 * ```cpp
 * class MyCommand : public Command {
 * public:
 * 	std::string name() const override { return "myCommand"; }
 * 	std::string description() const override { return "This is my command"; }
 * 	std::vector<CommandArgument> arguments() const override {
 * 		return {
 * 			{"file", "Input file path", true, ""},
 * 			{"format", "Output format", false, "text"}
 * 		};
 * 	}
 * 	std::vector<std::string> usage() const override {
 * 		return {
 * 			"xported-cli myCommand file.txt",
 * 			"xported-cli myCommand file.txt --format=json"
 * 		};
 * 	}
 *
 * 	void execute(const std::vector<std::string> &args) override {
 * 		// Command logic goes here
 * 	}
 * };
 * ```
 *
 * @note The `execute` method should not throw exceptions. Instead, it should handle errors gracefully and return an error code of 0 on success or a non-zero error code on failure.
 */
class Command {
public:
	virtual ~Command() = default;

	/**
	 * @brief Get the name of the command.
	 *
	 * @return The name of the command.
	 */
	virtual std::string name() const = 0;

	/**
	 * @brief Get a brief description of the command.
	 *
	 * @return A string describing the command's functionality.
	 */
	virtual std::string description() const = 0;

	/**
	 * @brief Get the arguments this command accepts.
	 *
	 * @return A vector of CommandArguments that the command accepts.
	 */
	virtual std::vector<CommandArgument> arguments() const {
		return {};	// Default implementation returns empty list
	}

	/**
	 * @brief Get usage examples for this command.
	 *
	 * @return A vector of strings with usage examples.
	 */
	virtual std::vector<std::string> usage() const {
		return {name()};  // Default implementation returns just the command name
	}

	/**
	 * @brief Execute the command with the given arguments.
	 *
	 * @param args A vector of strings representing the command-line arguments.
	 *
	 * @returns int 0 on success, or a non-zero error code on failure.
	 */
	virtual int execute(const std::vector<std::string> &args) = 0;
};