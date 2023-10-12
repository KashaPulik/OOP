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
    tPoint() : x(0), y(0), dx(0), dy(0), color(sf::Color(255, 255, 255))
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
protected:
    size_t n_points;
    std::vector<tPoint> points;
    sf::VertexArray shape;
    sf::Color color;
    float dx;
    float dy;
    float r_angle;

public:
    tShape() : tPoint()
    {
        n_points = 0;
        shape.setPrimitiveType(sf::LinesStrip);
        color = sf::Color(255, 255, 255);
        dx = 0;
        dy = 0;
        r_angle = 0;
    }
    tShape(size_t init_n_points) : n_points(init_n_points)
    {
        points.resize(n_points);
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
    void set_n_points(size_t new_n_points)
    {
        n_points = new_n_points;
        shape.resize(n_points);
        points.resize(n_points);
    }
    size_t get_n_points()
    {
        return n_points;
    }
    void resize_points(size_t n_points)
    {
        points.resize(n_points);
    }
    void set_shape_point(size_t index, float new_x, float new_y)
    {
        if (index > n_points)
            return;
        points[index].setxy(new_x, new_y);
        shape[index].position = sf::Vector2f(new_x, new_y);
        if (index == 0 && n_points != 2)
        {
            points[n_points - 1] = points[0];
            shape[n_points - 1] = shape[0];
        }
    }
    void set_shape_position(float new_x, float new_y)
    {
        size_t cicle_n_points = n_points == 2 ? n_points : n_points - 1;
        float dxpos = new_x - points[0].get_x();
        float dypos = new_y - points[0].get_y();
        for (size_t i = 0; i < cicle_n_points; i++)
        {
            float new_x_for_each = points[i].get_x() + dxpos;
            float new_y_for_each = points[i].get_y() + dypos;
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
    sf::Vector2f rotatePoint(const sf::Vector2f &point, const sf::Vector2f &center, float angle)
    {
        angle = angle * (M_PI / 180.f);
        float s = sin(angle);
        float c = cos(angle);

        sf::Vector2f translated = point - center;

        float xnew = translated.x * c - translated.y * s;
        float ynew = translated.x * s + translated.y * c;

        return sf::Vector2f(xnew + center.x, ynew + center.y);
    }

    sf::Vector2f get_center_point()
    {
        sf::Vector2f center(0.f, 0.f);
        for (size_t i = 0; i < n_points; ++i)
        {
            center += shape[i].position;
        }
        return center /= static_cast<float>(n_points);
    }

    void rotate_shape()
    {
        sf::Vector2f center = get_center_point();

        for (size_t i = 0; i < n_points; ++i)
        {
            shape[i].position = rotatePoint(shape[i].position, center, r_angle);
            points[i].setxy(shape[i].position.x, shape[i].position.y);
        }
    }

    void solve_rotate_collision(int x_size, int y_size)
    {
        sf::Vector2f tmp_points[n_points];

        sf::Vector2f center = get_center_point();

        for (size_t i = 0; i < n_points; ++i)
        {
            tmp_points[i] = rotatePoint(shape[i].position, center, r_angle);
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
public:
    tLine() : tShape(2) {}
};

class tTriangle : public tShape
{
public:
    tTriangle() : tShape(4) {}
};

class tRectangle : public tShape
{
public:
    tRectangle() : tShape(5)
    {
        for (int i = 0; i < 5; i++)
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

class tEllipse : public tShape
{
protected:
    float a, b;
    float arc;

public:
    tEllipse() : tShape(), a(0), b(0) {}
    sf::Vector2f rotatePointEllipse(float a, float b, float angle)
    {
        angle = angle * (M_PI / 180.f);
        return sf::Vector2f(
            a * cos(angle),
            b * sin(angle));
    }

    void calculate_points_position()
    {
        float arc_for_each = 0;
        sf::Vector2f center = get_center_point();
        for (size_t i = 0; i < n_points; i++)
        {
            sf::Vector2f cur_point = sf::Vector2f(get_point_x(i), get_point_y(i));
            cur_point = rotatePointEllipse(a, b, arc_for_each);
            set_shape_point(i, cur_point.x + center.x, cur_point.y + center.y);
            arc_for_each += arc;
        }
    }
    void set_up_left_position()
    {
        set_shape_position(2 * a, b);
    }
    tEllipse(float init_a, float init_b) : tShape(std::max(init_a, init_b) * 8 + 1), a(init_a), b(init_b), arc(360.f/(std::max(init_a, init_b) * 8))
    {
        calculate_points_position();
        set_up_left_position();
    }
    void set_ab(float new_a, float new_b)
    {
        a = new_a;
        b = new_b;
        n_points = (size_t)(std::max(a, b) * 8 + 1);
        set_n_points(n_points);
        arc = 360.f / (n_points - 1);
        calculate_points_position();
    }
    void set_ellipse_position(float new_x, float new_y)
    {
        set_shape_position(2 * a + new_x, b + new_y);
    }
};

class tCircle : public tEllipse
{
private:
    float radius;

public:
    tCircle() : tEllipse(), radius(0) {}
    tCircle(float init_radius) : tEllipse(init_radius, init_radius), radius(init_radius) {}
    void set_radius(float new_radius)
    {
        radius = new_radius;
        set_ab(radius, radius);
    }
};

class tRhomb : public tShape
{
private:
    float length;
    float angle;

public:
    tRhomb() : tShape(5) {set_shape_point(0, 0, 0);}
    void calculate_points()
    {
        set_shape_point(1, get_point_x(0) + length, get_point_y(0));
        sf::Vector2f point = get_shape_object()[1].position;
        point = rotatePoint(sf::Vector2f(point.x + length, point.y), point, angle);
        set_shape_point(2, point.x, point.y);
        set_shape_point(3, point.x - length, point.y);
    }
    tRhomb(float init_length, float init_angle) : tShape(5), length(init_length), angle(init_angle)
    {
        set_shape_point(0, 0, 0);
        calculate_points();
    }
    void set_length(float new_length)
    {
        length = new_length;
        calculate_points();
    }
    void set_angle(float new_angle)
    {
        angle = new_angle;
        calculate_points();
    }
};

int main()
{
    srand(time(0));

    tLine line;
    line.set_shape_point(0, 50, 75);
    line.set_shape_point(1, 100, 175);
    line.set_shape_move(1, 2);
    line.set_shape_rotation(1.5);

    tTriangle triangle;
    triangle.set_shape_color(sf::Color::Magenta);
    triangle.set_shape_point(0, 0, 0);
    triangle.set_shape_point(1, 0, 60);
    triangle.set_shape_point(2, 30, 30);
    triangle.set_shape_position(50, 70);
    triangle.set_shape_move(-1, 2);
    triangle.set_shape_rotation(-1.3);

    tRectangle rectangle;
    rectangle.set_shape_color(sf::Color::Blue);
    rectangle.set_x_length(45);
    rectangle.set_y_length(35);
    rectangle.set_shape_move(2, 3);
    rectangle.set_shape_rotation(1);
    rectangle.set_shape_position(300, 350);

    tRhomb rhomb(90, 60);
    rhomb.set_shape_color(sf::Color::Red);
    rhomb.set_shape_move(1, -2);
    rhomb.set_shape_rotation(-1.7);
    rhomb.set_shape_position(200, 450);

    tEllipse ellipse(150.f, 100.f);
    ellipse.set_shape_color(sf::Color::Yellow);
    ellipse.set_shape_move(-2, 1);
    ellipse.set_shape_rotation(-1);
    ellipse.set_ellipse_position(150, 100);

    tCircle circle(100.f);
    circle.set_shape_color(sf::Color::Green);
    circle.set_shape_move(3, -1);
    circle.set_ellipse_position(50, 80);
    
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

        line.solve_shape_collision(x_size, y_size);
        line.move_shape();
        line.solve_rotate_collision(x_size, y_size);
        line.rotate_shape();

        triangle.solve_shape_collision(x_size, y_size);
        triangle.move_shape();
        triangle.solve_rotate_collision(x_size, y_size);
        triangle.rotate_shape();

        rectangle.solve_shape_collision(x_size, y_size);
        rectangle.move_shape();
        rectangle.solve_rotate_collision(x_size, y_size);
        rectangle.rotate_shape();

        rhomb.solve_shape_collision(x_size, y_size);
        rhomb.move_shape();
        rhomb.solve_rotate_collision(x_size, y_size);
        rhomb.rotate_shape();

        ellipse.solve_rotate_collision(x_size, y_size);
        ellipse.rotate_shape();
        ellipse.solve_shape_collision(x_size, y_size);
        ellipse.move_shape();

        circle.solve_shape_collision(x_size, y_size);
        circle.move_shape();

        window.draw(line.get_shape_object());
        window.draw(triangle.get_shape_object());
        window.draw(rectangle.get_shape_object());
        window.draw(rhomb.get_shape_object());
        window.draw(ellipse.get_shape_object());
        window.draw(circle.get_shape_object());

        window.display();
    }
    return 0;
}