
import fs from 'fs';
import path from 'path';


type File = {
	type: 'file';
	name: string;
};
type Directory = {
	type: 'directory';
	name: string;
	children: (File | Directory)[];
};

/**
 * Maps the directory structure to a tree-like object.
 * 
 * @param {string} dir - The directory to map.
 * @returns {Directory} The mapped directory structure.
 */
const mapDirectory = async (dir: string): Promise<Directory> => {
	const childNames = await fs.promises.readdir(dir);
	const childrenPromises = childNames.map(async (child): Promise<File | Directory> => {
		const childPath = path.join(dir, child);
		const stats = await fs.promises.stat(childPath);

		if (stats.isDirectory())
			return await mapDirectory(childPath);
		else
			return { type: 'file', name: child.split('/').pop() || '' } as File;
	});

	const children = await Promise.all(childrenPromises);
	return { type: 'directory', name: dir.split('/').pop() || '', children };
};

export default mapDirectory;
export { mapDirectory };
export type { File, Directory };