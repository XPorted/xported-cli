
import fs from 'fs';
import path from 'path';

import { Command } from '../classes/Command.js';
import { findInit } from '../utils/FindInit.js';

const Init = new Command({
	name: 'init',
	category: 'general',
	description: 'Initializes a new XPorted directory.',
	methods: '*',
	parameters: [
		{
			name: 'force',
			description: 'Force initialization even if the directory exists.',
			type: 'parameter',
			required: false
		}
	],
	action: (method, parameters) => {
		const directoryPath = !method ? process.env['INIT_CWD'] : path.resolve(process.cwd(), method);
		console.log(`Initializing XPorted directory at ${directoryPath}`);

		// Check if the directory exists
		if (!fs.existsSync(directoryPath)) {
			// If the directory does not exist, create it
			try {
				fs.mkdirSync(directoryPath, { recursive: true });
			} catch (error) {
				console.error(`Error creating directory: ${error.message}`);
				return process.exit(1);
			};
		};

		const force = parameters.find(param => param.name === 'force');

		// Check if the is already an XPorted directory
		const initPath = findInit(directoryPath);
		if (initPath !== '' && !force) {
			// If the directory already exists and force is not set, exit with an error
			console.error(`XPorted configuration already exists at ${initPath}`);
			console.error('Use --force to overwrite the existing configuration.');
			return process.exit(1);
		};

		// Proceed with initialization logic here
		// Create the .xported file
		const xportedPath = path.join(directoryPath, '.xported');
		try {
			fs.writeFileSync(xportedPath, `# .xported
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
port = 8080`, {
				encoding: 'utf8',
				flag: force ? 'w' : 'wx' // Overwrite if force is set, fail if file exists otherwise
			});
			console.log(`XPorted directory initialized successfully at ${xportedPath}`);
			console.log('You can now start using XPorted CLI commands.');
			console.log('For more information, our github page is available at: https://github.com/XPorted/xported-cli/');
		} catch (error) {
			console.error(`Error creating .xported file: ${error.message}`);
			return process.exit(1);
		};
	}
});

export default Init;