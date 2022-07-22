#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <thread>

#include "Graph.h"
#include "Map.h"

using namespace std;
using namespace sf;

// Примеры первоначальных матриц для графов
vector<vector<int>> mas = {
        {-1, 5, 11, 9},
        {10, -1, 8, 7},
        {7, 14, -1, 8},
        {12, 6, 15, -1}
};
vector<vector<int>> mas2 = {
        {0, 10, 6, 8, 0, 0, 0, 0, 0},
        {0, 0, 0, 5, 13, 0, 11, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0, 0},
        {0, 0, 2, 0, 5, 7, 12, 0, 0},
        {0, 0, 0, 0, 0, 9, 0, 0, 12},
        {0, 0, 0, 0, 0, 0, 0, 8, 10},
        {0, 0, 0, 0, 0, 4, 0, 6, 16},
        {0, 0, 0, 0, 0, 0, 0, 0, 15},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
};
vector<vector<int>> mas3 = {
        {-1, 7, 9, -1, 4},
        {-1, -1, 8, 12, -1},
        {-1, -1, -1, 11, 2},
        {-1, 3, 11, -1, -1},
        {-1, -1, 2, -1, -1}
};
vector<vector<int>> mas4 = {
        {-1, 7, 9, 4, 4},
        {12, -1, 8, 12, 11},
        {6, 5, -1, 11, 2},
        {4, 3, 11, -1, 1},
        {9, 3, 2, 8, -1}
};

// Создание графа
Graph graph(mas4);

// Функция, создающая окно, в котором будет отображаться граф
void SetWindow() {
    sf::RenderWindow window(sf::VideoMode(900, 900), ""); // Создается окно
    while (window.isOpen()) // Цикл окна
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        window.clear();

        // Добавление в окно графическое представление графа
        Map a(graph);
        a.Draw(window);

        window.display();
    }
}

// Функция, создающая консоль, в которой нужно писать команды
void SetConsol() {
    string str;
    int a;
    char b;
    while (true) {
        // Просим пользователя ввести команду
        cout
            << "1 Изменить граф\n"
            << "2 Изменить звено графа\n"
            << "3 Заполнить граф случайными числами\n"
            << "4 Изменить размер графа\n"
            << "5 Решить задачу Комивояжёра\n"
            << "6 Вывести таблицу графа\n"
            << "7 Закрыть программу\n\n"
            << "Выберете действие : ";
        cin >> str;

        graph.shortestDetour.clear(); // При выборе другой команды, регение задачи о комивояжере будет убираться
        switch (str[0])
        {
        case '1': // Изменить граф
            graph.SetGraph();
            cout << '\n';
            break;
        case '2': // Изменить звено графа
            while (true) {
                cout << "Введите звено : ";
                cin >> b;
                if (b - 65 < graph.GetSize() and b - 65 >= 0) {
                    graph.SetNode(b);
                    break;
                }
            }
            cout << '\n';
            break;
        case '3': // Заполнить граф случайными числами
            graph.SetGraphRand();
            break;
        case '4': // Изменить размер графа
            while (true) {
                cout << "Введите новый размер : ";
                cin >> str;
                a = atoi(str.c_str());
                if (a > 0) {
                    graph.SetSize(atoi(str.c_str()));
                    break;
                }
            }
            cout << '\n';
            break;
        case '5': // Решить задачу Комивояжёра
            graph.ShortestDetour();
            for (list<char>::iterator i = graph.shortestDetour.begin(); i != graph.shortestDetour.end(); i++) {
                cout << *i << ' ';
            }
            cout << '\n';
            cout << '\n';
            break;
        case '6': // Вывести таблицу графа
            graph.Print();
            cout << '\n';
            break;
        case '7': // Закрыть программу
            exit(0);
            break;
        default:
            cout << "\nВыберете другое действие!!!\n\n";
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(0));
    system("chcp1251");
    system("cls");

    thread w(SetWindow); // Создание потока окна с графом
    thread c(SetConsol); // Создание потока консоли
    w.join(); // Запуск потока окна с графом
    c.join(); // Запуск потока консоли

    return 0;
}