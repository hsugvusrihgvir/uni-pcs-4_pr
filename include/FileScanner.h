#ifndef FILE_SCANNER_H
#define FILE_SCANNER_H

#include <filesystem>
#include <string>
#include <vector>

class FileScanner {
public:
    std::vector<std::filesystem::path> scan(const std::string& inputPath) const;
};

#endif
