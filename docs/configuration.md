# Configuration

## Overview
XPorted CLI uses a TOML configuration file named `xported.toml` stored in the root of the directory where the CLI is executed. This file contains settings that control the behavior of the CLI, including file management options, remote server configurations, and other preferences.

## Configuration File Structure
The configuration file is structured in a TOML format, which is easy to read and write.

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

### 4. `files`
- **Type**: Table
- **Description**: Contains settings related to file management.
- **Fields**:
  - `includes`: An array of file patterns to include in the file management operations.
  - `excludes`: An array of file patterns to exclude from the file management operations.
- **Example**:
```toml
[files]
includes = ["*.txt", "src/*.js", "main.cpp"]
excludes = ["*.log", "*.tmp"]
```
### 5. `access`
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
- **Modifying File Patterns**: Adjust the `includes` and `excludes` arrays to specify which files should be included or excluded from operations.
- **Changing Access Settings**: Modify the `access` section to enable or disable remote access and change the port number.

## Example Configuration
Here is an example of a more complex configuration file:

```toml
# xported.toml
# This file is used to store the configuration for the xported CLI.

schema = "v1" # The schema version of the configuration file.

[owner]
name = "Your Name"
email = "example@email.com"

[[contributors]]
name = "Contributor Name"
email = "contributor@email.com"

[files]
includes = ["*.txt", "src/*.js", "main.cpp"]
excludes = ["*.log", "*.tmp"]

[access.http]
enabled = true
port = 8080
```

## Next Steps
Now that you have a basic understanding of the configuration file, you can explore specific commands in detail. Check out the [Usage](usage.md) section for more information on how to use the CLI effectively, and the [Development](development.md) section if you're interested in contributing to XPorted.