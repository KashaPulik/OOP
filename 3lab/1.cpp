#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    ContextSettings settings;

    settings.antialiasingLevel = 32;

    RenderWindow window(VideoMode(500, 300), "ABOBA", Style::Default, settings);

    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(250, 220, 100, 0));

        CircleShape circle(50.f);
        circle.setFillColor(Color(230, 0, 230));
        circle.setOutlineThickness(15.f);
        circle.setOutlineColor(Color(80, 220, 50));
        circle.move(15, 15);
        window.draw(circle);

        CircleShape triangle(65.f, 3);
        triangle.setPosition(125, 0);
        triangle.setFillColor(Color(Color::Blue));
        window.draw(triangle);

        CircleShape square(60.f, 4);
        square.setPosition(250, 0);
        square.setFillColor(Color::Red);
        window.draw(square);

        CircleShape octagon(0.5, 3);
        octagon.setPosition(380, 0);
        octagon.setFillColor(Color::Cyan);
        window.draw(octagon);

        ConvexShape convex;

        convex.setPointCount(5);

        convex.setPoint(0, Vector2f(0.f, 0.f));
        convex.setPoint(1, Vector2f(150.f, 10.f));
        convex.setPoint(2, Vector2f(120.f, 90.f));
        convex.setPoint(3, Vector2f(30.f, 100.f));
        convex.setPoint(4, Vector2f(5.f, 50.f));

        convex.setFillColor(Color::Black);

        convex.move(1, 150);

        window.draw(convex);

        RectangleShape rectangle(Vector2f(70.f, 100.f));

        rectangle.move(165, 150);

        rectangle.setFillColor(Color(175, 180, 240));

        window.draw(rectangle);

        window.display();
    }
}