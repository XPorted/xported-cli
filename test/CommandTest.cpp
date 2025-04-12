#include "Command.hpp"
#include <gtest/gtest.h>

// Basic tests for the Command base class functionality
TEST(CommandTest, CommandArgumentsHandling) {
    // Create a concrete command implementation for testing
    class TestableCommand : public Command {
    public:
        std::string name() const override { return "testable"; }
        std::string description() const override { return "Testable command"; }
        std::vector<CommandArgument> arguments() const override {
            return {{"arg1", "Test arg", false, "default"}};
        }
        std::vector<std::string> usage() const override { 
            return {"testable <arg1>"}; 
        }
        int execute(const std::vector<std::string>& args) override { return 0; }
    };
    
    TestableCommand cmd;
    auto args = cmd.arguments();
    
    ASSERT_EQ(args.size(), 1);
    EXPECT_EQ(args[0].name, "arg1");
    EXPECT_EQ(args[0].description, "Test arg");
    EXPECT_FALSE(args[0].required);
    EXPECT_EQ(args[0].defaultValue, "default");
}