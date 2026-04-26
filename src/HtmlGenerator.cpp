#include "HtmlGenerator.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

HtmlGenerator::HtmlGenerator()
    : strategy(std::make_unique<DetailedHtmlStrategy>()) {}

void HtmlGenerator::setStrategy(std::unique_ptr<HtmlGenerationStrategy> newStrategy) {
    if (!newStrategy) {
        throw std::runtime_error("HTML generation strategy is not set");
    }
    strategy = std::move(newStrategy);
}

void HtmlGenerator::generate(const ProjectD& project, const std::string& outputPath) const {
    namespace fs = std::filesystem;

    fs::path outputDirectory(outputPath);
    fs::create_directories(outputDirectory);

    fs::path outputFile = outputDirectory / "index.html";
    std::ofstream output(outputFile);
    if (!output.is_open()) {
        throw std::runtime_error("Cannot save HTML file: " + outputFile.string());
    }

    output << strategy->generate(project);
}
