# Development

## Contributing to XPorted
XPorted is an open-source project, and we welcome contributions from the community. Whether you're fixing bugs, adding new features, or improving documentation, your help is appreciated!

## Project Structure
The XPorted project is organized into several directories, each serving a specific purpose:

```
xported-cli/
 ├── src/
 │ 	├── main.cpp # Main entry point for the application
 │ 	└── commands/
 ├── include/
 ├── docs/
 ├── tests/
 ├── .gitignore
 ├── CMakeLists.txt # CMake build configuration
 ├── LICENSE
 └── README.md
```

## Setting Up the Development Environment
### Prerequisites
- C++ compiler with C++17 support
- CMake 3.10 or higher
- Git
- Optional: A code editor or IDE (e.g., Visual Studio Code, CLion) for easier development
### Cloning the Repository
To get started, clone the repository:

```bash
git clone https://github.com/XPorted/xported-cli.git
cd xported-cli
```
### Building the Project
To build the project, create a build directory and run CMake:

```bash
mkdir -p build && cd build
cmake ..
make
```
### Running
After building, you can run the:

```bash
./xported-cli
```
### Running Tests
XPorted CLI includes a test suite to ensure the functionality of the commands with the use of Google Test framework. To run the tests, follow these steps:

```bash
cd build # Assuming you are in the root directory and have built the project
./ctest
```

## Command Structure
### Adding a New Command
To add a new command to XPorted, follow these steps:
1. Create a new source file in the `src/commands/` directory. Name it according to the command you are implementing (e.g., `MyCommand.cpp`).
2. Implement the `Command` interface in the new file. The interface should include methods for executing the command and handling any arguments.
3. Register the new command using the auto-registration pattern.

Here's an example for a new command:

```cpp
// src/comands/MyCommand.cpp
#include <iostream>
#include "Command.hpp"
#include "CommandRegistry.hpp"

class MyCommand : public Command {
public:
	std::string name() const override { return "mycommand"; }
	std::string description() const override { return "Description of my command"; }

	std::vector<CommandArgument> arguments() const override {
		return {
			{"argument", "Description of argument", true, ""}
		};
	}

	std::vector<std::string> usage() const override {
		return {
			"xported-cli mycommand <argument>",
			"xported-cli mycommand --option=value"
		};
	}

	int execute(const std::vector<std::string> &args) override {
		// Command implementation goes here
		std::cout << "MyCommand executed with " << args.size() << " arguments\n";
		for (const auto &arg : args) {
			std::cout << "Argument: " << arg << "\n";
		};
		return 0; // Return 0 for success, non-zero for failure
	}
};

// Auto-register the command
namespace {
	struct Registrar {
		Registrar() {
			CommandRegistry::instance().registerCommand(
				std::make_unique<MyCommand>()
			);
		}
	} autoRegister;
}  // namespace
```
### Command Interface
The `Command` interface defines the structure for all commands in XPorted. It includes methods for:
- `name()`: Returns the name of the command.
- `description()`: Returns a brief description of the command.
- `arguments()`: Returns a list of arguments required by the command.
- `usage()`: Returns usage examples for the command.
- `execute()`: The main method that executes the command logic.
### Command Registry
The `CommandRegistry` class is responsible for managing all registered commands. It provides methods to register new commands and execute them based on user input.
### Building and Testing
After making changes, you can build the project again using the same `cmake` and `make` commands.
1. Build the project:
```
cd build
cmake ..
make
```
2. Run the tests:
```bash
ctest # Assuming you are in the build directory
```

## Coding Standards
The project follows a specific coding style:
- Use 4 spaces for indentation.
- Google-style braces with adaptations for C++.
- Line lenghth is not restricted, but try to keep it reasonable.
- Use proper doumentation for classes and methods.

## Creating a Pull Request
1. Fork the repository.
2. Create a new branch for your changes.
3. Make your changes and commit them with a clear message.
4. Ensure your code passes all tests and adheres to the coding standards.
5. Ensure your code is documented.
6. Push your changes to your forked repository.
7. Create a pull request against the main repository.
8. Provide a clear description of your changes and any relevant information.

## License
XPorted is licensed under the MIT License. See the [LICENSE](../LICENSE) file for more details.