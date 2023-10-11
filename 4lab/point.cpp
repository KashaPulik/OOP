#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

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

class tShape : public tPoint
{
private:
    tPoint *points;
    sf::VertexArray shape;
    sf::Color color;
    size_t n_points;
    float dx;
    float dy;
    float r_angle;

public:
    tShape()
    {
        points = NULL;
        n_points = 0;
        shape.setPrimitiveType(sf::LinesStrip);
        color = sf::Color(255, 255, 255);
        dx = 0;
        dy = 0;
        r_angle = 0;
    }
    tShape(size_t init_n_points) : n_points(init_n_points)
    {
        points = new tPoint[n_points];
        if (n_points == 2)
            shape.setPrimitiveType(sf::Lines);
        else
            shape.setPrimitiveType(sf::LinesStrip);
        color = sf::Color(255, 255, 255);
        dx = 0;
        dy = 0;
        r_angle = 0;
        shape.resize(n_points);
    }
    ~tShape()
    {
        delete[] points;
    }
    void set_shape_point(size_t index, float new_x, float new_y)
    {
        if (index > n_points)
            return;
        points[index].setxy(new_x, new_y);
        shape[index].position = sf::Vector2f(new_x, new_y);
        if(index == 0 && n_points != 2) {
            points[n_points - 1] = points[0];
            shape[n_points - 1] = shape[0];
        }
    }
    void set_shape_position(float new_x, float new_y)
    {
        float dxpos = new_x - points[0].get_x();
        float dypos = new_y - points[0].get_y();
        for (size_t i = 0; i < n_points; i++)
        {
            float new_x_for_each = points[i].get_x() + dxpos;
            float new_y_for_each = points[i].get_y() + dypos;
            points[i].setxy(new_x_for_each, new_y_for_each);
            set_shape_point(i, new_x_for_each, new_y_for_each);
        }
    }
    void set_shape_move(float new_dx, float new_dy)
    {
        for (size_t i = 0; i < n_points; i++)
        {
            points[i].setmove(new_dx, new_dy);
        }
        dx = new_dx;
        dy = new_dy;
    }
    void set_shape_color(sf::Color new_color)
    {
        for (size_t i = 0; i < n_points; i++)
        {
            shape[i].color = new_color;
        }
        color = new_color;
    }
    void set_shape_rotation(float new_r_angle)
    {
        r_angle = new_r_angle;
    }
    sf::Color get_shape_color()
    {
        return color;
    }
    tPoint get_point(size_t index)
    {
        return points[index];
    }
    float get_point_x(size_t index)
    {
        return points[index].get_x();
    }
    float get_point_y(size_t index)
    {
        return points[index].get_y();
    }
    void move_shape()
    {
        set_shape_position(points[0].get_x() + dx, points[0].get_y() + dy);
    }
    void solve_shape_collision(int size_x, int size_y)
    {
        for (size_t i = 0; i < n_points; i++)
        {
            if (points[i].solve_collision(size_x, size_y))
            {
                set_shape_move(points[i].get_dx(), points[i].get_dy());
                break;
            }
        }
    }
    sf::Vector2f rotatePoint(const sf::Vector2f &point, float angle)
    {
        return sf::Vector2f(
            point.x * cos(angle) - point.y * sin(angle),
            point.x * sin(angle) + point.y * cos(angle));
    }
    void rotate_shape()
    {
        sf::Vector2f center(0.f, 0.f);
        for (size_t i = 0; i < n_points - 1; ++i)
        {
            center += shape[i].position;
        }
        center /= static_cast<float>(n_points - 1);

        for (size_t i = 0; i < n_points; ++i)
        {
            shape[i].position -= center;
        }

        float angle = r_angle * (M_PI / 180.f);
        for (size_t i = 0; i < n_points; ++i)
        {
            shape[i].position = rotatePoint(shape[i].position, angle);
        }

        for (size_t i = 0; i < n_points; ++i)
        {
            sf::Vector2f cur_point;
            shape[i].position += center;
            cur_point = shape[i].position;
            points[i].setxy(cur_point.x, cur_point.y);
        }
    }
    void solve_rotate_collision(int x_size, int y_size)
    {
        sf::Vector2f center(0.f, 0.f);
        sf::Vector2f tmp_points[n_points];
        for (size_t i = 0; i < n_points - 1; ++i)
        {
            center += shape[i].position;
        }
        center /= static_cast<float>(n_points - 1);

        for (size_t i = 0; i < n_points; ++i)
        {
            tmp_points[i] = shape[i].position - center;
        }

        float angle = r_angle * (M_PI / 180.f);
        for (size_t i = 0; i < n_points; ++i)
        {
            tmp_points[i] = rotatePoint(tmp_points[i], angle);
        }

        for (size_t i = 0; i < n_points; ++i)
        {
            tmp_points[i] += center;
            if (tmp_points[i].x >= x_size || tmp_points[i].x <= 0 || tmp_points[i].y >= y_size || tmp_points[i].y <= 0)
            {
                r_angle = -r_angle;
                return;
            }
        }
    }
    sf::VertexArray get_shape_object()
    {
        return shape;
    }
};

class tLine : public tShape
{
private:
    tShape line;

public:
    tLine() : tShape(2){}
};

class tTriangle : public tShape
{
private:
    tShape triange;
public:
    tTriangle() : tShape(4){}
};

class tRectangle : public tShape
{
private:
    tShape rectangle;
public:
    tRectangle() : tShape(5)
    {
        for(int i = 0; i < 5; i++)
            set_shape_point(i, 0, 0);
    }
    void set_x_length(float length)
    {
        set_shape_point(1, get_point_x(1) + length, get_point_y(1));
        set_shape_point(2, get_point_x(2) + length, get_point_y(2));
    }
    void set_y_length(float length)
    {
        set_shape_point(2, get_point_x(2), get_point_y(2) + length);
        set_shape_point(3, get_point_x(3), get_point_y(3) + length);
    }
};

// int main()
// {
//     srand(time(0));
//     int n_lines = 10;
//     // tLine lines[n_lines];
//     std::vector<tLine> lines(n_lines);
//     for (int i = 0; i < n_lines; i++)
//     {
//         lines[i].set_points(rand() % (x_size / 2), rand() % (y_size / 2), rand() % (x_size / 2), rand() % (y_size / 2));
//         lines[i].set_line_color(sf::Color(rand() % 256, rand() % 256, rand() % 256));
//         lines[i].set_move(rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1), rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1));
//         lines[i].set_line_rotation(0.5);
//     }
//     sf::RenderWindow window(sf::VideoMode(x_size, y_size), "ABOBA");
//     window.setPosition(sf::Vector2i(300, 300));
//     window.setFramerateLimit(60);

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//         window.clear();
//         for (int i = 0; i < n_lines; i++)
//         {
//             lines[i].solve_line_collision(x_size, y_size);
//             lines[i].move_line();
//             lines[i].solve_rotate_collision();
//             lines[i].rotate_line();
//             window.draw(lines[i].get_line_object());
//         }
//         window.display();
//     }
//     return 0;
// }

// int main()
// {
//     srand(time(0));
//     int n_lines = 10;
//     // tLine lines[n_lines];
//     std::vector<tLine> lines(n_lines);
//     for (int i = 0; i < n_lines; i++)
//     {
//         lines[i].set_shape_point(0, rand() % (x_size / 2), rand() % (y_size / 2));
//         lines[i].set_shape_point(1, rand() % (x_size / 2), rand() % (y_size / 2));
//         lines[i].set_shape_color(sf::Color(rand() % 256, rand() % 256, rand() % 256));
//         lines[i].set_shape_move(rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1), rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1));
//         lines[i].set_shape_rotation(0.5);
//     }
//     sf::RenderWindow window(sf::VideoMode(x_size, y_size), "ABOBA");
//     window.setPosition(sf::Vector2i(300, 300));
//     window.setFramerateLimit(60);

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//         window.clear();
//         for (int i = 0; i < n_lines; i++)
//         {
//             lines[i].solve_rotate_collision(x_size, y_size);
//             lines[i].rotate_shape();
//             lines[i].solve_shape_collision(x_size, y_size);
//             lines[i].move_shape();
//             window.draw(lines[i].get_shape_object());
//         }
//         window.display();
//     }
//     return 0;
// }

// int main()
// {
//     srand(time(0));
//     int n_shapes = 10;
//     // tLine lines[n_lines];
//     std::vector<tTriangle> lines(n_shapes);
//     for (int i = 0; i < n_shapes; i++)
//     {
//         lines[i].set_shape_point(0, rand() % (x_size / 2), rand() % (y_size / 2));
//         lines[i].set_shape_point(1, rand() % (x_size / 2), rand() % (y_size / 2));
//         lines[i].set_shape_point(2, rand() % (x_size / 2), rand() % (y_size / 2));
//         lines[i].set_shape_color(sf::Color(rand() % 256, rand() % 256, rand() % 256));
//         lines[i].set_shape_move(rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1), rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1));
//         lines[i].set_shape_rotation(0.5);
//     }
//     sf::RenderWindow window(sf::VideoMode(x_size, y_size), "ABOBA");
//     window.setPosition(sf::Vector2i(300, 300));
//     window.setFramerateLimit(60);

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//         window.clear();
//         for (int i = 0; i < n_shapes; i++)
//         {
//             lines[i].solve_rotate_collision(x_size, y_size);
//             lines[i].rotate_shape();
//             lines[i].solve_shape_collision(x_size, y_size);
//             lines[i].move_shape();
//             window.draw(lines[i].get_shape_object());
//         }
//         window.display();
//     }
//     return 0;
// }

int main()
{
    srand(time(0));
    int n_shapes = 10;
    // tLine lines[n_lines];
    std::vector<tRectangle> lines(n_shapes);
    for (int i = 0; i < n_shapes; i++)
    {
        lines[i].set_x_length(rand() % (x_size / 2));
        lines[i].set_y_length(rand() % (x_size / 2));
        lines[i].set_shape_position(15, 15);
        lines[i].set_shape_color(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        lines[i].set_shape_move(rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1), rand() % 2 == 0 ? rand() % 2 + 1 : -(rand() % 2 + 1));
        lines[i].set_shape_rotation(0.5);
    }
    sf::RenderWindow window(sf::VideoMode(x_size, y_size), "ABOBA");
    window.setPosition(sf::Vector2i(300, 300));
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < n_shapes; i++)
        {
            lines[i].solve_rotate_collision(x_size, y_size);
            lines[i].rotate_shape();
            lines[i].solve_shape_collision(x_size, y_size);
            lines[i].move_shape();
            window.draw(lines[i].get_shape_object());
        }
        window.display();
    }
    return 0;
}