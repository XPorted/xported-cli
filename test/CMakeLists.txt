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
# Individual test executables
add_executable(command_registry_test CommandRegistryTest.cpp)
add_executable(command_test CommandTest.cpp)
add_executable(version_test commands/VersionTest.cpp)

# Link libraries for each test
target_link_libraries(command_registry_test gtest gtest_main pthread)
target_link_libraries(command_test gtest gtest_main pthread)
target_link_libraries(version_test gtest gtest_main pthread)

# Add individual tests
add_test(NAME command_registry_test COMMAND command_registry_test)
add_test(NAME command_test COMMAND command_test)
add_test(NAME version_test COMMAND version_test)

# Optional: Keep the all_tests target if you still want it
add_executable(all_tests
	CommandRegistryTest.cpp
	CommandTest.cpp
	commands/VersionTest.cpp
)
target_link_libraries(all_tests gtest gtest_main pthread)
add_test(NAME all_tests COMMAND all_tests)