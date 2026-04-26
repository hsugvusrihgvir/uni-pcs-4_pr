#include "CodeParser.h"

#include "DocFactory.h"

#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>

ProjectD CodeParser::parse(const std::vector<std::filesystem::path>& files,
                           const std::string& projectName) const {
    ProjectD project = DocFactory::createProjectDoc(projectName);

    for (const auto& filePath : files) {
        project.addFile(parseFile(filePath));
    }

    return project;
}

FileD CodeParser::parseFile(const std::filesystem::path& filePath) const {
    std::ifstream input(filePath);
    if (!input.is_open()) {
        throw std::runtime_error("Cannot read file: " + filePath.string());
    }

    FileD fileDoc = DocFactory::createFileDoc(filePath.filename().string(), filePath.string());

    std::regex classRegex(R"(^\s*(class|struct)\s+([A-Za-z_][A-Za-z0-9_]*)\b)");
    std::regex functionRegex(R"(^\s*([A-Za-z_][A-Za-z0-9_:<>~*&\s]*)\s+([A-Za-z_][A-Za-z0-9_:~]*)\s*\(([^;{}]*)\)\s*(const)?\s*(\{|;)?\s*$)");

    std::string line;
    std::string pendingComment;
    bool inBlockComment = false;
    std::ostringstream blockComment;

    while (std::getline(input, line)) {
        std::string trimmed = trim(line);

        if (inBlockComment) {
            const std::size_t endPos = trimmed.find("*/");
            if (endPos != std::string::npos) {
                blockComment << cleanCommentLine(trimmed.substr(0, endPos));
                pendingComment = trim(blockComment.str());
                blockComment.str("");
                blockComment.clear();
                inBlockComment = false;
            } else {
                blockComment << cleanCommentLine(trimmed) << " ";
            }
            continue;
        }

        if (trimmed.rfind("///", 0) == 0) {
            if (!pendingComment.empty()) {
                pendingComment += " ";
            }
            pendingComment += trim(trimmed.substr(3));
            continue;
        }

        const std::size_t blockStart = trimmed.find("/**");
        if (blockStart != std::string::npos) {
            const std::size_t blockEnd = trimmed.find("*/", blockStart + 3);
            if (blockEnd != std::string::npos) {
                pendingComment = cleanCommentLine(trimmed.substr(blockStart + 3, blockEnd - blockStart - 3));
            } else {
                inBlockComment = true;
                blockComment << cleanCommentLine(trimmed.substr(blockStart + 3)) << " ";
            }
            continue;
        }

        std::smatch match;
        if (std::regex_search(line, match, classRegex)) {
            fileDoc.classes.push_back(DocFactory::createClassDoc(match[2].str(), pendingComment));
            pendingComment.clear();
            continue;
        }

        if (trimmed.find("if") == 0 || trimmed.find("for") == 0 || trimmed.find("while") == 0 ||
            trimmed.find("switch") == 0 || trimmed.find("return") == 0) {
            continue;
        }

        if (std::regex_search(line, match, functionRegex)) {
            std::string returnType = trim(match[1].str());
            std::string functionName = trim(match[2].str());
            std::string parameters = trim(match[3].str());

            if (!functionName.empty() && functionName.find("::") == std::string::npos) {
                fileDoc.functions.push_back(
                    DocFactory::createFunctionDoc(functionName, returnType, parameters, pendingComment));
            } else {
                fileDoc.functions.push_back(
                    DocFactory::createFunctionDoc(functionName, returnType, parameters, pendingComment));
            }
            pendingComment.clear();
        }
    }

    return fileDoc;
}

std::string CodeParser::trim(const std::string& value) const {
    const std::size_t first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

std::string CodeParser::cleanCommentLine(const std::string& line) const {
    std::string result = trim(line);
    if (!result.empty() && result[0] == '*') {
        result = trim(result.substr(1));
    }
    return result;
}
