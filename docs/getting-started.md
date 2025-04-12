# Getting Started with XPorted CLI

## Basic Usage

XPorted CLI uses a command-based interface. The basic syntax is:

```bash
xported-cli <command> [arguments]
```

## Initialize a Directory

To start using XPorted in a directory:

```bash
# Initialize in the current directory
xported-cli init

# Or specify a directory
xported-cli init /path/to/directory

# Force initialization (overwrite existing config)
xported-cli init --force
```

This creates a `xported.toml` configuration file that defines your directory settings.

## Getting Help

To see available commands:

```bash
xported-cli help
```

For help on a specific command:

```bash
xported-cli help --command=init
```

## Next Steps
Now that you have initialized your directory, you can:
- Configure your directory by editing the `xported.toml` file
- Learn about specific commands and their options in the [Usage](usage.md) section
- Explore the [Configuration](configuration.md) section for more details on the configuration file
- Check out the [Development](development.md) section if you're interested in contributing to XPorted