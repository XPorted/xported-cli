import Help from '../../src/commands/Help.js';
import { jest } from '@jest/globals';

describe('Help Valid Command', () => {
	test('should have correct name and description', () => {
		expect(Help.name).toBe('help');
		expect(Help.description).toContain('help');
		expect(Help.category).toBe('general');
	});

	test('should output help information when executed', async () => {
		// Mock console.log
		const consoleSpy = jest.spyOn(console, 'log').mockImplementation(() => { });

		// Execute the command
		await Help.execute([]);

		// Check that console.log was called with help info
		expect(consoleSpy).toHaveBeenCalled();
		expect(consoleSpy.mock.calls[0][0]).toMatch(/Usage: xported-cli <command> \[options\]/);

		// Restore console.log
		consoleSpy.mockRestore();
	});

	test('should output help information for a specific command', async () => {
		// Mock console.log
		const consoleSpy = jest.spyOn(console, 'log').mockImplementation(() => { });

		// Execute the command with a specific command name
		await Help.execute(['--command', 'version']);

		// Check that console.log was called with specific command info
		expect(consoleSpy).toHaveBeenCalled();
		expect(consoleSpy.mock.calls[0][0]).toMatch(/version - Show xported-cli version./);

		// Restore console.log
		consoleSpy.mockRestore();
	});
});

describe('Help Invalid Command', () => {
	test('should handle command not found', async () => {
		const exitSpy = jest.spyOn(process, 'exit').mockImplementation(() => {
			return undefined as never;
		});

		await Help.execute(['--command', 'nonexistent']);

		expect(exitSpy).toHaveBeenCalledWith(1);
		exitSpy.mockRestore();
	});
});