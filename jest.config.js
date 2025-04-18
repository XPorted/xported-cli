export default {
	preset: 'ts-jest',
	testEnvironment: 'node',
	extensionsToTreatAsEsm: ['.ts'],
	moduleNameMapper: {
		'^(\\.{1,2}/.*)\\.js$': '$1',
	},
	transform: {
		'^.+\\.tsx?$': ['ts-jest', {
			useESM: true,
			tsconfig: {
				// Explicitly set module format to support import.meta
				module: 'es2022'
			}
		}]
	}
};