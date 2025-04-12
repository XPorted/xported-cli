#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Command.hpp"

/**
 * @brief Singleton class to manage commands creation and execution.
 *
 * Usage:
 * ```cpp
 * #include "CommandRegistry.hpp"
 *
 * int main() {
 * 	// Get the singleton instance of CommandRegistry
 * 	auto &registry = CommandRegistry::instance();
 * 	std::vector<std::string> args = {"arg1", "arg2"};
 *
 * 	// Test command registration and execution
 * 	if (auto *cmd = registry.getCommand("myCommand")) {
 * 		cmd->execute(args);
 * 	} else {
 * 		std::cerr << "Command not found\n";
 * 	};
 * }
 * ```
 *
 * @note This class is a singleton, meaning that only one instance of it can exist.
 */
class CommandRegistry {
public:
	static CommandRegistry &instance() {
		static CommandRegistry instance;
		return instance;
	}

	/**
	 * @brief Register a command.
	 */
	void registerCommand(std::unique_ptr<Command> cmd) {
		commands_[cmd->name()] = std::move(cmd);
	}

	Command *getCommand(const std::string &name) {
		auto it = commands_.find(name);
		return (it != commands_.end()) ? it->second.get() : nullptr;
	}

	const std::map<std::string, std::unique_ptr<Command>> &allCommands() const {
		return commands_;
	}

	/**
	 * @brief Clear all registered commands.
	 */
	void clear() {
		commands_.clear();
	}

private:
	std::map<std::string, std::unique_ptr<Command>> commands_;
};