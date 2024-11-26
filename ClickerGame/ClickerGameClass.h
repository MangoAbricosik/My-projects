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
	void Start();		// ������ "�������"
private:
	// �������� ������
	void keyHandler();	// ��������� ���� �������
	void preparation();	// ���������� ����� ������ (��������� ����)
	void out();			// ������� ������ ��������� �������� ���� �� �����
	void clickShop();	// ������� ��������� "�����"
	void incomeShop();	// ������� ��������� "���������� ������"
	void showStats();	// �������� ����������

	// ��������������� ������
	void increaseThePrice(int& curPrice, double& ratio);	// ���������� ��������� "����" ����� ������ ��� �������
	void increaseMoney();									// ���������� "�����" ����� ������� �������
	void passiveIncome();									// ���������� "�����" ������ "���������� ���"
	void showYourItems();									// ���������� ��������� ��������
	void turnTheOutThread(bool var);						// ��������/��������� ����� ������ ��������� ���� �� �����
	void save();
	void load();


	// ������
	int curMoney;							// ������� ������
	int curPassiveIncome;					// ������� ��������� �����
	int moneyForClick;						// ������� ����������� �� ������ ����

	// ���� ��������
	int curTimePauseForClick;				// ������� �������� ����� �������
	int curTimePauseForOut;					// ������� �������� ����� �������� �� ����� ��������� ����
	int curTimePauseForOtherKeys;			// ������� �������� ����� ����� ��������� "�� ��������" ������
	int curTimeForPassiveIncome;			// ������� �������� ����� "���������� ������"

	// ���� ���� �����
	double ratioUpgradeClickPower;			// ����������� ���������� ���� ����� ��������� ���� �����
	int curPriceUpgradeClickPower;			// ������� ���� ��������� ���� �����
	int curCountUpgreadeClickPower;			// ���������� ��� ��������� ���������
	int upForOneUpgreadeCliclPower;			// ������� ����������� �� ������ ��������� ���� �����

	// ���� ����� ������������ �����
	double ratioCritChance;					// ����������� ���������� ���� ����� ��������� ����� ������������ �����
	int curPriceCritChance;					// ������� ���� ��������� ����� ������������ �����
	int curCritChance;						// ������� ���� �����
	int upForOneUpgreadeCritChance;			// ������� ����������� �� ������ ��������� ����� ������������ �����

	// ���� ���� ������������ �����
	double ratioCritMultiplier;				// ����������� ���������� ���� ����� ��������� ���� ������������ �����
	int curPriceCritMultiplier;				// ������� ���� ��������� ����� ������������ �����
	int curCritMultiplier;					// ������� ���� ������������ �����
	int upForOneUpgreadeCritMultiplier;		// ������� ����������� �� ������ ��������� ���� ������������ �����

	// ���� "�����"
	double ratioPlus;						// ����������� ���������� ���� ����� ������� "�����"
	int curPricePlus;						// ������� ���� "�����"
	int curIncomePlus;						// ������� ��������� ������ "����" � ���������� ������  
	int countOfPlus;						// ����������� "������"

	// ���� "������"
	double ratioAt;							// ����������� ���������� ���� ����� ������� "������"
	int curPriceAt;							// ������� ���� "������"
	int curIncomeAt;						// ������� ��������� ������ "������" � ���������� ������ 
	int countOfAt;							// ����������� "�����"

	// ���� "�������"
	double ratioQuestion;					// ����������� ���������� ���� ����� ������� "����� �������"
	int curPriceQuestion;					// ������� ���� "�������"
	int curIncomeQuestion;					// ������� ��������� ������ "������" � ���������� ������  
	int countOfQuestion;					// ����������� "��������"

	// ���������
	std::string status;						// ������ "��������" ������
	bool last;								// ��� ������ "�������"
	bool outThreadActivity;					// ���� ����������/��������� ��������� ������ ������
	int totalClicks;						// ����� �������
	int totalBuys;
	std::chrono::steady_clock::time_point start; // ��������� ����� ������� ����

	// ������
	std::condition_variable cv;				// �������� ���������� ��� ������������� �������
	std::thread outThread;					// ����� ��� ������ ��������� ����
	std::thread keyHandlerThread;			// ����� ��� ���������� �������
	std::thread passiveIncomeThread;		// ����� ��� ���������� ���������� ������
	std::mutex mtx;							// ������ ��� �������������

	std::string CookieNormal = "   ***   \n  *****  \n  *****  \n  *****  \n   ***   ";
	std::string CookiePressed = "   &&&   \n  &&&&&  \n  &&&&&  \n  &&&&&  \n   &&&   ";
	std::string Cookie;
};