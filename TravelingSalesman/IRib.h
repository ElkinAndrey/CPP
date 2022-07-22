#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// Интерфейс-стрелка
class IRib {
public:
    IRib() {}
    virtual void Draw(sf::RenderWindow& window) = 0; // отрисовка стрелки
};