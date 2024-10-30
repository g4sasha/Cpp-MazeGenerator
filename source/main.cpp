#include <SFML/Graphics.hpp>
#include "MazeGenerator.h"

const int CELL_SIZE = 10;   // Размер клетки в пикселях
const int MAZE_WIDTH = 101; // Ширина лабиринта (должна быть нечётной)
const int MAZE_HEIGHT = 51; // Высота лабиринта (должна быть нечётной)

// TODO: Вынести кнопку в отдельный класс
bool isMouseOverButton(const sf::RectangleShape &button, const sf::Vector2i &mousePos)
{
    return button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

int main()
{
    // Поддержка Русского языка
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Генерация лабиринта
    MazeGenerator generator(MAZE_WIDTH, MAZE_HEIGHT);
    generator.generateMaze();

    // SFML окно
    sf::RenderWindow window(sf::VideoMode(MAZE_WIDTH * CELL_SIZE, MAZE_HEIGHT * CELL_SIZE + 50 * 2), "Maze generator", sf::Style::Close);
    window.setFramerateLimit(10);

    // Кнопки
    sf::Font font;
    font.loadFromFile("../resources/pixel.ttf");

    sf::Text newMazeText(L"Новый", font, 20);
    sf::RectangleShape newMazeButton(sf::Vector2f(150, 50));
    newMazeButton.setPosition(10, MAZE_HEIGHT * CELL_SIZE + 10);
    newMazeButton.setFillColor(sf::Color::Magenta);
    newMazeText.setPosition(51, MAZE_HEIGHT * CELL_SIZE + 21);

    sf::Text solveMazeText(L"Найти путь", font, 20);
    sf::RectangleShape solveMazeButton(sf::Vector2f(150, 50));
    solveMazeButton.setPosition(170, MAZE_HEIGHT * CELL_SIZE + 10);
    solveMazeButton.setFillColor(sf::Color::Blue);
    solveMazeText.setPosition(185, MAZE_HEIGHT * CELL_SIZE + 21);

    // Определение входа и выхода
    sf::Vector2i entrance(1, MAZE_HEIGHT - 2);
    sf::Vector2i exit(MAZE_WIDTH - 2, 1);

    // Флаг для отображения пути
    bool showPath = false;

    // Основной цикл
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Проверка нажатия на кнопки
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (isMouseOverButton(newMazeButton, mousePos))
                {
                    generator.generateMaze();
                    showPath = false;
                }

                if (isMouseOverButton(solveMazeButton, mousePos))
                {
                    generator.resetRobot();                             // Сброс состояния робота
                    generator.findPath(entrance.x, entrance.y, window); // Запускаем поиск пути
                    showPath = true;                                    // Показываем путь
                }
            }
        }

        // Начало отрисовки
        window.clear();

        // Отрисовка лабиринта
        const auto &visited = generator.getMaze();
        for (int x = 0; x < MAZE_WIDTH; ++x)
        {
            for (int y = 0; y < MAZE_HEIGHT; ++y)
            {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);

                if (!visited[x][y])
                {
                    cell.setFillColor(sf::Color::Black);
                }
                else
                {
                    cell.setFillColor(sf::Color::White);
                }

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
            const auto &path = generator.getPath();
            for (const auto &p : path)
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
    }

    return 0;
}