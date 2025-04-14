#include <gtest/gtest.h>

#include "../../src/commands/Version.cpp"
#include "utils/Execute.hpp"

TEST(VersionTest, VersionCommand) {
	// Execute the CLI command
	std::string output = Execute("cd ../../build && ./xported-cli version");

	// Remove any trailing whitespace (like newlines)
	if (!output.empty() && output.back() == '\n') {
		output.pop_back();
	};

	// Verify the output
	EXPECT_EQ(output, "Xported CLI version 0.1.0");

	// Check that the command returns success exit code
	int exitCode = system("cd ../../build && ./xported-cli version > /dev/null 2>&1");
	EXPECT_EQ(exitCode, 0);
}