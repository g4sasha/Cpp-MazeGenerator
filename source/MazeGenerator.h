#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

class MazeGenerator
{
public:
    // Конструктор
    MazeGenerator(int width, int height);

    // Команды
    void generateMaze();
    void findPath(int x, int y, sf::RenderWindow &window);
    void resetRobot();

    // Геттеры
    const std::vector<std::vector<bool>> &getMaze() const;
    const std::vector<sf::Vector2i> &getPath() const;

private:
    // Свойства
    int width, height;
    std::vector<std::vector<bool>> visited;
    std::vector<std::vector<bool>> robotVisited;
    std::mt19937 rng;

    // Данные
    std::vector<sf::Vector2i> path;
    bool pathFound;

    // Методы
    void carvePath(int x, int y);
};

#endif