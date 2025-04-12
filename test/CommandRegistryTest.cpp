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

// Test cases for CommandRegistry
TEST(CommandRegistryTest, RegisterAndGetCommand) {
	// Clear the registry first to ensure a clean state
	CommandRegistry::instance().clear();

	// Register a test command
	auto testCmd = std::make_unique<TestCommand>();
	CommandRegistry::instance().registerCommand(std::move(testCmd));

	// Get the command and verify it exists
	Command* cmd = CommandRegistry::instance().getCommand("test");
	ASSERT_NE(cmd, nullptr);
	EXPECT_EQ(cmd->name(), "test");
	EXPECT_EQ(cmd->description(), "A test command");
}

TEST(CommandRegistryTest, GetNonExistentCommand) {
	// Clear the registry first to ensure a clean state
	CommandRegistry::instance().clear();

	// Try to get a command that doesn't exist
	Command* cmd = CommandRegistry::instance().getCommand("nonexistent");
	EXPECT_EQ(cmd, nullptr);
}

TEST(CommandRegistryTest, AllCommands) {
	// Clear the registry first to ensure a clean state
	CommandRegistry::instance().clear();

	// Register a test command
	CommandRegistry::instance().registerCommand(std::make_unique<TestCommand>());

	// Get all commands and verify the size
	const auto& commands = CommandRegistry::instance().allCommands();
	EXPECT_EQ(commands.size(), 1);
	EXPECT_TRUE(commands.find("test") != commands.end());
}

TEST(CommandRegistryTest, ClearCommands) {
	// Register a test command
	CommandRegistry::instance().registerCommand(std::make_unique<TestCommand>());

	// Clear the registry
	CommandRegistry::instance().clear();

	// Verify that no commands exist
	const auto& commands = CommandRegistry::instance().allCommands();
	EXPECT_EQ(commands.size(), 0);
}

TEST(CommandRegistryTest, CommandExecution) {
	// Clear the registry first to ensure a clean state
	CommandRegistry::instance().clear();

	// Register a test command
	CommandRegistry::instance().registerCommand(std::make_unique<TestCommand>());

	// Get the command
	Command* cmd = CommandRegistry::instance().getCommand("test");
	ASSERT_NE(cmd, nullptr);

	// Test execution with different scenarios
	EXPECT_EQ(cmd->execute({}), 1);								   // No arguments
	EXPECT_EQ(cmd->execute({"arg1"}), 0);						   // One argument
	EXPECT_EQ(cmd->execute({"arg1", "arg2"}), 0);				   // Two arguments
	EXPECT_EQ(cmd->execute({"arg1", "arg2", "arg3"}), 0);		   // Three arguments
	EXPECT_EQ(cmd->execute({"arg1", "arg2", "arg3", "arg4"}), 2);  // Too many arguments
	EXPECT_EQ(cmd->execute({"error"}), 3);						   // Error argument
}

// Main function to run the tests
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
