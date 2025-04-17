
import { Command, ValuedParameter } from '../classes/Command.js';

const Help = new Command({
	name: 'help',
	category: 'general',
	description: 'Show help for xported-cli',
	methods: [],
	parameters: [
		{
			name: 'command',
			description: 'The command to show help for',
			type: 'valuedParameter',
			required: false
		}
	],
	action: async (option, parameters, rawArguments) => {
		const CommandRegistry = (await import('../utils/CommandRegistry.js')).default;

		const commandParameter = parameters.find(param => param.name === 'command') as ValuedParameter | undefined;

		if (!commandParameter) {
			console.log('Usage: xported-cli <command> [options]');
			console.log();
			console.log('Commands:');

			const categorizedCommands = new Map<string, Command[]>();
			for (const [name, command] of CommandRegistry) {
				if (!categorizedCommands.has(command.category))
					categorizedCommands.set(command.category, []);
				categorizedCommands.get(command.category)?.push(command);
			};

			for (const [category, commands] of categorizedCommands) {
				console.log(`\t${category}:`);
				for (const command of commands) {
					console.log(`\t\t${command.name} - ${command.description}.`);
				};
				console.log();
			};

			console.log('Use "xported-cli help --command <command>" for more information on a specific command.');
		} else {
			const commandName = commandParameter.value;
			const commandInfo = CommandRegistry.get(commandName);

			if (!commandInfo) {
				console.error(`Command "${commandName}" not found.`);
				process.exit(1);
			};

			console.log(`${commandInfo.name} - ${commandInfo.description}.`);
			if (commandInfo.methods.length > 0) {
				console.log();
				console.log('Methods:');
				for (const method of commandInfo.methods)
					console.log(`\t${method}`);
			};
			if (commandInfo.parameters.length > 0) {
				console.log();
				console.log('Parameters:');
				for (const parameter of commandInfo.parameters) {
					if (parameter.type === 'valuedParameter') {
						console.log(`\t--${parameter.name} <${parameter.name}> - ${parameter.description}.`);
					} else {
						console.log(`\t--${parameter.name} - ${parameter.description}.`);
					};
				};
			};

			console.log();
			console.log('Usage:');
			console.log(`\txported-cli ${commandInfo.name}${commandInfo.methods.length > 0 ? ' <method>' : ''}${commandInfo.parameters.length > 0 ? ' [parameters]' : ''}`);

			console.log();
			console.log('Use "xported-cli help" to see all commands.');
		};
	}
});

export default Help;