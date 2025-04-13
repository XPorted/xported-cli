#pragma once
#include <filesystem>
#include <string>

/**
 * @brief Find the initialization file in the given directory or its parent directories.
 */
std::string FindInit(const std::string &directory);