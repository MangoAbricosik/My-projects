#include "ClickerGameClass.h"

void ClickerGame::Start() {
	preparation();															// Установка изначальных значений игры
	keyHandlerThread = std::thread(&ClickerGame::keyHandler, this);			// Отдельный поток для считывания клавиш
	passiveIncomeThread = std::thread(&ClickerGame::passiveIncome, this);	// Отдельный поток для "пассивного дохода"
	outThread = std::thread(&ClickerGame::out, this);						// Отдельный поток для вывода

	outThread.join();														// Что бы не закончить раньше времени
}	// Запуск "кликера"

void ClickerGame::keyHandler() {
	char temp, last = ' ';
	while (true) {

		std::thread t([&temp]() {temp = getch(); 	 });								// Постояная попытка получить данные от пользователя
		std::this_thread::sleep_for(std::chrono::milliseconds(curTimePauseForClick));	// Приостановка основного потока (Защита от спама)
		t.join();																		// Получим данные

		switch (temp) {
		case 'q':							// Если 'q' или 'e' и они не повторяються 2 раза подряд, то увеличем значение денег 
		case 'e':
			if (temp != last)
				increaseMoney();
			break;
		case '1':
			turnTheOutThread(false);		// Выключение основного потока вывода
			clickShop();					// Магазин улучшений "клика"
			break;
		case '2':
			turnTheOutThread(false);		// Выключение основного потока вывода
			incomeShop();					// Магазин улучшений "пассивного дохода"
			break;
		case '3':
			turnTheOutThread(false);		// Выключение основного потока вывода
			showStats();					// Показать статистику
			break;
		case '4':
			turnTheOutThread(false);		// Выключение основного потока вывода
			showYourItems();				// Показать "предметы"
			break;
		case '5':
			turnTheOutThread(false);		// Выключение основного потока вывода
			save();
			break;
		case '6':
			turnTheOutThread(false);		// Выключение основного потока вывода
			load();
			break;
		}
		last = temp;						// Анти спам
		temp = ' ';							//
	}
} // Оброботка всех нажатий

void ClickerGame::preparation() {
	// Установка изначальных значений игры

	curMoney = 0;
	moneyForClick = 1;
	curPassiveIncome = 0;

	curTimePauseForClick = 30;
	curTimePauseForOut = 100;
	curTimePauseForOtherKeys = 100;
	curTimeForPassiveIncome = 1000;

	ratioUpgradeClickPower = 1.3;
	curPriceUpgradeClickPower = 10;
	curCountUpgreadeClickPower = 0;
	upForOneUpgreadeCliclPower = 1;

	ratioCritChance = 1.6;
	curPriceCritChance = 100;
	curCritChance = 1;
	upForOneUpgreadeCritChance = 1;

	ratioCritMultiplier = 5;
	curPriceCritMultiplier = 100;
	curCritMultiplier = 10;
	upForOneUpgreadeCritMultiplier = 10;

	ratioPlus = 1.2;
	curPricePlus = 10;
	curIncomePlus = 1;
	countOfPlus = 0;

	ratioAt = 1.25;
	curPriceAt = 100;
	curIncomeAt = 5;
	countOfAt = 0;

	ratioQuestion = 1.30;
	curPriceQuestion = 1000;
	curIncomeQuestion = 25;
	countOfQuestion = 0;

	last = true;
	status = "Homeless";
	totalClicks = 0;
	totalBuys = 0;

	outThreadActivity = true;	// Изначально основной поток вывода включен

	Cookie = CookieNormal;
}	// Заполнение полей класса (Настройки игры)

void ClickerGame::out() {
	// Функция не закончена
	while (true) {
		std::unique_lock<std::mutex> ulm(mtx);
		cv.wait(ulm, [&]() {return outThreadActivity; }); // Если будет получен сигнал false, то остановим поток, пока не получим true

		std::this_thread::sleep_for(std::chrono::milliseconds(curTimePauseForOut));
		system("cls");
		std::cout << "Your money: " << curMoney << "\t\tYour status: " << status << "\n\n";

		std::cout << Cookie << "\n\n";

		std::cout << "1 - improve the click\n2 - improve passive income\n3 - stats\n4 - show your items\n5 - save\n6 - load\n";
		ulm.unlock();
	}
}	// Функция вывода основного игрового меню на экран

void ClickerGame::clickShop() {
	// Функция не закончена
	auto clickShopHelper = [&](int& curMoney, int& curPassiveIncome, int& CurPrice, int& CurIncome, int& countOf, double& ratio) {
		if ((curMoney - CurPrice) > 0) {
			curPassiveIncome += CurIncome;
			curMoney -= CurPrice;
			countOf++;
			increaseThePrice(CurPrice, ratio);
			totalBuys++;
		}
		};

	system("cls");
	std::cout << "Your money: " << curMoney << '\n';
	std::cout << "1 - Improve click power (" << curPriceUpgradeClickPower << ")\t\tNow improvements you have: " << curCountUpgreadeClickPower << "\n";
	std::cout << "2 - Crit chance (" << curPriceCritChance << ")\t\t\tNow your crit chance: " << curCritChance << "\n";
	std::cout << "3 - crit multiplier (" << curPriceCritMultiplier << ")\t\tNow your crit multiplier: " << curCritMultiplier << "\n";
	std::cout << "\n0 - exit shop\n";

	std::cout << "Input: ";
	int temp;
	temp = getch();
	int mute = 0;
	switch (temp - 48) // Адаптировать кейсы 2 и 3 под лямбду
	{
	case 1:
		clickShopHelper(curMoney, moneyForClick, curPriceUpgradeClickPower, upForOneUpgreadeCliclPower, curCountUpgreadeClickPower, ratioUpgradeClickPower);
		break;
	case 2:
		clickShopHelper(curMoney, curCritChance, curPriceCritChance, upForOneUpgreadeCritChance, mute, ratioCritChance);
		break;
	case 3:
		clickShopHelper(curMoney, curCritMultiplier, curPriceCritMultiplier, upForOneUpgreadeCritMultiplier, mute, ratioCritMultiplier);
		break;
	case 0:
		goto exit;
	}
	clickShop();
exit:
	turnTheOutThread(true);
	return;
}

void ClickerGame::incomeShop() {

	auto incomeShopHelper = [&](int& curMoney, int& curPassiveIncome, int& CurPrice, int& CurIncome, int& countOf, double& ratio) {
		if (curMoney - CurPrice > 0) {
			curPassiveIncome += CurIncome;
			curMoney -= CurPrice;
			countOf++;
			increaseThePrice(CurPrice, ratio);
			totalBuys++;
		}
		}; // Лямбда помощник

	system("cls");
	std::cout << "Your money: " << curMoney << '\n';
	std::cout << "1 - Buy a mini arrow (" << curPricePlus << ")\tNow you have: " << countOfPlus << "\n";
	std::cout << "2 - Buy a super at (" << curPriceAt << ")\tNow you have: " << countOfAt << "\n";
	std::cout << "3 - Buy mega question  (" << curPriceQuestion << ")\tNow you have: " << countOfQuestion << "\n";
	std::cout << "\n0 - exit shop\n";

	std::cout << "Input: ";
	int temp;
	temp = getch();

	switch (temp - 48)
	{
	case 1:
		incomeShopHelper(curMoney, curPassiveIncome, curPricePlus, curIncomePlus, countOfPlus, ratioPlus);
		break;
	case 2:
		incomeShopHelper(curMoney, curPassiveIncome, curPriceAt, curIncomeAt, countOfAt, ratioAt);
		break;
	case 3:
		incomeShopHelper(curMoney, curPassiveIncome, curPriceQuestion, curIncomeQuestion, countOfQuestion, ratioQuestion);
		break;
	case 0:
		goto exit;
		break;
	}
	incomeShop(); // Рекурсивный запуск
exit:
	turnTheOutThread(true);
	return;
}	// Магазин улучшений "пассивного дохода"

void ClickerGame::showStats() {
	auto showStatsHelper = [&]() {
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;
		return duration;
		};

	system("cls");
	std::cout << "Total clicks on cookies: " << totalClicks << "\n";
	std::cout << "Total purchases: " << totalBuys << "\n";

	std::cout << "The session lasts: " << showStatsHelper().count() << "\n";
	std::cout << "\n\nPress any key: ";

	getch();
	turnTheOutThread(true);
	return;
}

void ClickerGame::increaseThePrice(int& curPrice, double& ratio) {
	curPrice *= ratio; // Умножить цену на коэфицент
}	// Увелинение стоймости "лота" после каждой его покупки

void ClickerGame::increaseMoney() {
	if (last) {
		Cookie = CookieNormal;
		last = false;
	}
	else {
		Cookie = CookiePressed;
		last = true;
	}

	srand(std::time(NULL));
	if ((rand() % 100) <= curCritChance)
		curMoney += (moneyForClick * curCritMultiplier);
	curMoney += moneyForClick;

	totalClicks++;
}	// Увелинение стоймости "лота" после каждой его покупки

void ClickerGame::passiveIncome() {

	auto getStatus = [&]() {
		if (curMoney >= 1000000)
			status = "Millionaire";
		else if (curMoney >= 100000)
			status = "Businessman";
		else if (curMoney >= 50000)
			status = "Well-to-do";
		else if (curMoney >= 10000)
			status = "Worker";
		else if (curMoney >= 1000)
			status = "Poor";
		else if (curMoney < 1000)
			status = "Homeless";
		}; // Вспомогательная лямбда для получение текущего статуса

	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(curTimeForPassiveIncome));

		curMoney += curPassiveIncome;
		getStatus();
	}
}	// Увелечение "денег" каждый "пассивнный тик"

void ClickerGame::showYourItems() {

	auto outHelper = [](int counter, std::string name, char symbol) {
		std::cout << "\n\nYou have " << counter << " " << name << "'s:\n\n";
		for (size_t i = 1; i < (counter)+1; i++) {
			std::cout << symbol;
			if (i % 10 == 0)
				std::cout << std::endl;
		}
		};

	system("cls");

	outHelper(countOfPlus, "plus", '+');
	outHelper(countOfAt, "at", '@');
	outHelper(countOfQuestion, "question", '?');

	std::cout << "\n\nPress any key: ";
	getch();
	turnTheOutThread(true);
	return;


}	// Отобразить купленные предметы

void ClickerGame::turnTheOutThread(bool var) {
	if (var) { // Если ture изменть состояние на true и сообщить
		outThreadActivity = true;
		cv.notify_one();
	}
	else { // Иначе изменить состояние на false, сообщить и подождать двойное время окна вывода, для избежания наложения экранов
		outThreadActivity = false;
		cv.notify_one();
		std::this_thread::sleep_for(std::chrono::milliseconds(curTimePauseForOut * 2));
	}
}	// Включить/Выключить поток вывода основного меню на экран

void ClickerGame::save() {
	system("cls");
	std::ofstream fout;
	fout.open("ClickSave.txt");

	fout << curMoney << " " << moneyForClick << " " << curPassiveIncome << '\n';
	fout << curTimePauseForClick << " " << curTimePauseForOut << " " << curTimePauseForOtherKeys << " " << curTimeForPassiveIncome << '\n';
	fout << ratioUpgradeClickPower << " " << curPriceUpgradeClickPower << " " << curCountUpgreadeClickPower << " " << upForOneUpgreadeCliclPower << '\n';
	fout << ratioCritChance << " " << curPriceCritChance << " " << curCritChance << " " << upForOneUpgreadeCritChance << '\n';
	fout << ratioCritMultiplier << " " << curPriceCritMultiplier << " " << curCritMultiplier << " " << upForOneUpgreadeCritMultiplier << '\n';
	fout << ratioPlus << " " << curPricePlus << " " << curIncomePlus << " " << countOfPlus << '\n';
	fout << ratioAt << " " << curPriceAt << " " << curIncomeAt << " " << countOfAt << '\n';
	fout << ratioQuestion << " " << curPriceQuestion << " " << curIncomeQuestion << " " << countOfQuestion << '\n';
	fout << last << " " << status << " " << totalClicks << " " << totalBuys << " " << outThreadActivity << '\n';

	fout.close();


	std::cout << "Game saved\n\nPress any key: ";
	getch();
	turnTheOutThread(true);
}

void ClickerGame::load() {
	system("cls");

	std::ifstream fin;
	fin.open("ClickSave.txt");

	if (!fin.is_open()) { std::cout << "Can't open the save"; }
	else {
		std::string temp;
		fin >> curMoney >> moneyForClick >> curPassiveIncome;
		fin >> curTimePauseForClick >> curTimePauseForOut >> curTimePauseForOtherKeys >> curTimeForPassiveIncome;
		fin >> ratioUpgradeClickPower >> curPriceUpgradeClickPower >> curCountUpgreadeClickPower >> upForOneUpgreadeCliclPower;
		fin >> ratioCritChance >> curPriceCritChance >> curCritChance >> upForOneUpgreadeCritChance;
		fin >> ratioCritMultiplier >> curPriceCritMultiplier >> curCritMultiplier >> upForOneUpgreadeCritMultiplier;
		fin >> ratioPlus >> curPricePlus >> curIncomePlus >> countOfPlus;
		fin >> ratioAt >> curPriceAt >> curIncomeAt >> countOfAt;
		fin >> ratioQuestion >> curPriceQuestion >> curIncomeQuestion >> countOfQuestion;
		fin >> last >> status >> totalClicks >> totalBuys >> outThreadActivity;
	}

	fin.close();

	std::cout << "Save load\n\nPress any key: ";
	getch();
	turnTheOutThread(true);
}


