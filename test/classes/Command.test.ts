import Command from '../../src/classes/Command';
import { jest } from '@jest/globals';

describe('Command Class', () => {
	const command = new Command({
		name: 'test',
		category: 'test',
		description: 'Test command',
		methods: ['method1', 'method2'],
		parameters: [
			{
				name: 'param1',
				description: 'Parameter 1',
				type: 'parameter',
				required: true
			},
			{
				name: 'param2',
				description: 'Parameter 2',
				type: 'valuedParameter',
				required: false
			}
		],
		action: (method, parameters, rawArguments) =>
			// Mock action function
			new Promise((resolve) => {
				resolve({ method, parameters, rawArguments });
			})
	});

	test('should have correct properties', () => {
		expect(command.name).toBe('test');
		expect(command.category).toBe('test');
		expect(command.description).toBe('Test command');
		expect(command.methods).toEqual(['method1', 'method2']);
		expect(command.parameters).toEqual([
			{
				name: 'param1',
				description: 'Parameter 1',
				type: 'parameter',
				required: true
			},
			{
				name: 'param2',
				description: 'Parameter 2',
				type: 'valuedParameter',
				required: false
			}
		]);
	});

	test('should execute action with correct parameters', async () => {
		const rawArguments = ['method1', '--param1'];
		const result = await command.execute(rawArguments);

		expect(result).toEqual({
			method: 'method1',
			parameters: [
				{ name: 'param1', description: 'Parameter 1', type: 'parameter', required: true }
			],
			rawArguments: []
		});
	});

	test('should `return process.exit(1)` when missing required parameters', async () => {
		const rawArguments = ['method1'];
		const exitSpy = jest.spyOn(process, 'exit').mockImplementation(code => {
			return undefined as never;
		});

		await command.execute(rawArguments);

		expect(exitSpy).toHaveBeenCalledWith(1);
		exitSpy.mockRestore();
	});
});