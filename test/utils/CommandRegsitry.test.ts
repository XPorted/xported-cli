import CommandRegistry from '../../src/utils/CommandRegistry.js';
import { jest } from '@jest/globals';

import fs from 'fs';
import path from 'path';

describe('CommandRegistry', () => {
	test('should be a Map', () => {
		expect(CommandRegistry).toBeInstanceOf(Map);
	});

	test('should contain all commands', () => {
		const commandsPath = path.resolve('src/commands'); // Relative to the root of the project
		const commandFiles: string[] = [];

		// Read all files in the commands directory, including subdirectories
		const readFilesRecursively = (dir) => {
			const files = fs.readdirSync(dir);
			for (const file of files) {
				if (fs.statSync(path.join(dir, file)).isDirectory()) // If the file is a directory, read it recursively
					readFilesRecursively(path.join(dir, file));
				else if (file.endsWith('.ts')) // If the file is a TypeScript file and not a test file
					commandFiles.push(path.join(dir, file));
			};
		};
		readFilesRecursively(commandsPath);

		for (const file of commandFiles) {
			const command = require(file);
			expect(CommandRegistry.has(command.default.name)).toBe(true);
		};
		expect(CommandRegistry.size).toBe(commandFiles.length);
	});
});