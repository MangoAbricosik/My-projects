#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <conio.h> 
#include <fstream>

class CoreClass {
public:
	CoreClass(int Height = 4, int Width = 4) : Height(Height), Width(Width), field(Height, std::vector<int>(Width))	{
		if (std::ifstream(saveName)){	// ���� ���� ���������� ����, �� �������� ����
			loadGame(); 
		} 
		else {							// ����� ������� ���� ���������� � �������� ����������
			saveGame(); 
		}
	}
	void start();												// ������, ����
private:
	void keyHandler();											// ���������� �������
	void dataOutput();											// �����
	bool Spawner();												// ������� �������
	void moveField(char axis, char sign);						// �������� ������ ����	
	std::vector<std::pair<int, int>> numbersOfEmptySlots();		// �������� ������ "������ ������

	void saveGame();					// ��������� ����
	void loadGame();					// ��������� ����

	bool useAutoPlay = false;			// ������������ �� ���� �����
	bool slowRandom = false;			// ����� ��������� ������, � ������� �������� "�����������"

	long long score = 0;				// ���� ������� ������
	long long pb_solo_standart = 0;		// ������ � ��������� ����������� ������
	long long pb_solo_custom = 0;		// ������ � ��������� ������������� ������
	long long pb_auto_standart = 0;		// ������ � ����-����������� ������
	long long pb_auto_custom = 0;		// ������ � ����-������������� ������

	int Height, Width;					// ������ � ������ ����


	std::string saveName = "Save2048.txt";	// ��� ����� ���������� 
	std::vector<std::vector<int>> field;	// ������� ����
};

