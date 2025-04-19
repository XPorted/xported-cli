
import term from 'terminal-kit';

import { Command, ValuedParameter } from '../classes/Command.js';

const terminal = term.terminal;

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
			terminal.bold('Usage: ').cyan('xported-cli ').cyan('<command> ').cyan('[options]\n\n');
			terminal.bold('Commands:\n');

			const categorizedCommands = new Map<string, Command[]>();
			for (const [name, command] of CommandRegistry) {
				if (!categorizedCommands.has(command.category))
					categorizedCommands.set(command.category, []);
				categorizedCommands.get(command.category)?.push(command);
			};

			for (const [category, commands] of categorizedCommands) {
				terminal.yellow(`\t${category}:\n`);
				for (const command of commands) {
					terminal.cyan(`\t\t${command.name}`).gray(` - ${command.description}.\n`);
				};
				terminal('\n');
			};

			terminal.bold('Use "').cyan('xported-cli help --command <command>').bold('" for more information on a specific command.\n');
		} else {
			const commandName = commandParameter.value;
			const commandInfo = CommandRegistry.get(commandName);

			if (!commandInfo) {
				terminal.red(`Command "${commandName}" not found.\n`);
				return process.exit(1);
			};

			terminal.bold.cyan(`${commandInfo.name}`).gray(` - ${commandInfo.description}.\n`);
			if (commandInfo.methods === '*')
				commandInfo.methods = [];
			if (commandInfo.methods.length > 0) {
				terminal('\n');
				terminal.bold('Methods:\n');
				for (const method of commandInfo.methods)
					terminal.yellow(`\t${method}\n`);
			};
			if (commandInfo.parameters.length > 0) {
				terminal('\n');
				terminal.bold('Parameters:\n');
				for (const parameter of commandInfo.parameters) {
					if (parameter.type === 'valuedParameter') {
						terminal.cyan(`\t--${parameter.name} <${parameter.name}>`).gray(` - ${parameter.description}.\n`);
					} else {
						terminal.cyan(`\t--${parameter.name}`).gray(` - ${parameter.description}.\n`);
					};
				};
			};

			terminal('\n');
			terminal.bold('Usage:\n');
			terminal.cyan(`\txported-cli ${commandInfo.name}${commandInfo.methods.length > 0 ? ' <method>' : ''}${commandInfo.parameters.length > 0 ? ' [parameters]' : ''}\n`);

			terminal('\n');
			terminal.bold('Use "').cyan('xported-cli help').bold('" to see all commands.\n');
		};
	}
});

export default Help;