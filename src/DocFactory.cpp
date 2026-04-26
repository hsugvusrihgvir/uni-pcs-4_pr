#include "DocFactory.h"

ProjectD DocFactory::createProjectDoc(const std::string& projectName) {
    ProjectD project;
    project.projectName = projectName;
    return project;
}

FileD DocFactory::createFileDoc(const std::string& fileName, const std::string& filePath) {
    FileD file;
    file.fileName = fileName;
    file.filePath = filePath;
    return file;
}

ClassD DocFactory::createClassDoc(const std::string& className, const std::string& description) {
    ClassD classDoc;
    classDoc.className = className;
    classDoc.description = description;
    return classDoc;
}

FunctionD DocFactory::createFunctionDoc(const std::string& functionName,
                                        const std::string& returnType,
                                        const std::string& parameters,
                                        const std::string& description) {
    FunctionD function;
    function.functionName = functionName;
    function.returnType = returnType;
    function.parameters = parameters;
    function.description = description;
    return function;
}
