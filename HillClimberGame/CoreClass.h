#pragma once

#include <iostream>
#include <thread>
#include <conio.h> 
#include <vector>
#include <mutex>
#include <string>
#include <mutex>
#include <windows.h>

#pragma warning( disable : 4996) // for test

class CoreClass {
public:
	void Menu();	// Меню
private:
	std::vector<std::string> curLevel; // Текущий уровень

	// Вспомогательная структура
	struct Player {
		Player(int other_y = 10, int other_x = 10, char other_playerSym = '&', int jumpPower = 3) : y(other_y), x(other_x), playerSym(other_playerSym), jumpPower(jumpPower) {}

		unsigned int getY() { return y; }
		void setY(int val) { y = val; }

		unsigned int getX() { return x; }
		void setX(int val) { x = val; }
		
		char getSym() { return playerSym; }

		unsigned int getJumpPower() { return jumpPower; }
		void setJumpPower(int jumpPower) { this->jumpPower = jumpPower; }

	private:
		int jumpPower;	// Сила прыжка игрока
		int y, x;		// Координаты игрока
		char playerSym; // Символ игрока
	};

	// Основные методы
	void mainGame();						// Запуск всех основных потоков
	void output();							// Вывод
	void move();							// Определить куда хочет игрок, узнать возможно ли это. Дополнительная обработка прыжка
	void movePlayer(char val, char sym);	// Сдвинуть координаты игрока
	void gravity();							// Гравитация

	// Вспомогательные методы
	bool weCanStep(std::pair<int, int> tempPoint);	// Можем ли мы наступить на координату
	void turnTheGravityThread(bool var);			// Выключить гравитацию, нужно для прыжка

	bool gravityThreadActivity = true;				// Вспомогательная переменная для метода выключения гравитации
	bool turnAllThreads = true;						// Закончить все "главные" потоки


	MSG msg;	// Для асинхронного считывания клавиатуры

	// Потоки
	std::thread outputThread;					// Поток вывода
	std::thread gravityThread;					// Поток гравитации
	std::thread moveThread;						// Поток движения
	std::thread jumpThread;						// Поток прыжка
	std::condition_variable cvGrivityThread;	// Состояние гравитации
	std::mutex MtxGravityLock;					// Мутекс для гравитации
	std::mutex MtxMovePlayer;					// Для движения
	std::mutex MtxCanWeStep;					// Для метода "возможность настпупить"

	// Объект игрок
	Player player;
};
