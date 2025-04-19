
import fs from 'fs';
import path from 'path';
import term from 'terminal-kit';

import express from 'express';
import mimeTypes from 'mime-types';
import contentDisposition from 'content-disposition';

import { Command } from '../../classes/Command.js';
import findInit from '../../utils/FindInit.js';
import parseInit from '../../utils/ParseInit.js';
import { File, Directory } from '../../utils/MapDirectory.js';

const terminal = term.terminal;

const app = express();
app.use(express.json());
app.use(express.urlencoded({ extended: true, limit: '50mb' }));
app.use((req, res, next) => {
	// Set the headers to allow CORS
	res.header('Access-Control-Allow-Origin', '*');
	res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept');
	res.header('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE, OPTIONS');
	res.header('Access-Control-Expose-Headers', 'Content-Disposition');
	res.header('Access-Control-Allow-Credentials', 'true');
	res.header('Content-Type', 'application/json');
	res.header('Content-Disposition', 'inline');
	res.header('Accept-Ranges', 'bytes');
	res.header('Accept-Encoding', 'gzip, deflate, br');
	res.header('Vary', 'Accept-Encoding');
	res.header('X-Content-Type-Options', 'nosniff');
	next();
});

const Http = new Command({
	name: 'http',
	category: 'hosting',
	description: 'Start the xported host',
	methods: [],
	parameters: [],
	action: async () => {
		const directoryPath = process.env['INIT_CWD'];
		if (!directoryPath || directoryPath === '') {
			console.error('No directory path found');
			return process.exit(1);
		};

		const initPath = findInit(directoryPath);
		if (initPath === '') {
			console.error('No xported configuration found');
			console.error('Please run "xported-cli init" to initialize a new xported directory.');
			return process.exit(1);
		};
		const rootDirectory = path.dirname(initPath);;
		terminal(`XPorted starting in ${rootDirectory}\n`);

		// Load the xported configuration
		const config = parseInit(rootDirectory);
		if (!config) {
			console.error('Error loading xported configuration');
			return process.exit(1);
		};
		// Check if the http access is enabled
		if (!config.access.http.enabled) {
			console.error('HTTP access is not enabled in the xported configuration');
			return process.exit(1);
		};

		// Check if the port is valid
		if (isNaN(config.access.http.port) || config.access.http.port < 0 || config.access.http.port > 65535) {
			console.error('Invalid port number in the xported configuration');
			return process.exit(1);
		};
		// Check if the port is already in use
		const portInUse = await new Promise((resolve) => {
			const server = app.listen(config.access.http.port, () => {
				server.close();
				resolve(false);
			}).on('error', (err) => {
				if (err['code'] === 'EADDRINUSE') {
					resolve(true);
				} else {
					console.error(`Error starting server: ${err.message}`);
					resolve(false);
				};
			});
		});
		if (portInUse) {
			console.error(`Port ${config.access.http.port} is already in use`);
			return process.exit(1);
		};

		type HttpLog = {
			timestamp: string;
			duration: number;
			method: string;
			path: string;
			status: number;
		};
		const logs: HttpLog[] = [];

		const updateLogTable = () => {
			terminal.clear();
			terminal.cyan('XPorted is running on ').white.bold(`http://localhost:${config.access.http.port}\n`);

			// Limit the number of logs to the height of the terminal
			if (logs.length > terminal.height - 4) 
				logs.splice(0, logs.length - (terminal.height - 4));

			terminal.moveTo(1, 3);
			terminal.table([
				['Method', 'Timestamp', 'Duration', 'Path', 'Status'],
				...logs.map(log => [
					log.method,
					log.timestamp,
					log.duration ? `${log.duration} ms` : 'N/A',
					log.path,
					log.status
				]) as readonly string[][]
			], {
				hasBorder: false,
				firstRowTextAttr: {
					bold: true,
					underline: true,
				},
				firstColumnTextAttr: {
					bold: true
				},
				wordWrap: true
			});

			terminal.moveTo(1, terminal.height - 1);
			terminal.cyan('Press ').white.bold('Ctrl+C').cyan(' to stop the server.\n');
		};
		terminal.on('resize', updateLogTable);

		// Serve the directory
		// Get the path from <url>/<path>
		app.get(['/', '/*'], async (request, response) => {
			const urlPath = decodeURIComponent(request.path);
			const filePath = path.join(rootDirectory, urlPath);

			// Create log
			const log: HttpLog = {
				timestamp: new Date().toISOString(),
				duration: undefined,
				method: request.method,
				path: filePath,
				status: undefined
			};
			logs.push(log);
			updateLogTable();

			// Start the timer
			const start = Date.now();

			// Check if the file or directory exists
			if (!fs.existsSync(filePath)) {
				response.status(404).send('File or directory not found');
				log.status = 404;
				log.duration = Date.now() - start;
				updateLogTable();
				return;
			};

			// Check if the path is a directory or a file
			const stats = fs.statSync(filePath);
			if (stats.isDirectory()) {
				const contents: Array<Directory | File> = [];
				// Read the directory contents
				for (const content of fs.readdirSync(filePath))
					contents.push({
						name: content,
						type: fs.statSync(path.join(filePath, content)).isDirectory() ? 'directory' : 'file',
						children: undefined
					});
				// Send the directory contents as JSON
				response.header({
					'Content-Type': 'application/json',
					'Content-Disposition': 'inline'
				}).json(contents);

				log.status = 200;
				log.duration = Date.now() - start;
				updateLogTable();
			} else {
				const fileName = path.basename(filePath);
				const mimeType = mimeTypes.lookup(fileName) || 'application/octet-stream';
				// Send the file
				response.sendFile(filePath, {
					headers: {
						'Content-Type': mimeType,
						'Content-Disposition': contentDisposition(fileName, { type: 'inline' }),
						'Accept-Ranges': 'bytes',
						'Content-Length': stats.size
					},
					dotfiles: 'allow',
					etag: true
				});

				log.status = 200;
				log.duration = Date.now() - start;
				updateLogTable();
			};
		});

		// Start the server
		app.listen(config.access.http.port, () => {
			updateLogTable();
		});
	}
});

export default Http;