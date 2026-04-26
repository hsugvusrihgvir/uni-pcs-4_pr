#include "FileScanner.h"

#include <algorithm>
#include <stdexcept>

std::vector<std::filesystem::path> FileScanner::scan(const std::string& inputPath) const {
    namespace fs = std::filesystem;

    fs::path root(inputPath);
    if (!fs::exists(root)) {
        throw std::runtime_error("Input directory does not exist: " + inputPath);
    }
    if (!fs::is_directory(root)) {
        throw std::runtime_error("Input path is not a directory: " + inputPath);
    }

    std::vector<fs::path> files;
    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        const std::string extension = entry.path().extension().string();
        if (extension == ".cpp" || extension == ".h") {
            files.push_back(entry.path());
        }
    }

    std::sort(files.begin(), files.end());
    return files;
}
