#include "FileScanner.h"

#include <exception>
#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << ".\\build\\doc_generator.exe C:\\Users\\daria\\CLionProjects\\project_pks" << std::endl;
        return 1;
    }

    try {
        FileScanner scanner;
        std::vector<std::filesystem::path> files = scanner.scan(argv[1]);

        if (files.empty()) {
            std::cout << "No files" << std::endl;
            return 0;
        }

        std::cout << "Files:" << std::endl;

        for (const auto& file : files) {
            std::cout << "- " << file.string() << std::endl;
        }

        return 0;
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }
}