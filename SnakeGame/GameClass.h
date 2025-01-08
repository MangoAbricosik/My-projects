#pragma once

#include <iostream>
#include <vector>
#include <conio.h> 
#include <thread>
#include <chrono>
#include <queue>
#include <windows.h>

#pragma warning( disable : 4996) // for test

class SnakeGame
{
public:
    void StartGame(int y, int x, int timePause);                                                // Запуск игры
    void StartAutoGame(int y, int x, int timePause);                                            // Запуск игры в автоматическом режиме

private:
    void createWalls();                                                                         // Создание "стен" в изнчально пустом поле
    void createSnake();                                                                         // Создание "змеи"
    void createFood();                                                                          // Создание "еды"
    std::pair<int, int> getAPoint();                                                            // Метод получание случайной точки на "поле" внутри "стен"
    bool weCanStep(std::pair<int, int> tempPoint);                                              // Можно ли сделать шаг в эту точку? Нет ли части "змеи" или "стены"
    void showField();                                                                           // Отобразить поле
    void repeater();                                                                            // Передвинуть все части "змеи" вслед за "головой"
    bool foodStillThere();                                                                      // Пока на "карте" есть еда новая не появится
    void increaseSnake();                                                                       // Увеличить длинну змеи на 1
    std::vector<std::pair<int, int>> bfs(int startY, int startX, int finishY, int finishX);     // Поиск в ширину
    void preSeput();                                                                            // Пред настройка

    int timePause = 0;                                                                          // Задержка перед новым ходом
    std::vector<std::vector<char>> field;                                                       // Поле
    std::vector<std::pair<std::pair<int, int>, char>> snake;                                    // Змея
    std::vector<std::pair<std::pair<int, int>, char>> snakeRepeter;                             // Копия змеи
    std::pair<int, int> food;                                                                   // Координаты еды

    const int startSnakeSize = 3;                                                               // Начальная длина змеи
};
