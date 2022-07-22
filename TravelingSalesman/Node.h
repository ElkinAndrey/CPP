#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <cmath>

#include "Graph.h"

using namespace std;
using namespace sf;

class Node {
private:
    char str; // Название звена
    int X; // Координата X у звена
    int Y; // Координата Y у звена
    sf::CircleShape circle; // Круг
    int radius; // Радиус круга
    Font font; // Шрифт текста
    Text text; // Текст

    // Установка нужных параметров у круга и текста
    void Config() {
        circle.setRadius(radius);
        circle.setPosition(X - radius, Y - radius);
        circle.setFillColor(sf::Color(57, 201, 78));

        font.loadFromFile("VarelaRound-Regular.ttf");//передаем нашему шрифту файл шрифта
        text.setFillColor(sf::Color(255, 255, 255));
        text.setString(str);//задает строку тексту
        text.setFont(font);
        text.setCharacterSize(radius);
        text.setOutlineColor(Color::Red);
        text.setPosition(X - 1.1 * text.getGlobalBounds().width / 2, Y - 1.8 * text.getGlobalBounds().height / 2);
    }
public:
    // Конструктор без параметров
    Node() {}

    // Конструктор, принимающий символ, радиус и позицию
    Node(char str, int radius, int X, int Y) {
        this->str = str;
        this->radius = radius;
        this->X = X;
        this->Y = Y;
    }
    // Конструктор копирования
    Node(const Node& node) {
        this->str = node.str;
        this->radius = node.radius;
        this->X = node.X;
        this->Y = node.Y;
    }

    // Получить X позицию звена
    int GetX() {
        return X;
    }

    // Получить Y позицию звена
    int GetY() {
        return Y;
    }

    // Получить радиус звена
    int GetRadius() {
        return radius;
    }

    // Нарисовать звено
    void Draw(sf::RenderWindow& window) {
        Config();
        window.draw(this->circle);
        window.draw(this->text);
    }

};