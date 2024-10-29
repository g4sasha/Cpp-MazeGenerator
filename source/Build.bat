@echo off
set SFML_DIR="C:\SFML-2.6.1"

:: Проверяем наличие папок include и lib SFML
if not exist %SFML_DIR%\include (
    echo Ошибка: Папка include не найдена в %SFML_DIR%
    exit /b 1
)
if not exist %SFML_DIR%\lib (
    echo Ошибка: Папка lib не найдена в %SFML_DIR%
    exit /b 1
)

:: Компиляция main.cpp и MazeGenerator.cpp в объектные файлы с указанием стандарта C++11
g++ -std=c++11 -I%SFML_DIR%\include -c main.cpp -o main.o
g++ -std=c++11 -I%SFML_DIR%\include -c MazeGenerator.cpp -o MazeGenerator.o

:: Линковка с явным указанием стандартной библиотеки C++
g++ -std=c++11 -L%SFML_DIR%\lib main.o MazeGenerator.o -o Program.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -lstdc++ -mwindows

:: Запуск программы, если компиляция и линковка прошли успешно
if exist Program.exe (
    echo Запуск Program.exe...
    .\Program.exe
) else (
    echo Ошибка: Program.exe не был создан
)
