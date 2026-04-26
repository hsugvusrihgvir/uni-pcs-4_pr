#ifndef DOC_FACTORY_H
#define DOC_FACTORY_H

#include "DocumentModel.h"

#include <string>

class DocFactory {
public:
    static ProjectD createProjectDoc(const std::string& projectName);
    static FileD createFileDoc(const std::string& fileName, const std::string& filePath);
    static ClassD createClassDoc(const std::string& className, const std::string& description);
    static FunctionD createFunctionDoc(const std::string& functionName,
                                       const std::string& returnType,
                                       const std::string& parameters,
                                       const std::string& description);
};

#endif
