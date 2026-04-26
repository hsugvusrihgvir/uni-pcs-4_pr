#include "HtmlGenerationStrategy.h"

#include <sstream>

namespace {
std::string escapeHtml(const std::string& text) {
    std::string result;
    for (char ch : text) {
        switch (ch) {
            case '&': result += "&amp;"; break;
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '"': result += "&quot;"; break;
            default: result += ch; break;
        }
    }
    return result;
}
}

std::string SimpleHtmlStrategy::generate(const ProjectD& project) const {
    std::ostringstream html;
    html << "<!doctype html>\n<html lang=\"ru\">\n<head>\n";
    html << "<meta charset=\"UTF-8\">\n<title>" << escapeHtml(project.projectName) << "</title>\n";
    html << "</head>\n<body>\n";
    html << "<h1>" << escapeHtml(project.projectName) << "</h1>\n";
    html << "<h2>Файлы проекта</h2>\n<ul>\n";

    for (const auto& file : project.files) {
        html << "<li>" << escapeHtml(file.fileName) << "</li>\n";
    }

    html << "</ul>\n</body>\n</html>\n";
    return html.str();
}

std::string DetailedHtmlStrategy::generate(const ProjectD& project) const {
    std::ostringstream html;
    html << "<!doctype html>\n<html lang=\"ru\">\n<head>\n";
    html << "<meta charset=\"UTF-8\">\n<title>" << escapeHtml(project.projectName) << "</title>\n";
    html << "<style>body{font-family:Arial,sans-serif;max-width:1000px;margin:30px auto;line-height:1.5;}";
    html << "code{background:#eee;padding:2px 4px;border-radius:4px;}";
    html << "section{border:1px solid #ddd;border-radius:8px;padding:16px;margin-bottom:16px;}";
    html << ".description{color:#555;}</style>\n";
    html << "</head>\n<body>\n";
    html << "<h1>Документация проекта: " << escapeHtml(project.projectName) << "</h1>\n";

    for (const auto& file : project.files) {
        html << "<section>\n";
        html << "<h2>Файл: " << escapeHtml(file.fileName) << "</h2>\n";
        html << "<p><code>" << escapeHtml(file.filePath) << "</code></p>\n";

        html << "<h3>Классы</h3>\n";
        if (file.classes.empty()) {
            html << "<p>Классы не найдены.</p>\n";
        } else {
            html << "<ul>\n";
            for (const auto& classDoc : file.classes) {
                html << "<li><b>" << escapeHtml(classDoc.className) << "</b>";
                if (!classDoc.description.empty()) {
                    html << " — <span class=\"description\">" << escapeHtml(classDoc.description) << "</span>";
                }
                html << "</li>\n";
            }
            html << "</ul>\n";
        }

        html << "<h3>Функции</h3>\n";
        if (file.functions.empty()) {
            html << "<p>Функции не найдены.</p>\n";
        } else {
            html << "<ul>\n";
            for (const auto& functionDoc : file.functions) {
                html << "<li><code>" << escapeHtml(functionDoc.returnType) << " "
                     << escapeHtml(functionDoc.functionName) << "("
                     << escapeHtml(functionDoc.parameters) << ")</code>";
                if (!functionDoc.description.empty()) {
                    html << " — <span class=\"description\">" << escapeHtml(functionDoc.description) << "</span>";
                }
                html << "</li>\n";
            }
            html << "</ul>\n";
        }

        html << "</section>\n";
    }

    html << "</body>\n</html>\n";
    return html.str();
}
