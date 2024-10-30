Структура проекта:
- Папка "resources" содержит шрифт, для отображения текста на экране
- Папка "source" содержит .cpp и .h файлы с кодом
- Папка "build" содержит исполняемый .exe файл. Он можент запускаться независимо. DoBuild.bat создаёт .o файлы и линкует их для .exe файла (читайте инструкцию внутри файла)

Используется:
- [SFML 2.6.1 для GCC 13.1.0 MinGW (SEH) - 64-bit](https://www.sfml-dev.org/download/sfml/2.6.1/)
- [Компилятор WinLibs MSVCRT 13.1.0 (64-bit)](https://github.com/brechtsanders/winlibs_mingw/releases/download/13.1.0-16.0.5-11.0.0-msvcrt-r5/winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5.7z)

Дополнительно:
- Возможно поменять размер клеток, ширину и высоту лабиринта в main.cpp

const int CELL_SIZE = 10;   // Размер клетки в пикселях
const int MAZE_WIDTH = 101; // Ширина лабиринта (должна быть нечётной)
const int MAZE_HEIGHT = 51; // Высота лабиринта (должна быть нечётной)

Ограничения:
- При больших размерах лабиринта может не хватить стека и программа может не запуститься
- Максимальные размеры, на которых тестировалась программа: CELL_SIZE = 2 | MAZE_WIDTH = 301 | MAZE_HEIGHT = 301
- При максимальных размерах сгенерировать лабиринт и найти путь получилось с ~20 попытки запуска

Материалы:
![image](https://github.com/user-attachments/assets/4958bb36-e013-4500-a220-6d32812d0c50)
![image](https://github.com/user-attachments/assets/4b5011b8-c21b-4839-84ef-dfacbb8f5eb5)
![image](https://github.com/user-attachments/assets/c241c99d-9169-4486-a484-799d7e8ddd64)
![image](https://github.com/user-attachments/assets/34042b94-9774-49de-a0ef-0e281d8db4e5)
