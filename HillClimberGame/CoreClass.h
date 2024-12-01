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
	void Menu();	// ����
private:
	std::vector<std::string> curLevel; // ������� �������

	// ��������������� ���������
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
		int jumpPower;	// ���� ������ ������
		int y, x;		// ���������� ������
		char playerSym; // ������ ������
	};

	// �������� ������
	void mainGame();						// ������ ���� �������� �������
	void output();							// �����
	void move();							// ���������� ���� ����� �����, ������ �������� �� ���. �������������� ��������� ������
	void movePlayer(char val, char sym);	// �������� ���������� ������
	void gravity();							// ����������

	// ��������������� ������
	bool weCanStep(std::pair<int, int> tempPoint);	// ����� �� �� ��������� �� ����������
	void turnTheGravityThread(bool var);			// ��������� ����������, ����� ��� ������

	bool gravityThreadActivity = true;				// ��������������� ���������� ��� ������ ���������� ����������
	bool turnAllThreads = true;						// ��������� ��� "�������" ������


	MSG msg;	// ��� ������������ ���������� ����������

	// ������
	std::thread outputThread;					// ����� ������
	std::thread gravityThread;					// ����� ����������
	std::thread moveThread;						// ����� ��������
	std::thread jumpThread;						// ����� ������
	std::condition_variable cvGrivityThread;	// ��������� ����������
	std::mutex MtxGravityLock;					// ������ ��� ����������
	std::mutex MtxMovePlayer;					// ��� ��������
	std::mutex MtxCanWeStep;					// ��� ������ "����������� ����������"

	// ������ �����
	Player player;
};
