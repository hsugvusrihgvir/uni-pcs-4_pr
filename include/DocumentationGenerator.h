#ifndef DOCUMENTATION_GENERATOR_H
#define DOCUMENTATION_GENERATOR_H

#include "CodeParser.h"
#include "FileScanner.h"
#include "HtmlGenerator.h"

#include <string>

class DocumentationGenerator {
public:
    static DocumentationGenerator& getInstance();

    DocumentationGenerator(const DocumentationGenerator&) = delete;
    DocumentationGenerator& operator=(const DocumentationGenerator&) = delete;

    void generate(const std::string& inputPath, const std::string& outputPath);

private:
    DocumentationGenerator() = default;

    FileScanner scanner;
    CodeParser parser;
    HtmlGenerator htmlGenerator;
};

#endif
