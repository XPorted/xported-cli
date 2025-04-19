import Init from '../../src/commands/Init.js';
import { jest } from '@jest/globals';

import fs from 'fs';
import path from 'path';

describe('Init Command', () => {
	test('should have correct name and description', () => {
		expect(Init.name).toBe('init');
		expect(Init.description).toContain('Initializes');
		expect(Init.category).toBe('general');
	});

	test('should create a .xported file', () => {
		const directoryPath = '/tmp/xported-cli-test';

		// Clean up before test
		if (fs.existsSync(directoryPath))
			fs.rmdirSync(directoryPath, { recursive: true });

		fs.mkdirSync(directoryPath, { recursive: true });
		Init.execute([directoryPath]);

		const filePath = path.join(directoryPath, '.xported');
		expect(fs.existsSync(filePath)).toBe(true);
		expect(fs.readFileSync(filePath, 'utf8')).toContain('xported');

		// Clean up after test
		fs.unlinkSync(filePath);
		fs.rmdirSync(directoryPath, { recursive: true });
	});

	test('should overide existing .xported file if --force is used', () => {
		const directoryPath = '/tmp/xported-cli-test';

		// Clean up before test
		if (fs.existsSync(directoryPath))
			fs.rmdirSync(directoryPath, { recursive: true });
		fs.mkdirSync(directoryPath, { recursive: true });

		const filePath = path.join(directoryPath, '.xported');
		fs.writeFileSync(filePath, 'test content');
		expect(fs.readFileSync(filePath, 'utf8')).toBe('test content'); // To ensure the file was created correctly

		Init.execute([directoryPath, '--force']);

		expect(fs.readFileSync(filePath, 'utf8')).toContain('xported');
		expect(fs.readFileSync(filePath, 'utf8')).not.toBe('test content'); // To ensure the file was overridden

		// Clean up after test
		fs.unlinkSync(filePath);
		fs.rmdirSync(directoryPath, { recursive: true });
	});

	test('should exit and not overide existing .xported file if --force is not used', () => {
		const directoryPath = '/tmp/xported-cli-test';

		// Clean up before test
		if (fs.existsSync(directoryPath))
			fs.rmdirSync(directoryPath, { recursive: true });
		fs.mkdirSync(directoryPath, { recursive: true });
		const filePath = path.join(directoryPath, '.xported');
		fs.writeFileSync(filePath, 'test content');
		expect(fs.readFileSync(filePath, 'utf8')).toBe('test content'); // To ensure the file was created correctly

		const exitSpy = jest.spyOn(process, 'exit').mockImplementation(() => {
			return undefined as never;
		});

		Init.execute([directoryPath]);
		expect(exitSpy).toHaveBeenCalledWith(1);
		expect(fs.readFileSync(filePath, 'utf8')).toBe('test content'); // To ensure the file was not overridden
		exitSpy.mockRestore();

		// Clean up after test
		fs.unlinkSync(filePath);
		fs.rmdirSync(directoryPath, { recursive: true });
	});
});