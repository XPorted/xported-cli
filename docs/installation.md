# Installation

## Prerequisites
- C++ compiler with C++17 support
- CMake 3.10 or higher

## Building from source
```bash
# Clone the repository
git clone https://github.com/Xported/xported-cli.git
cd xported-cli

# Create build directory
mkdir -p build && cd build

# Generate build files and compile
cmake ..
make

# Install (optional)
sudo make install
```

## Verifying Installation

After installation, verify that XPorted CLI is working correctly:
```bash
xported-cli version
```

This should display the current version of XPorted CLI.

## Next Steps
Now that you have XPorted CLI installed, you can start using it for file management tasks. Check out the [Getting Started](getting-started.md) guide for more information on how to use the tool effectively.