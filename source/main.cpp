#include <SFML/Graphics.hpp>
#include "MazeGenerator.h"

const int CELL_SIZE = 10; // reccomended cell size: 20
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 50;

bool isMouseOverButton(const sf::RectangleShape &button, const sf::Vector2i &mousePos)
{
    return button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

int main()
{
    int width = 101, height = 51; //recommended maze size: w = 23, h = 33 ALWAYS ODD
    MazeGenerator generator(width, height);
    generator.generateMaze();

    sf::RenderWindow window(sf::VideoMode(width * CELL_SIZE, height * CELL_SIZE + BUTTON_HEIGHT * 2), "Maze");

    // Настройка шрифта и кнопок
    sf::Font font;
    font.loadFromFile("arial.ttf"); // Убедитесь, что шрифт существует

    sf::Text newMazeText("New Maze", font, 20);
    sf::RectangleShape newMazeButton(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
    newMazeButton.setPosition(10, height * CELL_SIZE + 10);
    newMazeButton.setFillColor(sf::Color::Magenta);
    newMazeText.setPosition(20, height * CELL_SIZE + 20);

    sf::Text solveMazeText("Solve Maze", font, 20);
    sf::RectangleShape solveMazeButton(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
    solveMazeButton.setPosition(170, height * CELL_SIZE + 10);
    solveMazeButton.setFillColor(sf::Color::Blue);
    solveMazeText.setPosition(180, height * CELL_SIZE + 20);

    // Определение входа и выхода
    sf::Vector2i entrance(1, height - 2); // Вход
    sf::Vector2i exit(width - 2, 1); // Выход

    // Флаги для отображения
    bool showPath = false;
    bool mazeGenerated = true; // Флаг для отслеживания состояния лабиринта

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Проверка нажатий на кнопки
                if (isMouseOverButton(newMazeButton, mousePos))
                {
                    generator.generateMaze(); // Генерируем новый лабиринт
                    showPath = false; // Скрываем путь
                    mazeGenerated = true; // Устанавливаем флаг, что лабиринт был сгенерирован
                }
                if (isMouseOverButton(solveMazeButton, mousePos))
                {
                    generator.resetRobot(); // Сброс состояния робота
                    generator.findPath(entrance.x, entrance.y, window); // Запускаем поиск пути
                    showPath = true; // Показываем путь
                }
            }
        }

        // Отрисовка только если лабиринт сгенерирован или путь найден
        if (mazeGenerated || showPath)
        {
            window.clear();

            // Отрисовка лабиринта
            const auto &maze = generator.getMaze();
            for (int x = 0; x < width; ++x)
            {
                for (int y = 0; y < height; ++y)
                {
                    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);

                    if (!maze[x][y])
                        cell.setFillColor(sf::Color::Black);
                    else
                        cell.setFillColor(sf::Color::White);

                    window.draw(cell);
                }
            }

            // Отрисовка входа (красная клетка)
            sf::RectangleShape entranceCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            entranceCell.setPosition(entrance.x * CELL_SIZE, entrance.y * CELL_SIZE);
            entranceCell.setFillColor(sf::Color::Red);
            window.draw(entranceCell);

            // Отрисовка выхода (зелёная клетка)
            sf::RectangleShape exitCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            exitCell.setPosition(exit.x * CELL_SIZE, exit.y * CELL_SIZE);
            exitCell.setFillColor(sf::Color::Green);
            window.draw(exitCell);

            // Отрисовка пути, если он найден
            if (showPath)
            {
                const auto& path = generator.getPath();
                for (const auto& p : path)
                {
                    // Пропускаем рисование, если клетка - вход или выход
                    if (p != entrance && p != exit)
                    {
                        sf::RectangleShape pathCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                        pathCell.setPosition(p.x * CELL_SIZE, p.y * CELL_SIZE);
                        pathCell.setFillColor(sf::Color::Yellow); // Цвет пути
                        window.draw(pathCell);
                    }
                }
            }

            // Отрисовка кнопок
            window.draw(newMazeButton);
            window.draw(newMazeText);
            window.draw(solveMazeButton);
            window.draw(solveMazeText);

            window.display();
            mazeGenerated = false; // Сбрасываем флаг после отрисовки
        }
    }

    return 0;
}