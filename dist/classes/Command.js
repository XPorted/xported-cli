class Command {
    constructor(name, description, args, action) {
        this.name = name;
        this.description = description;
        this.args = args;
        this.action = action;
        this.name = name;
        this.description = description;
        this.args = args;
        this.action = action;
    }
    ;
    execute(rawArgs) {
        const args = [];
        this.action(args);
    }
    ;
}
;
export default Command;
export { Command };
