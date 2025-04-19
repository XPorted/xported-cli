
import { Command } from '../classes/Command.js';

/**
 * CommandRegistry is a map that stores all the commands available in the application.
 */
const CommandRegistry = new Map<string, Command>();

// Import all commands
import Version from '../commands/Version.js'; CommandRegistry.set(Version.name, Version);
import Help from '../commands/Help.js'; CommandRegistry.set(Help.name, Help);
import Init from '../commands/Init.js'; CommandRegistry.set(Init.name, Init);
import Http from '../commands/Hosting/Http.js'; CommandRegistry.set(Http.name, Http);

export default CommandRegistry;