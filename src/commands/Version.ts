
import fs from 'fs';
import path from 'path';
import term from 'terminal-kit';

import { Command } from '../classes/Command.js';

const packageJsonPath = path.resolve('package.json'); // Relative to the root of the project
const packageJson = JSON.parse(fs.readFileSync(packageJsonPath, 'utf8'));
const version = packageJson.version;

const terminal = term.terminal;

const Version = new Command({
	name: 'version',
	category: 'general',
	description: 'Show xported-cli version',
	methods: [],
	parameters: [],
	action: () => {
		terminal('XPorted CLI version: ');
		terminal.bold(version);
		terminal('\n');
	}
});

export default Version;