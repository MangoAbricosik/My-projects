#include "GameClass.h"

//#define DEBUG

std::vector<int> getSettings() {                    // В случае выбора своих настроек получение таковых
    int y, x, timePause;
    system("cls");
    std::cout << "Write the height: ";              // Высота
    std::cin >> y;
    system("cls");
    std::cout << "Write the width: ";               // Ширина
    std::cin >> x;
    system("cls");
    std::cout << "Write the delay time: ";          // Задержка
    std::cin >> timePause;
    return std::vector<int> { y, x, timePause };
}

int main() {
    //freopen("input.txt", "r", stdin); // for test         
    std::ios_base::sync_with_stdio(false);          // Отключение синхронизации (Картинка становиться стабильнее)

    //SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { 10 , 10 });

    while (true) {
        system("cls");
        std::cout << "Please use the English layout\n\n1 - Classic game\n2 - AutoPlay\n\n";
        std::cout << "3 - Classic game (Your settings)\n4 - AutoPlay (Your settings) (Recommend)";
        std::cout << "\n\nYour choice : ";

        char temp;
        temp = getch();
        temp -= 48;

        SnakeGame game;
        std::vector<int> settings(3);

        switch ((int)temp)
        {
        case 1:
            game.StartGame(10, 20, 200);                                // Классический старт с стандартными настройками
            break;
        case 2:
            game.StartAutoGame(25, 50, 0);                              // Auto mod старт с стандартными настройками
            break;
        case 3:                                                         // Режим со своими настройками                             
            settings = getSettings();
            game.StartGame(settings[0], settings[1], settings[2]);
            break;
        case 4:                                                         // Режим со своими настройками
            settings = getSettings();
            game.StartAutoGame(settings[0], settings[1], settings[2]);
            break;
        default:
            return 0;
            break;
        }

        std::cout << "\nPress any key to restart: ";
        getch();
    }
    return 0;
}