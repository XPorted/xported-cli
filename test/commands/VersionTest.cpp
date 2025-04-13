#include <gtest/gtest.h>

#include "../../src/commands/Version.cpp"

TEST(VersionTest, VersionCommand) {
	Version versionCmd;
	EXPECT_EQ(versionCmd.name(), "version");
	EXPECT_EQ(versionCmd.description(), "Show the version");
	EXPECT_EQ(versionCmd.arguments().size(), 0);
	EXPECT_EQ(versionCmd.usage().size(), 1);
	EXPECT_EQ(versionCmd.usage()[0], "version");
	EXPECT_EQ(versionCmd.execute({}), 0);	// Assuming execute returns 0 on success
	EXPECT_NO_THROW({
		std::ostringstream oss;
		std::streambuf *oldCoutBuf = std::cout.rdbuf(oss.rdbuf());
		versionCmd.execute({});
		std::cout.rdbuf(oldCoutBuf);
		EXPECT_EQ(oss.str(), "Xported CLI version 0.1.0\n");
	});
}