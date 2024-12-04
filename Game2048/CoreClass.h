#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <conio.h> 
#include <fstream>

class CoreClass {
public:
	CoreClass(int Height = 4, int Width = 4) : Height(Height), Width(Width), field(Height, std::vector<int>(Width))	{
		if (std::ifstream(saveName)){	// Если файл сохранения есть, то загрузим игру
			loadGame(); 
		} 
		else {							// Иначе сделаем файл сохранения с нулевыми значениями
			saveGame(); 
		}
	}
	void start();												// Запуск, меню
private:
	void keyHandler();											// Обработчик клавишь
	void dataOutput();											// Вывод
	bool Spawner();												// Создать элемент
	void moveField(char axis, char sign);						// Сдвинуть ячейки поля	
	std::vector<std::pair<int, int>> numbersOfEmptySlots();		// Получить номера "пустых слотов

	void saveGame();					// Сохранить игру
	void loadGame();					// Загрузить игру

	bool useAutoPlay = false;			// Использовать ли авто режим
	bool slowRandom = false;			// Режим медленной работы, с большей степенью "случайности"

	long long score = 0;				// Очки текущий ссесии
	long long pb_solo_standart = 0;		// Рекорд в одиночном стандартном режиме
	long long pb_solo_custom = 0;		// Рекорд в одиночном настраиваемом режиме
	long long pb_auto_standart = 0;		// Рекорд в авто-стандартном режиме
	long long pb_auto_custom = 0;		// Рекорд в авто-настраиваемом режиме

	int Height, Width;					// Высота и ширина поля


	std::string saveName = "Save2048.txt";	// Имя файла сохронения 
	std::vector<std::vector<int>> field;	// Игровое поле
};

