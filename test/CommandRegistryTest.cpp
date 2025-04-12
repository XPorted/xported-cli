#include "CommandRegistry.hpp"

#include <gtest/gtest.h>

#include "Command.hpp"

class TestCommand : public Command {
public:
	TestCommand() = default;

	std::string name() const override {
		return "test";
	}

	std::string description() const override {
		return "A test command";
	}

	std::vector<CommandArgument> arguments() const override {
		return {
			{"arg1", "First argument", false, ""},
			{"arg2", "Second argument", false, ""},
			{"arg3", "Third argument", false, "default_value"}};
	}

	std::vector<std::string> usage() const override {
		return {
			"test <arg1>",
			"test <arg1> <arg2>",
			"test <arg1> <arg2> <arg3>"};
	}

	int execute(const std::vector<std::string>& args) override {
		// Simulate command execution
		if (args.empty()) {
			return 1;  // Error: no arguments provided
		};
		if (args.size() > 3) {
			return 2;  // Error: too many arguments
		};
		if (args.size() == 1 && args[0] == "error") {
			return 3;  // Simulate an error
		};
		// Simulate successful execution
		return 0;
	}
};
class TestCommand2 : public Command {
public:
	TestCommand2() = default;

	std::string name() const override {
		return "test2";
	}

	std::string description() const override {
		return "Another test command";
	}

	std::vector<CommandArgument> arguments() const override {
		return {
			{"arg1", "First argument", false, ""},
			{"arg2", "Second argument", false, ""}};
	}

	std::vector<std::string> usage() const override {
		return {"test2 <arg1>", "test2 <arg1> <arg2>"};
	}

	int execute(const std::vector<std::string>& args) override {
		return 0;  // Simulate successful execution
	}
};

// Test cases for CommandRegistry

// 1. Test the singleton instance
TEST(CommandRegistryTest, SingletonInstance) {
	CommandRegistry &instance1 = CommandRegistry::instance();
	CommandRegistry &instance2 = CommandRegistry::instance();
	EXPECT_EQ(&instance1, &instance2);
}
// 2. Test command registration
TEST(CommandRegistryTest, RegisterCommand) {
	CommandRegistry &registry = CommandRegistry::instance();
	registry.clear();  // Clear any existing commands

	auto command = std::make_unique<TestCommand>();
	registry.registerCommand(std::move(command));

	EXPECT_NE(registry.getCommand("test"), nullptr);
	EXPECT_EQ(registry.getCommand("nonexistent"), nullptr);
}
// 3.1 Single command registration
TEST(CommandRegistryTest, SingleCommandRegistration) {
	CommandRegistry &registry = CommandRegistry::instance();
	registry.clear();  // Clear any existing commands

	auto command = std::make_unique<TestCommand>();
	registry.registerCommand(std::move(command));

	EXPECT_NE(registry.getCommand("test"), nullptr);
	EXPECT_EQ(registry.getCommand("nonexistent"), nullptr);
}
// 3.2 Multiple command registration
TEST(CommandRegistryTest, MultipleCommandRegistration) {
	CommandRegistry &registry = CommandRegistry::instance();
	registry.clear();  // Clear any existing commands

	auto command1 = std::make_unique<TestCommand>();
	auto command2 = std::make_unique<TestCommand2>();
	registry.registerCommand(std::move(command1));
	registry.registerCommand(std::move(command2));

	EXPECT_NE(registry.getCommand("test"), nullptr);
	EXPECT_NE(registry.getCommand("test2"), nullptr);
	EXPECT_EQ(registry.getCommand("nonexistent"), nullptr);
}
// 4. Test command execution
TEST(CommandRegistryTest, CommandExecution) {
	CommandRegistry &registry = CommandRegistry::instance();
	registry.clear();  // Clear any existing commands

	auto command = std::make_unique<TestCommand>();
	registry.registerCommand(std::move(command));

	Command *cmd = registry.getCommand("test");
	EXPECT_NE(cmd, nullptr);

	// Test valid execution
	std::vector<std::string> args1 = {"arg1", "arg2", "arg3"};
	EXPECT_EQ(cmd->execute(args1), 0);

	// Test execution with no arguments
	std::vector<std::string> args2 = {};
	EXPECT_EQ(cmd->execute(args2), 1);

	// Test execution with too many arguments
	std::vector<std::string> args3 = {"arg1", "arg2", "arg3", "extra_arg"};
	EXPECT_EQ(cmd->execute(args3), 2);

	// Test execution with an error case
	std::vector<std::string> args4 = {"error"};
	EXPECT_EQ(cmd->execute(args4), 3);
}
// 5. Test command clearing
TEST(CommandRegistryTest, ClearCommands) {
	CommandRegistry &registry = CommandRegistry::instance();
	registry.clear();  // Clear any existing commands

	auto command = std::make_unique<TestCommand>();
	registry.registerCommand(std::move(command));

	EXPECT_NE(registry.getCommand("test"), nullptr);

	// Clear commands
	registry.clear();

	EXPECT_EQ(registry.getCommand("test"), nullptr);
	EXPECT_EQ(registry.allCommands().size(), 0);
}
// 6. Test command retrieval
TEST(CommandRegistryTest, GetCommand) {
	CommandRegistry &registry = CommandRegistry::instance();
	registry.clear();  // Clear any existing commands

	auto command = std::make_unique<TestCommand>();
	registry.registerCommand(std::move(command));

	Command *cmd = registry.getCommand("test");
	EXPECT_NE(cmd, nullptr);
	EXPECT_EQ(cmd->name(), "test");
	EXPECT_EQ(cmd->description(), "A test command");
	EXPECT_EQ(cmd->arguments().size(), 3);
	EXPECT_EQ(cmd->usage().size(), 3);

	// Test retrieval of a non-existent command
	EXPECT_EQ(registry.getCommand("nonexistent"), nullptr);
}