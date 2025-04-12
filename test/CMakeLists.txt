cmake_minimum_required(VERSION 3.10)

project(xported-cli-test
    VERSION 0.1.0
    DESCRIPTION "Unit tests for xported-cli"
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the path to the main source files
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/..")

# Download and build GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(CommandRegistryTest CommandRegistryTest.cpp)

# Include the source directory
target_include_directories(CommandRegistryTest PRIVATE ${SOURCE_DIR})

# Link Google Test and required libraries
target_link_libraries(CommandRegistryTest PRIVATE 
    gtest_main
    gmock_main
    pthread
)

# Add tests
add_test(NAME CommandRegistryTest COMMAND CommandRegistryTest)