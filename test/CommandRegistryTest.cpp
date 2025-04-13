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

	int execute(const std::vector<CommandLineArgument> &args) override {
		// Simulate command execution
		if (args.size() < 1) {
			return 1; // Error: not enough arguments
		};
		if (args[0].name != "arg1") {
			return 2; // Error: invalid argument
		};
		if (args.size() > 3) {
			return 3; // Error: too many arguments
		};
		return 0; // Success
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
		return {
			"test2 <arg1>",
			"test2 <arg1> <arg2>"};
	}

	int execute(const std::vector<CommandLineArgument> &args) override {
		if (args.size() < 1) {
			return 1; // Error: not enough arguments
		};
		if (args[0].name != "arg1") {
			return 2; // Error: invalid argument
		};
		if (args.size() > 2) {
			return 3; // Error: too many arguments
		};
		return 0; // Success
	}
};

// Test case for CommandRegistry

// 1. Test the singleton instance
TEST(CommandRegistryTest, SingletonInstance) {
	auto &instance1 = CommandRegistry::instance();
	auto &instance2 = CommandRegistry::instance();
	EXPECT_EQ(&instance1, &instance2);
}
// 2. Test command registration
// 2.a. Test registering a single command
TEST(CommandRegistryTest, RegisterSingleCommand) {
	auto &registry = CommandRegistry::instance();
	registry.clear(); // Clear any existing commands

	auto command = std::make_unique<TestCommand>();
	EXPECT_NO_THROW(registry.registerCommand(std::move(command)));
	EXPECT_EQ(registry.allCommands().size(), 1);
	EXPECT_NE(registry.getCommand("test"), nullptr);
	EXPECT_EQ(registry.getCommand("test")->name(), "test");
}
// 2.b. Test registering multiple commands
TEST(CommandRegistryTest, RegisterMultipleCommands) {
	auto &registry = CommandRegistry::instance();
	registry.clear(); // Clear any existing commands

	auto command1 = std::make_unique<TestCommand>();
	auto command2 = std::make_unique<TestCommand2>();
	EXPECT_NO_THROW(registry.registerCommand(std::move(command1)));
	EXPECT_NO_THROW(registry.registerCommand(std::move(command2)));
	EXPECT_EQ(registry.allCommands().size(), 2);
	EXPECT_NE(registry.getCommand("test"), nullptr);
	EXPECT_NE(registry.getCommand("test2"), nullptr);
}
// 3. Test command retrieval
TEST(CommandRegistryTest, GetCommand) {
	auto &registry = CommandRegistry::instance();
	registry.clear(); // Clear any existing commands

	auto command = std::make_unique<TestCommand>();
	registry.registerCommand(std::move(command));

	EXPECT_NE(registry.getCommand("test"), nullptr);
	EXPECT_EQ(registry.getCommand("nonexistent"), nullptr);
}
// 4. Test command execution
TEST(CommandRegistryTest, ExecuteCommand) {
	auto &registry = CommandRegistry::instance();
	registry.clear(); // Clear any existing commands

	auto command = std::make_unique<TestCommand>();
	registry.registerCommand(std::move(command));

	std::vector<CommandLineArgument> args = {
		{"arg1", "positional", "value1"},
		{"arg2", "positional", "value2"},
		{"arg3", "positional", "value3"}};

	EXPECT_EQ(registry.getCommand("test")->execute(args), 0);
}
// 5. Test command usage
TEST(CommandRegistryTest, CommandUsage) {
	auto &registry = CommandRegistry::instance();
	registry.clear(); // Clear any existing commands

	auto command = std::make_unique<TestCommand>();
	registry.registerCommand(std::move(command));

	EXPECT_EQ(registry.getCommand("test")->usage().size(), 3);
	EXPECT_EQ(registry.getCommand("test")->usage()[0], "test <arg1>");
	EXPECT_EQ(registry.getCommand("test")->usage()[1], "test <arg1> <arg2>");
	EXPECT_EQ(registry.getCommand("test")->usage()[2], "test <arg1> <arg2> <arg3>");
}
// 6. Test command clearing
TEST(CommandRegistryTest, ClearCommands) {
	auto &registry = CommandRegistry::instance();
	registry.clear(); // Clear any existing commands

	auto command = std::make_unique<TestCommand>();
	registry.registerCommand(std::move(command));

	EXPECT_EQ(registry.allCommands().size(), 1);
	registry.clear();
	EXPECT_EQ(registry.allCommands().size(), 0);
}