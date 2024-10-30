:: Чтобы bat файл работал, необходимо установить компилятор g++ ОБЯЗАТЕЛЬНО версии 13.1.0 (64-bit)
:: Затем компилятор g++ необходимо добавить в переменные среды
:: Затем установите библиотеку SFML с официального сайта: https://www.sfml-dev.org/download/sfml/2.6.1/
:: Распакуйте и положите SFML по пути: C:\SFML-2.6.1

:: TODO: Использовать CMake

@echo off
set SFML_DIR="C:\SFML-2.6.1"

:: Проверяем наличие папок include и lib SFML
if not exist %SFML_DIR%\include (
    echo Error: include folder not found in %SFML_DIR%
    exit /b 1
)
if not exist %SFML_DIR%\lib (
    echo Error: lib folder not found in %SFML_DIR%
    exit /b 1
)

:: Создание папки build, если она не существует
if not exist ..\build (
    mkdir ..\build
)

:: Компиляция всех .cpp файлов в папке source в объектные файлы с указанием стандарта C++11
for %%f in (..\source\*.cpp) do (
    g++ -std=c++11 -I%SFML_DIR%\include -c %%f -o ..\build\%%~nf.o
)

:: Линковка с указанием папки для exe-файла
g++ -std=c++11 -L%SFML_DIR%\lib ..\build\*.o -o ..\build\Maze.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -lstdc++ -mwindows

:: Запуск программы, если компиляция и линковка прошли успешно
if exist ..\build\Maze.exe (
    echo Running Maze.exe...
    ..\build\Maze.exe || echo Error: Execution failed with code %errorlevel%
) else (
    echo Error: Maze.exe was not created
    pause
)