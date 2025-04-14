# Init

## Overview
The `init` command initializes a new XPorted CLI directory in the current directory. This command creates a new configuration file and sets up the necessary configuration for your directory.

## Command Structure
```bash
xported-cli init [--force] [<directory>]
```

## Options
- `--force`: Force initialization, overwriting any existing configuration files in the specified directory.
- `<directory>`: The directory where you want to initialize the XPorted CLI. If not specified, the current directory will be used.

## Examples
### Initialize in the Current Directory
```bash
xported-cli init
```
This command will create a new `.xported` configuration file in the current directory.
### Initialize in a Specific Directory
```bash
xported-cli init /path/to/directory
```
This command will create a new `.xported` configuration file in the specified directory.
### Force Initialization
```bash
xported-cli init --force
```
This command will overwrite any existing `.xported` configuration file in the current directory or the specified directory.
### Force Initialization in a Specific Directory
```bash
xported-cli init --force /path/to/directory
```
This command will overwrite any existing `.xported` configuration file in the specified directory.

## Next Steps
Now that you have initialized your directory, you can:
- Configure your directory by editing the `.xported` file.
- Learn about specific commands and their options in the [Usage](../usage.md) section.
- Explore the [Configuration](../configuration.md) section for more details on the configuration file.
- Check out the [Development](../development.md) section if you're interested in contributing to XPorted.