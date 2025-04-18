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
		const commandFiles = fs.readdirSync(commandsPath).filter(file => file.endsWith('.ts') || file.endsWith('.js'));
		
		for (const file of commandFiles) {
			const command = require(path.join(commandsPath, file));
			expect(CommandRegistry.has(command.default.name)).toBe(true);
		};
		expect(CommandRegistry.size).toBe(commandFiles.length);
	});
});