
import fs from 'fs';
import path from 'path';
import toml from 'toml';

// .xported file schema in JSON format
const schema = {
	schema: 'v1',
	owner: {
		name: '',
		email: ''
	},
	contributors: [
		{
			name: '',
			email: ''
		}
	],
	access: {
		http: {
			enabled: false,
			port: 8080
		}
	}
};

/**
 * Parses the .xported file and returns the configuration object.
 * @param {string} directoryPath - The path to the directory containing the .xported file.
 * @returns {object} The parsed configuration object.
 */
const parseInit = (directoryPath: string): typeof schema => {
    const filePath = path.join(directoryPath, '.xported');
    const fileContent = fs.readFileSync(filePath, 'utf-8');
	
	const parsedContent = toml.parse(fileContent);
	
	// Validate the parsed content against the schema
	const isValid = Object.keys(schema).every(key => {
		if (typeof parsedContent[key] !== typeof schema[key])
			return false;

		if (typeof parsedContent[key] === 'object')
			return Object.keys(schema[key]).every(subKey => {
				return typeof parsedContent[key][subKey] === typeof schema[key][subKey];
			});
		
		return true;
	});

	if (!isValid) {
		console.error('Invalid configuration format');
		return null;
	};

	return parsedContent;
};

export default parseInit;
export { parseInit };