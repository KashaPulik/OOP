#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

class shapes
{
private:
    float *x;
    float *y;
    float dx;
    float dy;
    float r_angle;
    size_t n_points;
    sf::ConvexShape shape;

public:
    shapes(size_t nubmer_of_points) : n_points(nubmer_of_points)
    {
        dx = 0;
        dy = 0;
        x = new float[n_points];
        y = new float[n_points];
        shape.setPointCount(n_points);
    }
    ~shapes()
    {
        delete[] x;
        delete[] y;
    }
    void set_point_xy(size_t index, double new_x, double new_y)
    {
        if (index < n_points)
        {
            x[index] = new_x;
            y[index] = new_y;
            shape.setPoint(index, sf::Vector2f(new_x, new_y));
        }
    }
    void setmove(float new_dx, float new_dy)
    {
        dx = new_dx;
        dy = new_dy;
    }
    void set_r_angle(float new_angle)
    {
        r_angle = new_angle;
    }
    void setcolor(sf::Color new_color)
    {
        shape.setFillColor(new_color);
    }
    float get_point_x(size_t index)
    {
        if (index < n_points)
            return x[index];
        return -1;
    }
    float get_point_y(size_t index)
    {
        if (index < n_points)
            return y[index];
        return -1;
    }
    float get_dx()
    {
        return dx;
    }
    float get_dy()
    {
        return dy;
    }
    void solve_collisions(int x_size, int y_size)
    {
        for (size_t i = 0; i < n_points; i++)
        {
            if (x[i] + dx > x_size || x[i] + dx < 0)
                setmove(-dx, dy);
            if (y[i] + dy > y_size || y[i] + dy < 0)
                setmove(dx, -dy);
        }
    }
    void move_shape()
    {
        for (size_t i = 0; i < n_points; i++)
            set_point_xy(i, x[i] + dx, y[i] + dy);
    }
    void rotate_shape()
    {
        shape.rotate(r_angle);
    }
    sf::ConvexShape get_object()
    {
        return shape;
    }
};

int main()
{
    return 0;
}