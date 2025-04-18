
import fs from 'fs';
import path from 'path';

import { Command } from '../classes/Command.js';

const packageJsonPath = path.resolve('package.json'); // Relative to the root of the project
const packageJson = JSON.parse(fs.readFileSync(packageJsonPath, 'utf8'));
const version = packageJson.version;

const Version = new Command({
	name: 'version',
	category: 'general',
	description: 'Show xported-cli version',
	methods: [],
	parameters: [],
	action: () => {
		console.log(`Version: ${version}`);
	}
});

export default Version;