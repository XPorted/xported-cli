cmake_minimum_required(VERSION 3.10)

project(xported-cli
    VERSION 0.1.0
    DESCRIPTION "A fast command-line tool for local and remote file management."
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files - include both main source files and command implementations
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Include directories
include_directories(include)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Add compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
elseif(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()

set(CMAKE_INSTALL_MESSAGE LAZY)

enable_testing()
add_subdirectory(test)