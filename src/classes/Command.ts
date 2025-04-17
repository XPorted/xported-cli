
type Parameter = {
	name: string;
	description: string;
	type: 'parameter';
	required: boolean;
};

type ValuedParameter = {
	name: string;
	description: string;
	type: 'valuedParameter';
	value?: string;
	required: boolean;
};

type Parameters = Array<Parameter | ValuedParameter>;

type CommandOptions = {
	name: string;
	category: 'general';
	description: string;
	methods: string[];
	parameters: Parameters;

	action: (option: string, parameters: Parameters) => void | Promise<void>;
};

class Command {
	name: string;
	category: 'general';
	description: string;
	methods: string[];
	parameters: Parameters;
	private action: (option: string, parameters: Parameters) => void | Promise<void>;

	constructor(
		public command: CommandOptions = {
			name: '',
			category: 'general',
			description: '',
			methods: [],
			parameters: [],
			action: () => { }
		}
	) {
		this.name = command.name;
		this.category = command.category;
		this.description = command.description;
		this.methods = command.methods;
		this.parameters = command.parameters;

		this.action = command.action;
	};

	execute(rawArgs: string[]) {
		// Parse the raw parameters to extract methods and parameters
		// If the command has requires a method, get the first argument
		// and check if it is in the methods array
		let method = '';
		if (this.methods.length > 0) {
			method = rawArgs[0];
			// Check if the method exists in the methods array
			if (!method) {
				console.error(`A method is required for the command "${this.name}".`);
				process.exit(1);
			};
			// Check if the method is valid:
			// it should be in the methods array;
			// it should not start with '--';
			// and it should not be empty
			if (
				!this.methods.includes(method) ||
				method.startsWith('--')
			) {
				console.error(`Invalid method "${method}" for the command "${this.name}".`);
				process.exit(1);
			};

			// Remove the method from the raw arguments
			rawArgs = rawArgs.slice(1);
		};

		// Parse the parameters
		const parameters: Parameters = [];
		let i = 0;
		while (i < this.parameters.length) {
			const parameter = this.parameters[i];

			// Check the parameter type
			if (parameter.type === 'parameter') {
				// Find the parameter in the raw arguments
				const paramIndex = rawArgs.findIndex(arg => arg === `--${parameter.name}`);
				if (paramIndex !== -1) {
					// If the parameter is found, remove it from the raw arguments
					rawArgs.splice(paramIndex, 1);
					// Add the parameter to the parameters array
					parameters.push(parameter);
				} else if (parameter.required) {
					// If the parameter is required and not found, show an error
					console.error(`Missing required parameter "--${parameter.name}" for the command "${this.name}".`);
					process.exit(1);
				};
			} else if (parameter.type === 'valuedParameter') {
				// Find the parameter in the raw arguments
				const paramIndex = rawArgs.findIndex(arg => arg.startsWith(`--${parameter.name}`));
				if (paramIndex !== -1) {
					// If the parameter is found, remove it from the raw arguments
					const paramValue = rawArgs[paramIndex + 1];
					if (!paramValue) {
						console.error(`Missing value for parameter "--${parameter.name}" for the command "${this.name}".`);
						process.exit(1);
					};
					rawArgs.splice(paramIndex, 2);
					// Add the parameter to the parameters array
					parameters.push({
						...parameter,
						value: paramValue
					});
				} else if (parameter.required) {
					// If the parameter is required and not found, show an error
					console.error(`Missing required parameter "--${parameter.name}" for the command "${this.name}".`);
					process.exit(1);
				};
			};
			i++;
		};
		this.action(method, parameters);
	};
};

export default Command;
export { Command };
export type { CommandOptions, Parameters, ValuedParameter, Parameter };