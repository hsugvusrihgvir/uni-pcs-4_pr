#ifndef CODE_PARSER_H
#define CODE_PARSER_H

#include "DocumentModel.h"

#include <filesystem>
#include <string>
#include <vector>

class CodeParser {
public:
    ProjectD parse(const std::vector<std::filesystem::path>& files,
                   const std::string& projectName) const;

private:
    FileD parseFile(const std::filesystem::path& filePath) const;
    std::string trim(const std::string& value) const;
    std::string cleanCommentLine(const std::string& line) const;
};

#endif
