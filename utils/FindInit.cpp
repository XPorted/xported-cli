#include "utils/FindInit.hpp"

#include <filesystem>
#include <iostream>
#include <string>

std::string FindInit(const std::string &directory) {
	std::filesystem::path dirPath(directory);

	// Check if the directory exists
	if (!std::filesystem::exists(dirPath)) {
		return "";
	};

	// Traverse up to the ~/ directory
	while (dirPath != dirPath.root_path()) {
		// Check if the init file exists in the current directory
		std::filesystem::path initFilePath = dirPath / ".xported";
		if (std::filesystem::exists(initFilePath)) {
			return initFilePath.string();
		};

		// Move to the parent directory
		dirPath = dirPath.parent_path();
	};

	return "";
}