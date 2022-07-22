#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <cmath>

#include "Graph.h"
#include "Node.h"
#include "IRib.h"
#include "RibUnilateral.h"
#include "RibBilateral.h"

using namespace std;
using namespace sf;

// Класс, ресующий в окне
class Map {
private:
    vector<Node> Nodes; // Звенья графа
    Graph graph; // Граф
    int size; // Размер графа
public:
    // Конструктор, принимающий граф
    Map(Graph graph) {
        this->graph = graph; // Копирование графа
        this->size = graph.GetSize(); // Установка размера графа
        Nodes = vector<Node>(size, Node()); // Указывается количество звеньев
        for (int i = 0; i < size; i++) // Добавление звеньев
            Nodes[i] = Node(65 + i, 40, 400 + 300 * cos(2 * PI * i / size), 400 + 300 * sin(2 * PI * i / size));
    }

    void DrawGraph(sf::RenderWindow& window) {
        vector<vector<int>> mas = graph.GetGraph(); // Граф в виде матрицы

        //Нарисовать стрелки
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                IRib* c; // Интерфейс стрелки
                if (mas[i][j] != -1 and mas[j][i] != -1) // Если нужно нарисовать стрелку в двух направлениях
                    c = new RibBilateral(Nodes[i], Nodes[j], mas[i][j], mas[j][i], Color(255, 255, 255), Color(255, 255, 255));
                else if (mas[i][j] != -1) // Если от первого звена ко второму
                    c = new RibUnilateral(Nodes[i], Nodes[j], mas[i][j], Color(255, 255, 255));
                else if (mas[j][i] != -1)   // Если от второго звена к первому
                    c = new RibUnilateral(Nodes[j], Nodes[i], mas[j][i], Color(255, 255, 255));
                else
                    continue;
                c->Draw(window); // Нарисовать стрелку
            }
        }

        // Нарисовать красные стрелки
        for (list<char>::iterator i = graph.shortestDetour.begin(); i != graph.shortestDetour.end();) {
            IRib* c; // Интерфейс стрелки
            int a = int(*i) - 65;
            i++;
            if (i == graph.shortestDetour.end()) { // Нарисовать стрелку от последнего звена к первому
                int b = int(*graph.shortestDetour.begin()) - 65;
                if (mas[a][b] != -1 and mas[a][b] != -1)  // Если нужно нарисовать стрелку в двух направлениях
                    c = new RibBilateral(Nodes[a], Nodes[b], mas[a][b], mas[b][a], Color(255, 0, 0), Color(255, 255, 255));
                else if (mas[a][b] != -1)// Если от первого звена ко второму
                    c = new RibUnilateral(Nodes[a], Nodes[b], mas[a][b], Color(255, 0, 0));
                else if (mas[b][a] != -1) // Если от второго звена к первому
                    c = new RibUnilateral(Nodes[b], Nodes[a], mas[b][a], Color(255, 0, 0));
                else
                    break;
                c->Draw(window);
                break;
            }
            int b = int(*i) - 65;
            if (mas[a][b] != -1 and mas[a][b] != -1)// Если нужно нарисовать стрелку в двух направлениях
                c = new RibBilateral(Nodes[a], Nodes[b], mas[a][b], mas[b][a], Color(255, 0, 0), Color(255, 255, 255));
            else if (mas[a][b] != -1)// Если от первого звена ко второму
                c = new RibUnilateral(Nodes[a], Nodes[b], mas[a][b], Color(255, 0, 0));
            else if (mas[b][a] != -1)// Если от второго звена к первому
                c = new RibUnilateral(Nodes[b], Nodes[a], mas[b][a], Color(255, 0, 0));
            else
                continue;
            c->Draw(window);
        }

        // Нарисовать звенья
        for (int i = 0; i < size; i++) {
            Nodes[i].Draw(window);
        }
    }

    // Отрисовать окно
    void Draw(sf::RenderWindow& window) {
        DrawGraph(window);
    }
};