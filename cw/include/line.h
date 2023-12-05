#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class line : public sf::VertexArray {
public:
    line();
    line(float x1, float y1, float x2, float y2);
    void set_position(float x1, float y1, float x2, float y2);
    void set_color(const sf::Color& color);
    sf::VertexArray get_VertexArray();
};