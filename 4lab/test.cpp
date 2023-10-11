#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Circle using LineStrip");

    const sf::Vector2f center(400.f, 300.f);
    const float radius = 200.f;
    const unsigned int pointCount = 100; // Количество вершин. Чем больше, тем гладче окружность.

    sf::VertexArray circle(sf::LineStrip, pointCount + 1);

    for (unsigned int i = 0; i < pointCount + 1; ++i)
    {
        float angle = 2 * 3.14159265358979323846f * i / pointCount;
        float x = center.x + radius * std::cos(angle);
        float y = center.y + radius * std::sin(angle);
        
        circle[i].position = sf::Vector2f(x, y);
        circle[i].color = sf::Color::Red;
    }
    circle[pointCount].position = circle[0].position; // замыкающая вершина

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
