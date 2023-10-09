#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;

enum {x_size = 800, y_size = 600};

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(x_size, y_size), "ABOBA");

    window.setFramerateLimit(30);

    int n_points = 1000;

    int dx[n_points];
    int dy[n_points];

    for(int i = 0; i < n_points; i++) {
        dx[i] = rand() % 2 == 0 ? rand()%10 + 1 : -(rand()%10 + 1);
        dy[i] = rand() % 2 == 0 ? rand()%10 + 1 : -(rand()%10 + 1);
    }

    VertexArray points(Points, n_points);
    Vector2f position;

    for(int i = 0; i < n_points; i++) {
        points[i].position = Vector2f(rand()%x_size, rand()%y_size);
        points[i].color = Color(rand()%256, rand()%256, rand()%256);
    }

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        for(int i = 0; i < n_points; i++)
        {
            

            position = points[i].position;
            if(position.x + dx[i] > x_size || position.x + dx[i] < 0)
                dx[i] = -dx[i];
            if(position.y + dy[i] > y_size || position.y + dy[i] < 0)
                dy[i] = -dy[i];
            position.x += dx[i];
            position.y += dy[i];
            points[i].position = position;
        }
        window.clear();
        window.draw(points);
        window.display();
    }


}