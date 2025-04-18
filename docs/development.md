# Development

## Contributing to XPorted
XPorted is an open-source project, and we welcome contributions from the community. Whether you're fixing bugs, adding new features, or improving documentation, your help is appreciated!

## Project Structure
The XPorted project is organized into several directories, each serving a specific purpose:
```
xported-cli/
 ├── docs/
 ├── manuals/
 ├── src/
 │ 	├── index.ts # Main entry point
 │ 	├── classes/
 │ 	├── commands/
 │ 	└── utils/
 ├── tests/
 ├── .eslintrc
 ├── .gitignore
 ├── .prettierrc
 ├── jest.config.js
 ├── LICENSE
 ├── package-lock.json
 ├── package.json
 ├── README.md
 ├── tsconfig.json
 └── tsconfig.test.json
```

## Setting Up the Development Environment
### Prerequisites
- Node.js (>= 14.x)
- npm (>= 6.x)
- Git (optional, for cloning the repository)
- A terminal or command prompt
### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/XPorted/xported-cli.git

   cd xported-cli
   ```
2. Install the dependencies:
   ```bash
   npm install
   ```
3. Build the project:
   ```bash
   npm run build
   ```
### Running
After building the project, you can run it using:
```bash
npm run start
```
### Running Tests
XPorted uses Jest for testing. To run the tests, use:
```bash
npm test
```

## Command Structure
### Adding a New Command
To add a new command, create a new file in the `src/commands/` directory. The file should export an instance of the `Command` class. Here's a basic example:
```ts
import fs from 'fs';
import path from 'path';

import { Command } from '../classes/Command.js';

const Test = new Command({
	name: 'test',
	category: 'general',
	description: 'This is a test command',
	methods: [],
	parameters: [],
	action: (method, parameters, rawArguments) => {
		console.log('This is a test command');
	}
});

export default Test;
```
### Command Structure
The command structure consists of the following properties:
- `name`: The name of the command.
- `category`: The category of the command (e.g., general, file management).
- `description`: A brief description of what the command does.
- `methods`: An array of methods that the command supports (e.g., create, delete, update). It can be empty if the command doesn't support any methods. Or it can be a wildcard `*` to support all methods.
- `parameters`: An array of parameters that the command accepts. Each parameter can have a name, type, and description.
- `action`: A function that defines what the command does when executed. This function can accept parameters and return a value.
### Command Registry
The command registry is responsible for managing all the commands in the project. It is located in `src/utils/CommandRegistry.ts`. You can add new commands to the registry by importing them and adding them to the `commands` array. Here's an example:
```ts
import Test from '../commands/Test.js'; CommandRegistry.set(Test.name, Test);
```

## Create a Pull Request
1. Fork the repository.
2. Create a new branch for your changes:
   ```bash
   git checkout -b my-feature-branch
   ```
3. Make your changes and commit them:
   ```bash
   git commit -m "Add my feature"
   ```
4. Push your changes to your fork:
   ```bash
   git push origin my-feature-branch
   ```
5. Create a pull request against the main branch of the original repository.
6. Provide a clear description of your changes and why they are needed.

## License
XPorted is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.