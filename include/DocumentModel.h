#ifndef DOCUMENT_MODEL_H
#define DOCUMENT_MODEL_H

#include <string>
#include <vector>

struct FunctionD {
    std::string functionName;
    std::string returnType;
    std::string parameters;
    std::string description;
};

struct ClassD {
    std::string className;
    std::string description;
    std::vector<FunctionD> methods;
};

struct FileD {
    std::string fileName;
    std::string filePath;
    std::vector<ClassD> classes;
    std::vector<FunctionD> functions;
};

struct ProjectD {
    std::string projectName;
    std::vector<FileD> files;

    void addFile(const FileD& fileDoc);
};

#endif
