import Version from '../../src/commands/Version.js';
import { jest } from '@jest/globals';

describe('Version Command', () => {
	test('should have correct name and description', () => {
		expect(Version.name).toBe('version');
		expect(Version.description).toContain('version');
		expect(Version.category).toBe('general');
	});

	test('should output version when executed', async () => {
		// Mock console.log
		const consoleSpy = jest.spyOn(console, 'log').mockImplementation(() => {});

		// Execute the command
		await Version.execute([]);

		// Check that console.log was called with version info
		expect(consoleSpy).toHaveBeenCalled();
		expect(consoleSpy.mock.calls[0][0]).toMatch(/Version: \d+\.\d+\.\d+/);

		// Restore console.log
		consoleSpy.mockRestore();
	});
});