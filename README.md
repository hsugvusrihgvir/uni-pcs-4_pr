# Генератор документации

[отчет](отчет.md)

## Краткое описание

Проект представляет собой консольное приложение на C++, которое анализирует исходные файлы `.cpp` и `.h`, извлекает комментарии и основные элементы кода, а затем формирует HTML-документацию.

Приложение поддерживает:

- поиск файлов `.cpp` и `.h` во вложенных папках;
- чтение исходных файлов;
- извлечение комментариев формата `///` и `/** */`;
- определение классов, структур и функций;
- генерацию HTML-документации;
- сохранение результата в указанную папку.

## Структура проекта

```text
.
├── CMakeLists.txt
├── README.md
├── include/
│   ├── CodeParser.h
│   ├── DocFactory.h
│   ├── DocumentationGenerator.h
│   ├── DocumentModel.h
│   ├── FileScanner.h
│   ├── HtmlGenerationStrategy.h
│   └── HtmlGenerator.h
└── src/
    ├── CodeParser.cpp
    ├── DocFactory.cpp
    ├── DocumentationGenerator.cpp
    ├── DocumentModel.cpp
    ├── FileScanner.cpp
    ├── HtmlGenerationStrategy.cpp
    ├── HtmlGenerator.cpp
    └── main.cpp
```

## Использованные паттерны проектирования

- **Фабричный метод** — используется в `DocFactory` для создания объектов документации.
- **Одиночка** — используется в `DocumentationGenerator` для единой точки управления генерацией.
- **Фасад** — `DocumentationGenerator` скрывает работу модулей `FileScanner`, `CodeParser` и `HtmlGenerator`.
- **Стратегия** — используется для выбора способа генерации HTML-документации.

## Сторонние библиотеки

Сторонние библиотеки не используются. Проект написан на стандартной библиотеке C++17.

## Сборка проекта

Проект собирается через CMake.

```bash
cmake -S . -B build
cmake --build build
```

## Пример запуска



```bash
./build/doc_generator ./src ./docs
```


После запуска документация будет сохранена в файл `docs/index.html`


