
import fs from 'fs';
import path from 'path';

const checkFileExistance = (file: string): boolean => {
	try {
		return !!fs.readFileSync(file);
	} catch (error) {
		return false;
	};
};

/**
 * Finds the .xported init file in the given path or its parent directories.
 * 
 * @param {string} directoryPath - The path to search for the .xported init file.
 * @returns {string} - The path to the .xported init file or an empty string if not found.
 */
const findInit = (directoryPath: string): string => {
	// Loop through the directory and its parents to find the .xported init file
	let currentPath = directoryPath;
	while (currentPath !== '/') {
		const initPath = path.join(currentPath, '.xported');
		if (checkFileExistance(initPath))
			return initPath;
		currentPath = path.dirname(currentPath);
	};
	// If the .xported file is not found, return an empty string
	return '';
};

export default findInit;
export { findInit };