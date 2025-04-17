import fs from 'fs';
import path from 'path';
import { Command } from '../classes/Command.js';
const packageJsonPath = path.join(path.resolve(), 'package.json');
const packageJson = JSON.parse(fs.readFileSync(packageJsonPath, 'utf8'));
const version = packageJson.version;
const command = new Command('version', 'Print the version of the application', [], () => {
    console.log(`Version: ${version}`);
});
export default command;
