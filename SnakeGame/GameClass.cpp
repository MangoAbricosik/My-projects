#include "GameClass.h"

void SnakeGame::StartGame(int y, int x, int timePause) {                    // ������ ������������� �����
    field.resize(y, std::vector<char>(x, ' '));
    timePause = timePause;

    preSeput();                                                             // ����������

    std::pair<int, int> tempPoint;                                          // ��������� ����� ��� ���������� ������� ���������
    tempPoint.first = snake[0].first.first;                                 // ��� �������� �������� ����������� ���� �� ����� �����������
    tempPoint.second = snake[0].first.second;

    char temp;
    while (true) {
        std::thread t([&temp]() {temp = getch(); });                        // ��������� ������� �������� ������ �� ������������
        std::this_thread::sleep_for(std::chrono::milliseconds(timePause));  // ������������ ��������� ������
        t.detach();                                                         // �������� ��������� ������ ��� � ��������� ������

        if (temp == -32)                                                    // ��� ����������/������� "�������" � ����� ����� ��������� ����� ��� �������
            continue;                                                       // ���� �� ���, ����� ��� ��� �������, ��� "-32". ��� ������ ����������

        if (!foodStillThere())                                              // �������� ���� �� ��� �� ����
            createFood();                                                   // ���� ���, �� ������� ���

        snakeRepeter = snake;                                               // ��������� ����. ����� ��� ������� "repeater", ������� ��������� ���� ��������� �������
        switch (temp) {
        case 72:
        case 'w':
            tempPoint.first--;
            if (!weCanStep(tempPoint))
                return;
            snake[0].first.first--;
            break;
        case 75:
        case 'a':
            tempPoint.second--;
            if (!weCanStep(tempPoint))
                return;
            snake[0].first.second--;
            break;
        case 80:
        case 's':
            tempPoint.first++;
            if (!weCanStep(tempPoint))
                return;
            snake[0].first.first++;
            break;
        case 77:
        case 'd':
            tempPoint.second++;
            if (!weCanStep(tempPoint))
                return;
            snake[0].first.second++;
            break;
        default:
            system("cls");
            std::cout << "Wrong key" << std::endl;
            break;
        }
        repeater();
        showField();
    }

    return;
}

void SnakeGame::StartAutoGame(int y, int x, int timePause) {
    field.resize(y, std::vector<char>(x, ' '));
    timePause = timePause;

    preSeput();                                                                     // ����������

    std::pair<int, int> tempPoint;
    tempPoint.first = snake[0].first.first;
    tempPoint.second = snake[0].first.second;

    std::vector<std::pair<int, int>> way;
    int startY, startX, finishY, finishX;

    char temp;
    while (true) {
        if (!foodStillThere())                                                      // �������� ���� �� ��� �� ����
            createFood();                                                           // ���� ���, �� ������� ���

        if (way.empty()) {                                                          // ���� ��� ���� �� ���, ��
            startY = snake[0].first.first;                                          // �������� ���������� "������ ����", ��� ���������� ������
            startX = snake[0].first.second;

            finishY = food.first;                                                   // � ���������� ���, ��� ���������� ������
            finishX = food.second;

            way = bfs(startY, startX, finishY, finishX);                            // ����� ����� � ������, ������� ���� �� ���
            if (way.empty()) {                                                      // ���� ���� ����� ������ � ������ ����, ������ ���� ���
                showField();
                std::cout << "\nThe algorithm cannot find the path" << std::endl;
                break;
            }
        }

        for (size_t i = 0; i < way.size() - 1; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(timePause));                      // ���������� �������� ��� �������������
            if (way[i].first > way[i + 1].first && way[i].second == way[i + 1].second) {
                tempPoint.first--;
                if (!weCanStep(tempPoint))
                    return;
                snake[0].first.first--;
            }
            else if (way[i].first == way[i + 1].first && way[i].second > way[i + 1].second) {
                tempPoint.second--;
                if (!weCanStep(tempPoint))
                    return;
                snake[0].first.second--;
            }
            else if (way[i].first < way[i + 1].first && way[i].second == way[i + 1].second) {
                tempPoint.first++;
                if (!weCanStep(tempPoint))
                    return;
                snake[0].first.first++;
            }
            else if (way[i].first == way[i + 1].first && way[i].second < way[i + 1].second) {
                tempPoint.second++;
                if (!weCanStep(tempPoint))
                    return;
                snake[0].first.second++;
            }
            snakeRepeter = snake;
            repeater();
            std::thread feildStream([&]() {showField(); });                         // ��������� ����� ��� ������ ����
            feildStream.join();                                                     // ������������� ������ � ���� �����

            if (i == 10)                                                            // ������ 10 �������� ������� ����� ����� �������� ����
                break;
        }
        way.clear();                                                                // ����� ����������� ���� ���� ���������
    }

    return;
}

void SnakeGame::createWalls() {                                                     // �������� "����"
    for (size_t i = 0; i < field.size(); i++) {
        if (i == 0 || i == field.size() - 1) {
            for (size_t j = 0; j < field[i].size(); j++) {
                field[i][j] = '*';
            }
        }
        else {
            field[i][0] = '*';
            field[i][field[i].size() - 1] = '*';
        }
    }
}

void SnakeGame::createSnake() {                                                     // ��������� "����"
    snake.resize(startSnakeSize);
    for (size_t i = 0, j = startSnakeSize; i < startSnakeSize; ++i, --j) {
        snake[i].first = std::make_pair(1, j);
        snake[i].second = '&';
    }
}

void SnakeGame::createFood() {                                                      // �������� "���"
    srand(time(0));

    food = getAPoint();
    for (size_t i = 0; i < snake.size(); i++) {
        if (snake[i].first.first == food.first && snake[i].first.second == food.second) {
            food = getAPoint();
            i = 0;
        }
    }

    field[food.first][food.second] = '+';
}

std::pair<int, int> SnakeGame::getAPoint() {                                        // ����� ��������� ��������� ����� �� "����" ������ "����"
    std::pair<int, int> point;
    point.first = (rand() % (field.size() - 2)) + 1;
    point.second = (rand() % (field[0].size() - 2)) + 1;

    return point;
}

bool SnakeGame::weCanStep(std::pair<int, int> tempPoint)                            // ����� �� ������� ��� � ��� �����? ��� �� ����� "����" ��� "�����"
{
    for (size_t i = 0; i < snake.size() - 1; i++) {
        if (snake[i].first.first == tempPoint.first && snake[i].first.second == tempPoint.second) {
            showField();
            std::cout << "\nGAME OVER" << std::endl;
            return false;
        }
    }

    if (field[tempPoint.first][tempPoint.second] == ' ')
        return true;
    else if (field[tempPoint.first][tempPoint.second] == '+') {
        field[food.first][food.second] = ' ';
        increaseSnake();

        food.first = INT_MIN;
        food.second = INT_MIN;
        return true;
    }
    else {
        showField();
        std::cout << "\nGAME OVER" << std::endl;
        return false;
    }

    return false;
}

void SnakeGame::showField() {                                                       // ���������� ����
    system("cls");
    auto temp = field;
    for (auto& item : snake) {
        field[item.first.first][item.first.second] = item.second;
    }
    std::string accum = "";
    for (auto& item : field) {
        for (auto& inner_item : item)
            accum += inner_item;
        accum += "\n";
    }
    std::cout << accum;

    field = temp;
}

void SnakeGame::repeater() {                                                        // ����������� ��� ����� "����" ����� �� "�������"
    for (size_t i = 1; i < snake.size(); i++) {
        snake[i] = snakeRepeter[i - 1];
    }
}

bool SnakeGame::foodStillThere() {                                                  // ���� �� "�����" ���� ��� ����� �� ��������
    if (food.first == INT_MIN && food.second == INT_MIN)
        return false;
    return true;
}

void SnakeGame::increaseSnake() {                                                   // ��������� ������ ���� �� 1
    snake.push_back(std::make_pair(std::make_pair(snake[snake.size() - 1].first.first, snake[snake.size() - 1].first.second), '&'));
}

std::vector<std::pair<int, int>> SnakeGame::bfs(int startY, int startX, int finishY, int finishX)   // ����� � ������
{
    int h = field.size(), w = field[0].size();
    auto tempField = field;
    for (auto& item : snake) {
        tempField[item.first.first][item.first.second] = item.second;
    }

    std::vector<std::vector<int>> dist(h, std::vector<int>(w, INT_MAX));                                        // ����� ����������
    std::vector<std::vector<std::pair<int, int>>> from(h, std::vector<std::pair<int, int>>(w, { -1, -1 }));     // ��������� �������� 
    std::queue<std::pair<int, int>> q;                                                                          // �������

    dist[startY][startX] = 0;
    q.push(std::make_pair(startY, startX));
    std::vector<int> dy = { -1, 0, 1, 0 };              // ������� ��������
    std::vector<int> dx = { 0, 1, 0, -1 };
    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop();

        for (size_t d = 0; d < dy.size(); d++) {
            int ty = y + dy[d];
            int tx = x + dx[d];

            if (0 <= ty && ty < h && 0 <= tx && tx < w &&
                tempField[ty][tx] != '*' && tempField[ty][tx] != '&' && dist[ty][tx] > dist[y][x] + 1) {
                dist[ty][tx] = dist[y][x] + 1;
                from[ty][tx] = { y, x };
                q.push(std::make_pair(ty, tx));
            }
        }
    }

    std::vector<std::pair<int, int>> way;
    if (dist[finishY][finishX] != INT_MAX) {
        int y = finishY;
        int x = finishX;

        while (y != -1 && x != -1) {            // ������ ��������� �������, �� ���
            auto [py, px] = from[y][x];
            way.push_back({ py,px });
            y = py;
            x = px;
        }
    }

    reverse(way.begin(), way.end());            // ��������� �������
    if (!way.empty()) {                         // ���� ������ �� ����
        way.erase(way.begin());                 // ������ �� ������ ����� {-1,-1}
        way.push_back({ finishY, finishX });    // ������� � ����� ��������� �����
    }
    return way;                                 // ������ �������
}

void SnakeGame::preSeput() {                                                // ���� ���������
    createWalls();                                                          // ���������� ����
    createSnake();                                                          // �������� ����
    createFood();                                                           // �������� ���
    showField();                                                            // ����� ����
}


