cmake_minimum_required(VERSION 3.10)

project(doc_generator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
        src/main.cpp
        src/DocumentModel.cpp
        src/DocFactory.cpp
        src/FileScanner.cpp
        src/CodeParser.cpp
        src/HtmlGenerationStrategy.cpp
        src/HtmlGenerator.cpp
        src/DocumentationGenerator.cpp
)

add_executable(doc_generator ${SOURCES})

target_include_directories(doc_generator PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
