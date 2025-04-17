
import { Command } from '../classes/Command.js';

/**
 * CommandRegistry is a map that stores all the commands available in the application.
 */
const CommandRegistry = new Map<string, Command>();

// Import all commands
import Version from '../commands/Version.js'; CommandRegistry.set(Version.name, Version);
import Help from '../commands/Help.js'; CommandRegistry.set(Help.name, Help);

export default CommandRegistry;