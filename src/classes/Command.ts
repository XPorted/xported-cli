
type Flag = {
	name: string;
	description: string;
	required: boolean;
};

type Option = {
	name: string;
	description: string;
	value: string;
	type: string;
	required: boolean;
};

type CommandArgs = Array<Flag | Option>;

class Command {
	constructor(
		public name: string,
		public description: string,
		public args: CommandArgs,
		public action: (args: CommandArgs) => void
	) {
		this.name = name;
		this.description = description;
		this.args = args;
		this.action = action;
	};

	execute(rawArgs: string[]) {
		const args: CommandArgs = [];
		this.action(args);
	};
};

export default Command;
export { Command };
export type { Flag, Option, CommandArgs };