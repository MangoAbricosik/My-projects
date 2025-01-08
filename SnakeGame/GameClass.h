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
    void StartGame(int y, int x, int timePause);                                                // ������ ����
    void StartAutoGame(int y, int x, int timePause);                                            // ������ ���� � �������������� ������

private:
    void createWalls();                                                                         // �������� "����" � ��������� ������ ����
    void createSnake();                                                                         // �������� "����"
    void createFood();                                                                          // �������� "���"
    std::pair<int, int> getAPoint();                                                            // ����� ��������� ��������� ����� �� "����" ������ "����"
    bool weCanStep(std::pair<int, int> tempPoint);                                              // ����� �� ������� ��� � ��� �����? ��� �� ����� "����" ��� "�����"
    void showField();                                                                           // ���������� ����
    void repeater();                                                                            // ����������� ��� ����� "����" ����� �� "�������"
    bool foodStillThere();                                                                      // ���� �� "�����" ���� ��� ����� �� ��������
    void increaseSnake();                                                                       // ��������� ������ ���� �� 1
    std::vector<std::pair<int, int>> bfs(int startY, int startX, int finishY, int finishX);     // ����� � ������
    void preSeput();                                                                            // ���� ���������

    int timePause = 0;                                                                          // �������� ����� ����� �����
    std::vector<std::vector<char>> field;                                                       // ����
    std::vector<std::pair<std::pair<int, int>, char>> snake;                                    // ����
    std::vector<std::pair<std::pair<int, int>, char>> snakeRepeter;                             // ����� ����
    std::pair<int, int> food;                                                                   // ���������� ���

    const int startSnakeSize = 3;                                                               // ��������� ����� ����
};
