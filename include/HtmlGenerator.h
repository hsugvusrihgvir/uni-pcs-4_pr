#ifndef HTML_GENERATOR_H
#define HTML_GENERATOR_H

#include "DocumentModel.h"
#include "HtmlGenerationStrategy.h"

#include <memory>
#include <string>

class HtmlGenerator {
public:
    HtmlGenerator();
    void setStrategy(std::unique_ptr<HtmlGenerationStrategy> newStrategy);
    void generate(const ProjectD& project, const std::string& outputPath) const;

private:
    std::unique_ptr<HtmlGenerationStrategy> strategy;
};

#endif
