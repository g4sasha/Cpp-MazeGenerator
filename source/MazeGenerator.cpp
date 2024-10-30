#include "MazeGenerator.h"
#include <algorithm>
#include <random>
#include <iostream>

// Инициализация
MazeGenerator::MazeGenerator(int width, int height)
    : width(width), height(height), visited(width, std::vector<bool>(height, false)),
      robotVisited(width, std::vector<bool>(height, false)), rng(std::random_device()()), pathFound(false) {}

// Сгенерировать лабиринт
void MazeGenerator::generateMaze()
{
    visited = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false));
    robotVisited = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false)); // Сброс состояния
    path.clear();                                                                           // Сброс пути
    pathFound = false;                                                                      // Сброс состояния
    carvePath(1, height - 2);
}

// Найти и нарисовать путь
void MazeGenerator::carvePath(int x, int y)
{
    visited[x][y] = true;
    std::vector<int> directions = {1, 2, 3, 4};
    std::shuffle(directions.begin(), directions.end(), rng);

    for (int direction : directions)
    {
        int nx = x, ny = y;
        if (direction == 1)
            ny -= 2; // Север
        else if (direction == 2)
            nx += 2; // Восток
        else if (direction == 3)
            ny += 2; // Юг
        else if (direction == 4)
            nx -= 2; // Запад

        if (nx > 0 && ny > 0 && nx < width - 1 && ny < height - 1 && !visited[nx][ny])
        {
            visited[nx][ny] = true;
            visited[(x + nx) / 2][(y + ny) / 2] = true;
            carvePath(nx, ny); // Рекурсивно идём по всему лабиринту
        }
    }
}

// Сброс состояния робота
void MazeGenerator::resetRobot()
{
    for (auto &row : robotVisited)
    {
        std::fill(row.begin(), row.end(), false);
    }

    path.clear();
    pathFound = false;
}

// Найти путь
void MazeGenerator::findPath(int x, int y, sf::RenderWindow &window)
{
    if (pathFound)
    {
        return;
    }

    // Указываем текущий шаг
    robotVisited[x][y] = true;
    // Добавляем клетку в путь
    path.push_back(sf::Vector2i(x, y));

    // Проверка достижения финиша
    if (x == width - 2 && y == 1)
    {
        pathFound = true;
        return;
    }

    std::vector<int> directions = {1, 2, 3, 4};
    std::shuffle(directions.begin(), directions.end(), rng);

    for (int direction : directions)
    {
        int nx = x, ny = y;
        if (direction == 1)
            ny -= 1; // Север
        else if (direction == 2)
            nx += 1; // Восток
        else if (direction == 3)
            ny += 1; // Юг
        else if (direction == 4)
            nx -= 1; // Запад

        if (nx >= 0 && ny >= 0 && nx < width && ny < height && !robotVisited[nx][ny] && visited[nx][ny])
        {
            findPath(nx, ny, window); // Рекурсивно ищем путь

            if (pathFound)
            {
                return;
            }
        }
    }

    // Если не удалось найти путь, убираем последнюю клетку. Так стирается весь путь
    path.pop_back();
}

const std::vector<std::vector<bool>> &MazeGenerator::getMaze() const
{
    return visited;
}

const std::vector<sf::Vector2i> &MazeGenerator::getPath() const
{
    return path;
}