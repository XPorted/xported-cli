#include <gtest/gtest.h>

#include <vector>

#include "../../src/commands/Help.cpp"
#include "utils/ParseArgs.hpp"

TEST(HelpTest, HelpCommand) {
	Help helpCmd;
	EXPECT_EQ(helpCmd.name(), "help");
	EXPECT_EQ(helpCmd.description(), "Show this help message or details about a specific command");
	EXPECT_EQ(helpCmd.arguments().size(), 1);
	EXPECT_EQ(helpCmd.arguments()[0].name, "command");
	EXPECT_EQ(helpCmd.arguments()[0].description, "Show help for a specific command");
	EXPECT_EQ(helpCmd.arguments()[0].required, false);
	EXPECT_EQ(helpCmd.arguments()[0].defaultValue, "");
	EXPECT_EQ(helpCmd.usage().size(), 2);
	EXPECT_EQ(helpCmd.usage()[0], "xported-cli help");
	EXPECT_EQ(helpCmd.usage()[1], "xported-cli help --command=<command>");
	EXPECT_EQ(helpCmd.execute({}), 0);	// Assuming execute returns 0 on success
}