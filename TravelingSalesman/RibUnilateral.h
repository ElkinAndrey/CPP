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

using namespace std;
using namespace sf;

const double PI = 3.141592653589793; // число Pi

// Односторонняя стрелка
class RibUnilateral : public IRib {
private:
    Node node1;// первое звено
    Node node2; // второе звено
    int len; // путь от перового ко второму звену
    sf::Color color; // Цвет пути
public:
    // Конструктор с параметрами
    RibUnilateral(const Node& node1, const Node& node2, int len, sf::Color color) {
        this->node1 = node1;
        this->node2 = node2;
        this->len = len;
        this->color = color;
    }

    // ОТрисовка стрелки
    void Draw(sf::RenderWindow& window) override {
        // Рисуем линию
        VertexArray line(sf::LinesStrip, 2);
        line[0].position.x = node1.GetX();
        line[0].position.y = node1.GetY();
        line[0].color = color;
        line[1].position.x = node2.GetX();
        line[1].position.y = node2.GetY();
        line[1].color = color;
        window.draw(line);

        // Рисуем треугольник
        double Rotation = PI; // Угол наклона
        if (node2.GetX() - node1.GetX() > 0)
            Rotation = atan((double)(node2.GetY() - node1.GetY()) / (double)(node2.GetX() - node1.GetX())) + PI / 2;
        else if (node2.GetX() - node1.GetX() < 0)
            Rotation = atan((double)(node2.GetY() - node1.GetY()) / (double)(node2.GetX() - node1.GetX())) - PI / 2;
        else if (node2.GetY() - node1.GetY() < 0)
            Rotation = 0;

        int PositionX = node2.GetX() - node2.GetRadius() * sin(Rotation) - 8 * cos(Rotation); // Позиция по X
        int PositionY = node2.GetY() + node2.GetRadius() * cos(Rotation) - 8 * sin(Rotation); // Позиция по Y

        sf::CircleShape triangle(8, 3);
        triangle.setRotation(180 * Rotation / PI);
        triangle.setPosition(PositionX, PositionY);
        triangle.setFillColor(color);
        window.draw(triangle);

        // Рисуем длину
        int CenterX = (node1.GetX() + node2.GetX()) / 2;
        int CenterY = (node1.GetY() + node2.GetY()) / 2;

        int sizeSquare = 20;
        RectangleShape square(Vector2f(sizeSquare, sizeSquare));
        /*square.setOutlineThickness(2);
        square.setOutlineColor(Color(57, 201, 78));*/
        square.setPosition(CenterX - sizeSquare / 2, CenterY - sizeSquare / 2);
        window.draw(square);

        Font font;
        Text text;
        font.loadFromFile("VarelaRound-Regular.ttf");//передаем нашему шрифту файл шрифта
        text.setString(to_string(len));//задает строку тексту
        text.setFont(font);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(Color(57, 201, 78));
        text.setCharacterSize(sizeSquare / 1.3);
        text.setPosition(CenterX - 1.1 * text.getGlobalBounds().width / 2, CenterY - 1.8 * text.getGlobalBounds().height / 2);
        window.draw(text);
    }
};  