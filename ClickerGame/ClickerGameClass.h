#pragma once

#include <iostream>
#include <conio.h> 
#include <thread>
#include <mutex>
#include <fstream>

#pragma warning( disable : 4996) // for test

class ClickerGame {
public:
	ClickerGame() { start = std::chrono::high_resolution_clock::now(); }
	void Start();		// Запуск "кликера"
private:
	// Основные методы
	void keyHandler();	// Оброботка всех нажатий
	void preparation();	// Заполнение полей класса (Настройки игры)
	void out();			// Функция вывода основного игрового меню на экран
	void clickShop();	// Магизин улучшений "клика"
	void incomeShop();	// Магазин улучшений "пассивного дохода"
	void showStats();	// Показать статистику

	// Вспомогательные методы
	void increaseThePrice(int& curPrice, double& ratio);	// Увелинение стоймости "лота" после каждой его покупки
	void increaseMoney();									// Увеличение "денег" после каждого нажатия
	void passiveIncome();									// Увелечение "денег" каждый "пассивнный тик"
	void showYourItems();									// Отобразить купленные предметы
	void turnTheOutThread(bool var);						// Включить/Выключить поток вывода основного меню на экран
	void save();
	void load();


	// Деньги
	int curMoney;							// Текущий баланс
	int curPassiveIncome;					// Текущий пассивный доход
	int moneyForClick;						// Сколько начисляется за каждый клик

	// Поля задержок
	int curTimePauseForClick;				// Текущая задержка между кликами
	int curTimePauseForOut;					// Текущая задержка между выводами на экран основного меню
	int curTimePauseForOtherKeys;			// Текущая задержка между между нажатиями "не основных" клавиш
	int curTimeForPassiveIncome;			// Текущая задержка между "писсивными тиками"

	// Поля силы клика
	double ratioUpgradeClickPower;			// Коэффициент увеличения цены после улучшения силы клика
	int curPriceUpgradeClickPower;			// Текущая цена улучшения силы клика
	int curCountUpgreadeClickPower;			// Количество уже имеющихся улучшений
	int upForOneUpgreadeCliclPower;			// Сколько добавляется за каждое улучшение силы клика

	// Поля шанса критического удара
	double ratioCritChance;					// Коэффициент увеличения цены после улучшения шанса критического удара
	int curPriceCritChance;					// Текущая цена улучшения шанса критического удара
	int curCritChance;						// Текущий шанс крита
	int upForOneUpgreadeCritChance;			// Сколько добавляется за каждое улучшение шанса критического удара

	// Поля силы критического удара
	double ratioCritMultiplier;				// Коэффициент увеличения цены после улучшения силы критического удара
	int curPriceCritMultiplier;				// Текущая цена улучшения шанса критического удара
	int curCritMultiplier;					// Текущая сила критического удара
	int upForOneUpgreadeCritMultiplier;		// Сколько добавляется за каждое улучшение сыли критического удара

	// Поля "плюса"
	double ratioPlus;						// Коэффициент увеличения цены после покупки "плюса"
	int curPricePlus;						// Текущая цена "плюса"
	int curIncomePlus;						// Сколько добовляет каждый "плюс" к пассивному доходу  
	int countOfPlus;						// Колличество "плюсов"

	// Поля "собаки"
	double ratioAt;							// Коэффициент увеличения цены после покупки "собаки"
	int curPriceAt;							// Текущая цена "собаки"
	int curIncomeAt;						// Сколько добовляет каждая "собака" к пассивному доходу 
	int countOfAt;							// Колличество "собак"

	// Поля "вопроса"
	double ratioQuestion;					// Коэффициент увеличения цены после покупки "знака вопроса"
	int curPriceQuestion;					// Текущая цена "вопроса"
	int curIncomeQuestion;					// Сколько добовляет каждый "вопрос" к пассивному доходу  
	int countOfQuestion;					// Колличество "вопросов"

	// Остальное
	std::string status;						// Статус "богаства" игрока
	bool last;								// Для работы "печенья"
	bool outThreadActivity;					// Флаг выключения/включения основного потока вывода
	int totalClicks;						// Всего нажатий
	int totalBuys;
	std::chrono::steady_clock::time_point start; // Временная точка запуска игры

	// Потоки
	std::condition_variable cv;				// Условная переменная для синхронизации потоков
	std::thread outThread;					// Поток для вывода основного меню
	std::thread keyHandlerThread;			// Поток для считывания нажатий
	std::thread passiveIncomeThread;		// Поток для начисления пассивного дохода
	std::mutex mtx;							// Мутекс для синхронизации

	std::string CookieNormal = "   ***   \n  *****  \n  *****  \n  *****  \n   ***   ";
	std::string CookiePressed = "   &&&   \n  &&&&&  \n  &&&&&  \n  &&&&&  \n   &&&   ";
	std::string Cookie;
};