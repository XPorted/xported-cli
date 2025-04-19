import findInit from '../../src/utils/FindInit.js';
import { jest } from '@jest/globals';

import fs from 'fs';
import path from 'path';

describe('FindInit', () => {
	test('should be able to find the .xported init file', () => {
		const directoryPath = '/tmp/xported-cli-test';

		// Clean up before test
		if (fs.existsSync(directoryPath))
			fs.rmdirSync(directoryPath, { recursive: true });
		fs.mkdirSync(directoryPath, { recursive: true });

		const filePath = path.join(directoryPath, '.xported');
		fs.writeFileSync(filePath, 'test content');
		expect(fs.readFileSync(filePath, 'utf8')).toBe('test content'); // To ensure the file was created correctly

		const foundFile = findInit(directoryPath);
		expect(foundFile).toBe(filePath);

		// Clean up after test
		fs.unlinkSync(filePath);
		fs.rmdirSync(directoryPath, { recursive: true });
	});

	test('should return an empty string if no .xported file is found', () => {
		const directoryPath = '/tmp/xported-cli-test';

		// Clean up before test
		if (fs.existsSync(directoryPath))
			fs.rmdirSync(directoryPath, { recursive: true });
		fs.mkdirSync(directoryPath, { recursive: true });

		const foundFile = findInit(directoryPath);
		expect(foundFile).toBe('');


		fs.rmdirSync(directoryPath, { recursive: true });
	});
});