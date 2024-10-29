#include "MazeGenerator.h"
#include <algorithm>
#include <random>
#include <iostream>

MazeGenerator::MazeGenerator(int width, int height)
    : width(width), height(height), maze(width, std::vector<bool>(height, false)),
      robotVisited(width, std::vector<bool>(height, false)), rng(std::random_device()()), pathFound(false) {}

void MazeGenerator::generateMaze()
{
    maze = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false));
    robotVisited = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false)); // Сброс состояния
    path.clear(); // Сброс пути
    pathFound = false; // Сброс состояния
    carvePath(1, height - 2);
}

void MazeGenerator::carvePath(int x, int y)
{
    maze[x][y] = true;
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

        if (nx > 0 && ny > 0 && nx < width - 1 && ny < height - 1 && !maze[nx][ny])
        {
            maze[nx][ny] = true;
            maze[(x + nx) / 2][(y + ny) / 2] = true;
            carvePath(nx, ny);
        }
    }
}

void MazeGenerator::resetRobot()
{
    // Сброс состояния робота
    for (auto& row : robotVisited)
        std::fill(row.begin(), row.end(), false);
    path.clear(); // Очистка пути
    pathFound = false;
}

void MazeGenerator::findPath(int x, int y, sf::RenderWindow& window)
{
    if (pathFound) return; // Если путь найден, прекращаем выполнение

    // Указываем текущий шаг
    robotVisited[x][y] = true;
    path.push_back(sf::Vector2i(x, y)); // Добавляем клетку в путь

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
        if (direction == 1) ny -= 1; // Север
        else if (direction == 2) nx += 1; // Восток
        else if (direction == 3) ny += 1; // Юг
        else if (direction == 4) nx -= 1; // Запад

        if (nx >= 0 && ny >= 0 && nx < width && ny < height && !robotVisited[nx][ny] && maze[nx][ny])
        {
            findPath(nx, ny, window); // Рекурсивно ищем путь
            if (pathFound) return;
        }
    }

    // Если не удалось найти путь, убираем последнюю клетку
    path.pop_back();
}

const std::vector<std::vector<bool>>& MazeGenerator::getMaze() const
{
    return maze;
}

const std::vector<sf::Vector2i>& MazeGenerator::getPath() const
{
    return path;
}