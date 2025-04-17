#!/usr/bin/env node
import { importCommand } from './utils/importHelper.js';
// Initialize empty registry
const CommandRegistry = {};
// Load commands dynamically
try {
    CommandRegistry['version'] = await importCommand('Version');
    // Add more commands as needed
}
catch (error) {
    console.error('Failed to load command:', error);
}
;
const args = process.argv.slice(2);
const commandName = args[0];
const commandArgs = args.slice(1);
const command = CommandRegistry[commandName];
if (!command) {
    console.error(`Command "${commandName}" not found.`);
    process.exit(1);
}
;
// Execute the command
try {
    command.execute(commandArgs);
}
catch (error) {
    console.error(`Failed to execute command "${commandName}":`, error);
    process.exit(1);
}
;
