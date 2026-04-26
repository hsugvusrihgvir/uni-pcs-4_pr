#ifndef HTML_GENERATION_STRATEGY_H
#define HTML_GENERATION_STRATEGY_H

#include "DocumentModel.h"

#include <string>

class HtmlGenerationStrategy {
public:
    virtual ~HtmlGenerationStrategy() = default;
    virtual std::string generate(const ProjectD& project) const = 0;
};

class SimpleHtmlStrategy : public HtmlGenerationStrategy {
public:
    std::string generate(const ProjectD& project) const override;
};

class DetailedHtmlStrategy : public HtmlGenerationStrategy {
public:
    std::string generate(const ProjectD& project) const override;
};

#endif
