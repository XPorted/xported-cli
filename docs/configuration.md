# Configuration

## Overview
XPorted CLI uses two main configuration files:

1. **`.xported`**: A TOML configuration file stored in the root of the directory where the CLI is executed. This file contains settings that control the behavior of the CLI, including file management options, remote server configurations, and other preferences.

2. **`.xcludes`**: A file similar to `.gitignore` that specifies patterns for files and directories that should be excluded from XPorted's processing operations. This file uses pattern matching to determine which files to skip during CLI operations.

Both files work together to configure how the XPorted CLI behaves in your directory environment, with `.xported` handling general configuration settings and `.xcludes` managing file exclusions.

## Configuration File
The `.xported` configuration file is a TOML-formatted file that stores settings and preferences for the XPorted CLI. This file controls various aspects of the tool's behavior and should be placed in the root directory of your project.

## Configuration Sections
### 1. `schema`
- **Type**: String
- **Description**: Specifies the version of the configuration schema. This is important for compatibility with future versions of XPorted CLI.
- **Example**: `schema = "v1"`
### 2. `owner`
- **Type**: Table
- **Description**: Contains information about the owner of the configuration file.
- **Fields**:
  - `name`: The name of the owner.
  - `email`: The email address of the owner.
- **Example**:
```toml
[owner]
name = "Your Name"
email = "example@email.com"
```
### 3. `contributors`
- **Type**: Array of Tables
- **Description**: Contains information about contributors to the directory.
- **Fields**:
  - `name`: The name of the contributor.
  - `email`: The email address of the contributor.
- **Example**:
```toml
[[contributors]]
name = "Contributor Name"
email = "contributor@email.com"

[[contributors]]
name = "Second Contributor Name"
email = "contributor2@email.com"
```
### 4. `access`
- **Type**: Table
- **Description**: Contains settings related to remote access.
- **Fields**:
  - `http`: A table containing HTTP access settings.
	- `enabled`: A boolean indicating whether HTTP access is enabled.
	- `port`: The port number for HTTP access.
- **Example**:
```toml
[access.http]
enabled = true
port = 8080
```

## Customizing the Configuration
You can customize the configuration file to suit your needs. Here are some common modifications:
- **Adding Contributors**: You can add multiple contributors by repeating the `[[contributors]]` section.
- **Changing Access Settings**: Modify the `access` section to enable or disable remote access and change the port number.

## Example Configuration
Here is an example of a more complex configuration file:
```toml
# .xported
# This file is used to store the configuration for the xported CLI.

schema = "v1" # The schema version of the configuration file.

[owner]
name = "Your Name"
email = "example@email.com"

[[contributors]]
name = "Contributor Name"
email = "contributor@email.com"

[access.http]
enabled = true
port = 8080
```

## Exlusion File
The `.xcludes` file is used to specify files and directories that should be excluded from XPorted's processing operations. Similar to `.gitignore`, this file uses pattern matching to determine which files to skip.

### Location
The `.xcludes` file should be placed in the root of your directory, alongside the `.xported` configuration file.

### Syntax
- Each line in the file specifies a pattern
- Blank lines are ignored
- Lines starting with `#` are comments
- An asterisk (`*`) matches zero or more characters
- A question mark (`?`) matches exactly one character
- Patterns ending with `/` match directories only
- Patterns starting with `/` match from the root of the directory
- Patterns starting with `!` negate a previous pattern (include the file)

### Example Patterns
```
# Ignore all .log files
*.log

# Ignore the build directory
build/

# Ignore node_modules directory
node_modules/

# Ignore all .txt files in the doc/ directory
doc/*.txt

# Ignore all .tmp files
**/*.tmp

# Include important.log even though we're ignoring .log files
!important.log
```

### Sample .xcludes File
```
# XPorted exclusions

# Temporary files
*.tmp
*.bak
.DS_Store

# Build artifacts
dist/
build/
*.min.js

# Dependencies
node_modules/
vendor/

# Local environment files
.env
.env.local
```

### Best Practices
- Be specific with your exclusions to avoid accidentally ignoring important files
- Add comments to explain why certain patterns are excluded
- Organize your exclusions by category (temp files, build artifacts, etc.)
- Review your exclusions periodically as your directory evolves

## Next Steps
Now that you have a basic understanding of the configuration file, you can explore specific commands in detail. Check out the [Usage](usage.md) section for more information on how to use the CLI effectively, and the [Development](development.md) section if you're interested in contributing to XPorted.