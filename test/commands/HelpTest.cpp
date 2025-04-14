#include <gtest/gtest.h>

#include "../../src/commands/Version.cpp"
#include "utils/Execute.hpp"

TEST(HelpTest, HelpCommandFirstLine) {
	// Execute the CLI command
	std::string output = Execute("cd ../../build && ./xported-cli help");

	// Remove any trailing whitespace (like newlines)
	if (!output.empty() && output.back() == '\n') {
		output.pop_back();
	};

	// Verify the output's first line
	std::string expectedFirstLine = "Available commands:";
	EXPECT_EQ(output.substr(0, expectedFirstLine.length()), expectedFirstLine);
}

TEST(HelpTest, HelpCommandCommandParameter) {
	// Execute the CLI command
	std::string output = Execute("cd ../../build && ./xported-cli help --command=help");

	// Remove any trailing whitespace (like newlines)
	if (!output.empty() && output.back() == '\n') {
		output.pop_back();
	};

	// Verify the output's first line
	std::string expectedFirstLine = "help: Show this help message or details about a specific command";
	EXPECT_EQ(output.substr(0, expectedFirstLine.length()), expectedFirstLine);
}