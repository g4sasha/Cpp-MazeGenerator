#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

// Класс генератора лабиринтов
class MazeGenerator {
public:
    static const int CELL_SIZE = 20; // Размер клетки
    MazeGenerator(int width, int height);
    
    // Генерация лабиринта
    void generateMaze();
    
    // Получение лабиринта
    const std::vector<std::vector<bool>>& getMaze() const;

    // Поиск пути
    void findPath(int x, int y, sf::RenderWindow& window);
    
    // Сброс состояния робота
    void resetRobot(); 

    // Получение пути
    const std::vector<sf::Vector2i>& getPath() const;

private:
    // Метод, создающий путь в лабиринте
    void carvePath(int x, int y);
    
    int width, height; // Размеры лабиринта
    std::vector<std::vector<bool>> maze; // Лабиринт
    std::vector<std::vector<bool>> robotVisited; // Посещенные клетки роботом
    std::mt19937 rng; // Генератор случайных чисел

    std::vector<sf::Vector2i> path; // Хранение найденного пути
    bool pathFound; // Найден ли путь
};

#endif // MAZEGENERATOR_H