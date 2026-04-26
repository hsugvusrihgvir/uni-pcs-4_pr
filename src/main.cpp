#include "DocumentationGenerator.h"

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: doc_generator <input_directory> <output_directory>" << std::endl;
        return 1;
    }

    try {
        DocumentationGenerator::getInstance().generate(argv[1], argv[2]);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }
}
