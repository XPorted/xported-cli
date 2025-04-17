#!/usr/bin/env node
import CommandRegistry from './utils/CommandRegistry.js';
const args = process.argv.slice(2);
const commandName = args[0];
const commandArgs = args.slice(1);
const command = CommandRegistry.get(commandName);
if (!command) {
    console.error(`Command "${commandName}" not found.`);
    process.exit(1);
}
;
command.execute(commandArgs);
