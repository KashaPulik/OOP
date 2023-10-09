#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;

using namespace std;

enum window_size
{
    x_size = 800,
    y_size = 600
};

class tPoint
{
private:
    int *dx;
    int *dy;
    int n_points;
    VertexArray points;

public:
    tPoint(int size) : n_points(size)
    {
        dx = new int[n_points];
        dy = new int[n_points];
        points.setPrimitiveType(Points);
        points.resize(n_points);
    }
    ~tPoint()
    {
        delete[] dx;
        delete[] dy;
    }
    void setxy(int index, int new_x, int new_y)
    {
        if (index >= 0 && index < n_points)
            points[index].position = Vector2f(new_x, new_y);
    }
    void setmove(int index, int new_dx, int new_dy)
    {
        if (index >= 0 && index < n_points)
        {
            dx[index] = new_dx;
            dy[index] = new_dy;
        }
    }
    void setcolor(int index, Color new_color)
    {
        if (index >= 0 && index < n_points)
            points[index].color = new_color;
    }
    int get_x(int index)
    {
        if (index >= 0 && index < n_points)
            return (int)points[index].position.x;
        return -1;
    }
    int get_y(int index)
    {
        if (index >= 0 && index < n_points)
            return (int)points[index].position.y;
        return -1;
    }
    int get_dx(int index)
    {
        if (index >= 0 && index < n_points)
            return dx[index];
        return -1;
    }
    int get_dy(int index)
    {
        if (index >= 0 && index < n_points)
            return dy[index];
        return -1;
    }
    void rand_init(int x_size, int y_size)
    {
        srand(time(0));
        for (int i = 0; i < n_points; i++)
        {
            setxy(i, rand() % x_size, rand() % y_size);
            setmove(i, rand() % 2 == 0 ? rand() % 4 + 1 : -(rand() % 4 + 1), rand() % 2 == 0 ? rand() % 4 + 1 : -(rand() % 4 + 1));
            setcolor(i, Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }
    void solve_collision(int x_size, int y_size)
    {
        for (int i = 0; i < n_points; i++)
        {
            if (get_x(i) + get_dx(i) > x_size || get_x(i) + get_dx(i) < 0)
                setmove(i, -(get_dx(i)), get_dy(i));
            if (get_y(i) + get_dy(i) > y_size || get_y(i) + get_dy(i) < 0)
                setmove(i, get_dx(i), -(get_dy(i)));
        }
    }
    void move_points()
    {
        for(int i = 0; i < n_points; i++)
            setxy(i, get_x(i) + get_dx(i), get_y(i) + get_dy(i));
    }
    void random_move_points()
    {
        int dx, dy;
        for(int i = 0; i < n_points; i++)
        {
            dx = rand() % 2 == 0 ? rand()%2 + 1 : -(rand()%2 + 1);
            dy = rand() % 2 == 0 ? rand()%2 + 1 : -(rand()%2 + 1);
            if (get_x(i) + dx > x_size || get_x(i) + dx < 0)
                dx = -dx;
            if (get_y(i) + dy > y_size || get_y(i) + dy < 0)
                dy = -dy;
            setxy(i, get_x(i) + dx, get_y(i) + dy);
        }
    }
    VertexArray get_object()
    {
        return points;
    }
};

int main()
{
    int n_points;
    int status = 1;

    cout << "Введите количество точек: ";
    cin >> n_points;
    RenderWindow window(VideoMode(x_size, y_size), "ABOBA");
    window.setPosition(Vector2i(300, 200));
    window.setFramerateLimit(30);

    tPoint points(n_points);
    points.rand_init(x_size, y_size);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed) {
                if(event.mouseButton.button == Mouse::Left)
                    status = -status;
            }
        }
        points.solve_collision(x_size, y_size);
        if(status > 0)
            points.move_points();
        else
            points.random_move_points();
        window.clear();
        window.draw(points.get_object());
        window.display();
    }
    return 0;
}