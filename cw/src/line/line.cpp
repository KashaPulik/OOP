#include <SFML/Graphics.hpp>
#include <iostream>

#include <line.h>

line::line()
{
    this->setPrimitiveType(sf::Lines);
    this->resize(2);
    set_color(sf::Color::Red);
}
line::line(float x1, float y1, float x2, float y2)
{
    this->setPrimitiveType(sf::Lines);
    this->resize(2);
    set_color(sf::Color::Red);
    set_position(x1, y1, x2, y2);
}
void line::set_position(float x1, float y1, float x2, float y2)
{
    (*this)[0].position = sf::Vector2f(x1, y1);
    (*this)[1].position = sf::Vector2f(x2, y2);
}
void line::set_color(const sf::Color& color)
{
    (*this)[0].color = color;
    (*this)[1].color = color;
}
sf::VertexArray line::get_VertexArray()
{
    return *this;
}
