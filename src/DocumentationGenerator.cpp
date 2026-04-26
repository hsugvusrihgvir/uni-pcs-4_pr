#include "DocumentationGenerator.h"

#include <filesystem>
#include <iostream>
#include <stdexcept>

DocumentationGenerator& DocumentationGenerator::getInstance() {
    static DocumentationGenerator instance;
    return instance;
}

void DocumentationGenerator::generate(const std::string& inputPath, const std::string& outputPath) {
    namespace fs = std::filesystem;

    std::cout << "Start documentation generation" << std::endl;

    const auto files = scanner.scan(inputPath);
    if (files.empty()) {
        throw std::runtime_error("No .cpp or .h files found in input directory");
    }

    std::string projectName = fs::path(inputPath).filename().string();
    if (projectName.empty()) {
        projectName = "C++ Project";
    }

    ProjectD project = parser.parse(files, projectName);
    htmlGenerator.generate(project, outputPath);

    std::cout << "Documentation generated successfully" << std::endl;
    std::cout << "Output directory: " << outputPath << std::endl;
}
