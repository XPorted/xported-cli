export async function importCommand(commandName) {
    try {
        // Try .js extension first (for production/compiled code)
        return await import(`../commands/${commandName}.js`).then(m => m.default);
    }
    catch (error) {
        try {
            // Try .ts extension (for development environment)
            return await import(`../commands/${commandName}.ts`).then(m => m.default);
        }
        catch (innerError) {
            throw new Error(`Command module '${commandName}' not found`);
        }
        ;
    }
    ;
}
;
