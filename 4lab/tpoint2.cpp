#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

enum window_size
{
    x_size = 800,
    y_size = 600
};

class tPoint
{
private:
    float x;
    float y;
    float dx;
    float dy;
    sf::Color color;
    sf::VertexArray point;

public:
    tPoint()
    {
        point.setPrimitiveType(sf::Points);
        point.resize(1);
    }
    void setxy(float new_x, float new_y)
    {
        x = new_x;
        y = new_y;
        point[0].position = sf::Vector2f(x, y);
    }
    void setmove(float new_dx, float new_dy)
    {
        dx = new_dx;
        dy = new_dy;
    }
    void setcolor(sf::Color new_color)
    {
        point[0].color = new_color;
    }
    float get_x()
    {
        return x;
    }
    float get_y()
    {
        return y;
    }
    float get_dx()
    {
        return dx;
    }
    float get_dy()
    {
        return dy;
    }
    void rand_init(int x_size, int y_size)
    {
        setxy(rand() % x_size, rand() % y_size);
        setmove(rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1), rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1));
        setcolor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
    }
    bool solve_collision(int x_size, int y_size)
    {
        bool collision = 0;
        if (x + dx > x_size || x + dx < 0)
        {
            collision = 1;
            setmove(-dx, dy);
        }
        if (y + dy > y_size || y + dy < 0)
        {
            collision = 1;
            setmove(dx, -dy);
        }
        return collision;
    }
    void move_point()
    {
        setxy(x + dx, y + dy);
    }
    void random_set_move()
    {
        dx = rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1);
        dy = rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1);
    }
    sf::VertexArray get_object()
    {
        return point;
    }
};

int main()
{
    srand(time(0));
    int n_points;
    int status = 1;

    std::cout << "Введите количество точек: ";
    std::cin >> n_points;

    sf::RenderWindow window(sf::VideoMode(x_size, y_size), "ABOBA");
    window.setPosition(sf::Vector2i(300, 200));
    window.setFramerateLimit(60);

    std::vector<tPoint> points(n_points);

    for (int i = 0; i < n_points; i++)
        points[i].rand_init(x_size, y_size);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    status = -status;
            }
        }

        if (status > 0)
        {
            for (int i = 0; i < n_points; i++)
            {
                points[i].solve_collision(x_size, y_size);
                points[i].move_point();
            }
        }
        else
        {
            for (int i = 0; i < n_points; i++)
            {
                points[i].random_set_move();
                points[i].solve_collision(x_size, y_size);
                points[i].move_point();
            }
        }
        window.clear();
        for (int i = 0; i < n_points; i++)
            window.draw(points[i].get_object());
        window.display();
    }
    return 0;
}