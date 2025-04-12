#include <gtest/gtest.h>

// Main function to run the tests
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
