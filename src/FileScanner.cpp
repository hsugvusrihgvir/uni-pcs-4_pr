#include "FileScanner.h"

#include <algorithm>
#include <stdexcept>

std::vector<std::filesystem::path> FileScanner::scan(const std::string& inputPath) const {
    namespace fs = std::filesystem;

    fs::path directory(inputPath);

    if (!fs::exists(directory)) {
        throw std::runtime_error("Input directory does not exist");
    }

    if (!fs::is_directory(directory)) {
        throw std::runtime_error("Input path is not a directory");
    }

    std::vector<fs::path> files;

    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        auto pathString = entry.path().string();

        if (pathString.find("build") != std::string::npos ||
            pathString.find("cmake-build-debug") != std::string::npos) {
            continue;
        }

        auto extension = entry.path().extension().string();

        if (extension == ".cpp" || extension == ".h") {
            files.push_back(entry.path());
        }
    }

    std::sort(files.begin(), files.end());
    return files;
}