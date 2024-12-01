#include "CoreClass.h"
#include "Levels.h"

void CoreClass::Menu() {
	std::cout << "Level 1 - A small mountain\nLevel 2 - The Big Cave Mountain\n";

	std::cout << "\nThe level number: ";
	int temp = getch();
	system("cls");
	switch (temp) {
	case '1':
        player.setY(35);
        player.setX(7);
		curLevel = levelOne;
		break;
    case '2':
        player.setY(58);
        player.setX(7);
        curLevel = levelTwo;
        break;
    default:
        Menu();
        break;
	}
	mainGame();
} // Меню, выбор уровня

void CoreClass::mainGame() {
    // Запустим основные потоки
	outputThread = std::thread(&CoreClass::output, this);
    gravityThread = std::thread(&CoreClass::gravity, this);
    moveThread = std::thread(&CoreClass::move, this);

    while (turnAllThreads) {}


    // Остоновим основные потоки
    moveThread.detach();
    gravityThread.detach();
	outputThread.detach();

    // Завершение
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    system("cls");
    std::cout << "Level done\Thanks for playing\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
} // Запуск основных потоков

void CoreClass::output() {
	std::string temp;

    while (turnAllThreads) {
        temp = "";
        for (unsigned int i = (player.getY() - 8); i < (player.getY() - 8 + 12); i++) {
            for (unsigned int j = (player.getX() - 5); j < (player.getX() - 5 + 20); j++) {
                if (i == player.getY() && j == player.getX())
                    temp += '&';
                else
                    temp += curLevel[i][j];
            }
            temp += '\n';
        }
        system("cls");

        temp += "\n# - rock\n. - The background of the rock\n+ - junp boost\n* - exit\n";
        temp += "\nw - jump\na - left\nd - rigth";
        std::cout << temp;
    }
} // Вывод

void CoreClass::move() {
    // Для асинхронного ввода
    bool wPressed = false;
    bool aPressed = false;
    bool dPressed = false;

    while (turnAllThreads)
    {
         std::pair<int, int> tempPoint = { player.getY(), player.getX() };

         // Для асинхронного ввода
         short wState = GetAsyncKeyState('W');
         short aState = GetAsyncKeyState('A');
         short dState = GetAsyncKeyState('D');
        
        if (wState & 0x8000)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (jumpThread.joinable())
                jumpThread.detach();
            if (curLevel[player.getY() + 1][player.getX()] != '.' && curLevel[player.getY() + 1][player.getX()] != ' ' && turnAllThreads) {
                jumpThread = std::thread([&]() {
                    
                    turnTheGravityThread(false);
                    for (unsigned int i = 0; i < player.getJumpPower(); i++) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));
                        tempPoint.first--;
                        if (!weCanStep(tempPoint))
                            break;;
                        movePlayer('y', '-');
                    }

                    turnTheGravityThread(true);
                    });
            }
        }
        if (aState & 0x8000)
        {
            tempPoint.second--;
            if (!weCanStep(tempPoint))
                continue;
            movePlayer('x', '-');
        }
        if (dState & 0x8000)
        {
            tempPoint.second++;
            if (!weCanStep(tempPoint))
                continue;
            movePlayer('x', '+');
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
} // Оброботка того, куда хочет похожить игрок

void CoreClass::movePlayer(char val, char sym) {
    MtxMovePlayer.lock();
    switch (val) {
    case 'x':
        if (sym == '+') {
            player.setX(player.getX() + 1);
        }
        else {
            player.setX(player.getX() - 1);
        }
        break;
    case 'y':
        player.setY(player.getY() - 1);
        break;
    }
    MtxMovePlayer.unlock();
} // Двигаем игрока

void CoreClass::gravity() {
    while(turnAllThreads) {
        std::unique_lock<std::mutex> ulm(MtxGravityLock);
        cvGrivityThread.wait(ulm, [&]() {return gravityThreadActivity; });

        std::pair<int, int> tempPoint = { player.getY() + 1, player.getX() };
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (weCanStep(tempPoint))
            player.setY(player.getY() + 1);

        ulm.unlock();
    }
} // Гравитация

bool CoreClass::weCanStep(std::pair<int, int> tempPoint) {

    MtxCanWeStep.lock();
    if (curLevel[tempPoint.first][tempPoint.second] != '#' && tempPoint.first > 0 && tempPoint.first < curLevel.size() && tempPoint.second > 0 && tempPoint.second < curLevel[0].size()) {
        if (curLevel[tempPoint.first][tempPoint.second] == '+') {
            player.setJumpPower(player.getJumpPower() + 1);
            curLevel[tempPoint.first][tempPoint.second] = '.';
        }
        if (curLevel[tempPoint.first][tempPoint.second] == '*') {
            turnAllThreads = false;
        }
        MtxCanWeStep.unlock();
        return true;
    }
    MtxCanWeStep.unlock();
    return false;
} // Можем ли мы наступить

void CoreClass::turnTheGravityThread(bool var) {
    if (var) { 
        gravityThreadActivity = true;
        cvGrivityThread.notify_one();
    }
    else { 
        gravityThreadActivity = false;
        cvGrivityThread.notify_one();
    }
} // Выключить гравитацию

