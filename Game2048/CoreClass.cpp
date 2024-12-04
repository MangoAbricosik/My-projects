#include "CoreClass.h"

void CoreClass::start() {
	system("cls");
	std::cout << "1 - Play standart\t\t\t\tYour pb in this mod: " << pb_solo_standart << "\n";
	std::cout << "2 - Your field size\t\t\t\tYour pb in this mod: " << pb_solo_custom << "\n\n";
	std::cout << "3 - RandomPlay\t\t\t\t\tYour pb in this mod: " << pb_auto_standart << "\n";
	std::cout << "4 - RandomPlay with your field size\t\tYour pb in this mod: " << pb_auto_custom << "\n\n";
	std::cout << "5 - Do it slowly and randomly or quickly and predictably? ---> " << (slowRandom ? "Slow" : "Fast") << " <--- 5 - to change\n\n";
	std::cout << "Your choice: ";
	char temp;
	temp = _getch();

	switch (temp) {
	case '1':
		keyHandler();
		if (score > pb_solo_standart)
			pb_solo_standart = score;
		break;
	case '2':
		system("cls");
		std::cout << "Enter height: ";
		std::cin >> Height;
		system("cls");
		std::cout << "Enter width: ";
		std::cin >> Width;
		field.clear();
		field.resize(Height, std::vector<int>(Width));
		keyHandler();
		if (score > pb_solo_custom)
			pb_solo_custom = score;
		break;
	case '3':
		useAutoPlay = true;
		keyHandler();
		if (score > pb_auto_standart)
			pb_auto_standart = score;
		break;
	case '4':
		system("cls");
		std::cout << "Enter height: ";
		std::cin >> Height;
		system("cls");
		std::cout << "Enter width: ";
		std::cin >> Width;
		field.clear();
		field.resize(Height, std::vector<int>(Width));
		useAutoPlay = true;
		keyHandler();
		if (score > pb_auto_custom)
			pb_auto_custom = score;
		break;
	case '5':
		slowRandom = slowRandom ? false : true;
		start();
		break;

	}

	saveGame();
	system("cls");
	std::cout << "Game over\nYour score: " << score << '\n';

} // Запуск, меню

void CoreClass::keyHandler() {
	char temp;
	std::vector<int> keys{ 72,75,80,77 };

	Spawner();
	while (true) {
		if (!Spawner())
			break;
		dataOutput();
		
		if(!useAutoPlay)
			temp = _getch();
		else {
			if (slowRandom)
				srand(time(NULL));;
			temp = char(keys[(rand() % 4)]);
		}

		if (temp == -32)
			continue;

		switch (temp) {
		case 72:
		case 'w':
			moveField('y', '-');
			break;
		case 75:
		case 'a':
			moveField('x', '-');
			break;
		case 80:
		case 's':
			moveField('y', '+');
			break;
		case 77:
		case 'd':
			moveField('x', '+');
			break;
		}
		dataOutput();
	}
} // Обработчик клавишь

void CoreClass::dataOutput() {
	std::string temp;
	system("cls");
	for (auto item : field) {
		for (auto inner_item : item) {
			temp += std::to_string(inner_item);
			temp += '\t';
		}
		temp += '\n';
	}

	temp += "\n|||||||||||||||||||||||||||||||||||||\n\n";
	temp += "Your score: ";
	temp += std::to_string(score);

	std::cout << temp;
} // Вывод

bool CoreClass::Spawner() {

	std::vector<int> nubmers{2,4,8,16,32,64,128,256};
	auto getANumberForSpawner = [&]() { 
		if (score < 128)
			return 6;
		if (score < 256)
			return 5;
		if (score < 512)
			return 4;
		if (score < 1024)
			return 3;
		if (score < 2048)
			return 2;
		return 1;
		}; // Вспомогательная лямбда

	if (slowRandom)
		srand(time(NULL));;

	int val;
	auto emptySlots = numbersOfEmptySlots();
	if (!emptySlots.empty()) {
		val = rand() % emptySlots.size();
		field[emptySlots[val].first][emptySlots[val].second] = nubmers[rand() % (nubmers.size() - getANumberForSpawner())];
	}
	else {
		return false;
	}
	return true;
} // Создать элемент

void CoreClass::moveField(char axis, char sign) {

	if (axis == 'y') {
		for (size_t q = 0; q < field.size(); q++) {
			if (sign == '+') {
				for (size_t y = 0; y < field.size(); y++) {
					for (size_t x = 0; x < field[y].size(); x++) {
						for (size_t i = 1; i < field.size() - y; i++) {
							if (field[y][x] != 0) {
								if (field[y + i][x] == 0) {
									field[y + i][x] = field[y][x];
									field[y][x] = 0;
									i = 1;
								}
								else if (field[y + i][x] == field[y][x]) {
									field[y + i][x] *= 2;
									score += field[y + i][x];
									field[y][x] = 0;
								}
								else
									break;
							}
						}
					}
				}

			}
			else {
				for (size_t y = field.size() - 1; y > 0; y--) {
					for (size_t x = 0; x < field[y].size(); x++) {
						for (size_t i = 1; i <= y; i++) {
							if (field[y][x] != 0) {
								if (field[y - i][x] == 0) {
									field[y - i][x] = field[y][x];
									field[y][x] = 0;
									i = 1;
								}
								else if (field[y - i][x] == field[y][x]) {
									field[y - i][x] *= 2;
									score += field[y - i][x];
									field[y][x] = 0;
								}
								else
									break;
							}
						}
					}
				}
			}
		}
	}
	else {
		for (size_t q = 0; q < field[0].size(); q++)
		{
			if (sign == '+') {
				for (size_t y = 0; y < field.size(); y++) {
					for (size_t x = 0; x < field[y].size(); x++) {
						for (size_t i = 1; i < field[y].size() - x; i++) {
							if (field[y][x] != 0) {
								if (field[y][x + i] == 0) {
									field[y][x + i] = field[y][x];
									field[y][x] = 0;
									i = 1;
								}
								else if (field[y][x + i] == field[y][x]) {
									field[y][x + i] *= 2;
									score += field[y][x + i];
									field[y][x] = 0;
								}
								else
									break;
							}
						}
					}
				}
			}
			else {
				for (size_t y = 0; y < field.size(); y++) {
					for (size_t x = field[y].size() - 1; x > 0; x--) {
						for (size_t i = 1; i <= x; i++) {
							if (field[y][x] != 0) {
								if (field[y][x - i] == 0) {
									field[y][x - i] = field[y][x];
									field[y][x] = 0;
									i = 1;
								}
								else if (field[y][x - i] == field[y][x]) {
									field[y][x - i] *= 2;
									score += field[y][x - i];
									field[y][x] = 0;
								}
								else
									break;
							}
						}
					}
				}
			}
		}
	}
} // Сдвинуть ячейки поля	

std::vector<std::pair<int, int>> CoreClass::numbersOfEmptySlots()
{
	std::vector<std::pair<int,int>> result;
	for (size_t y = 0; y < field.size(); y++) {
		for (size_t x = 0; x < field[y].size(); x++) {
			if (field[y][x] == 0)
				result.push_back({ y,x });
		}
	}
	return result;
} // Получить номера "пустых слотов

void CoreClass::saveGame() {
	std::ofstream fout;
	fout.open(saveName);
	fout << pb_solo_standart << " " << pb_solo_custom << " " << pb_auto_standart << " " << pb_auto_custom;
	fout.close();
} // Сохранить игру

void CoreClass::loadGame() {
	std::ifstream fin;
	fin.open(saveName);
	fin >> pb_solo_standart >> pb_solo_custom >> pb_auto_standart >> pb_auto_custom;
	fin.close();
} // Загрузить игру

