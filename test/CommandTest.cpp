#include "Command.hpp"
#include <gtest/gtest.h>

// Basic tests for the Command base class functionality
TEST(CommandTest, CommandArgumentsHandling) {
    // Create a concrete command implementation for testing
	class TestCommand : public Command {
	public:
		std::string name() const override { return "test"; }
		std::string description() const override { return "Test command"; }
		int execute(const std::vector<CommandLineArgument> &args) override {
			return 0; // Dummy implementation
		}
	};
	// Create an instance of the command
	TestCommand cmd;
	// Check the command name
	EXPECT_EQ(cmd.name(), "test");
	// Check the command description
	EXPECT_EQ(cmd.description(), "Test command");
	// Check the default arguments
	EXPECT_TRUE(cmd.arguments().empty());
	// Check the default usage
	EXPECT_EQ(cmd.usage().size(), 1);
	EXPECT_EQ(cmd.usage()[0], "test");
	// Check the execute method
	EXPECT_EQ(cmd.execute({}), 0); // Dummy implementation should return 0
}