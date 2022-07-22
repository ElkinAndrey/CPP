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

// ������� �������������� ������ ��� ������
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

// �������� �����
Graph graph(mas4);

// �������, ��������� ����, � ������� ����� ������������ ����
void SetWindow() {
    sf::RenderWindow window(sf::VideoMode(900, 900), ""); // ��������� ����
    while (window.isOpen()) // ���� ����
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        window.clear();

        // ���������� � ���� ����������� ������������� �����
        Map a(graph);
        a.Draw(window);

        window.display();
    }
}

// �������, ��������� �������, � ������� ����� ������ �������
void SetConsol() {
    string str;
    int a;
    char b;
    while (true) {
        // ������ ������������ ������ �������
        cout
            << "1 �������� ����\n"
            << "2 �������� ����� �����\n"
            << "3 ��������� ���� ���������� �������\n"
            << "4 �������� ������ �����\n"
            << "5 ������ ������ ����������\n"
            << "6 ������� ������� �����\n"
            << "7 ������� ���������\n\n"
            << "�������� �������� : ";
        cin >> str;

        graph.shortestDetour.clear(); // ��� ������ ������ �������, ������� ������ � ����������� ����� ���������
        switch (str[0])
        {
        case '1': // �������� ����
            graph.SetGraph();
            cout << '\n';
            break;
        case '2': // �������� ����� �����
            while (true) {
                cout << "������� ����� : ";
                cin >> b;
                if (b - 65 < graph.GetSize() and b - 65 >= 0) {
                    graph.SetNode(b);
                    break;
                }
            }
            cout << '\n';
            break;
        case '3': // ��������� ���� ���������� �������
            graph.SetGraphRand();
            break;
        case '4': // �������� ������ �����
            while (true) {
                cout << "������� ����� ������ : ";
                cin >> str;
                a = atoi(str.c_str());
                if (a > 0) {
                    graph.SetSize(atoi(str.c_str()));
                    break;
                }
            }
            cout << '\n';
            break;
        case '5': // ������ ������ ����������
            graph.ShortestDetour();
            for (list<char>::iterator i = graph.shortestDetour.begin(); i != graph.shortestDetour.end(); i++) {
                cout << *i << ' ';
            }
            cout << '\n';
            cout << '\n';
            break;
        case '6': // ������� ������� �����
            graph.Print();
            cout << '\n';
            break;
        case '7': // ������� ���������
            exit(0);
            break;
        default:
            cout << "\n�������� ������ ��������!!!\n\n";
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

    thread w(SetWindow); // �������� ������ ���� � ������
    thread c(SetConsol); // �������� ������ �������
    w.join(); // ������ ������ ���� � ������
    c.join(); // ������ ������ �������

    return 0;
}