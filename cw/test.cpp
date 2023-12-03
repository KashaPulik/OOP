#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Real-Time Viewport Navigation");

    sf::View view;
    view.setSize(800.0f, 600.0f);
    view.setCenter(400.0f, 300.0f);
    window.setView(view);

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(100.0f, 100.0f));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(200.0f, 200.0f);

    sf::Vector2i lastMousePos;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Обработка событий мыши
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // Получаем текущие координаты мыши
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // Вычисляем разницу между текущим и предыдущим положением мыши
            sf::Vector2i delta = mousePos - lastMousePos;

            // Перемещаем камеру на эту разницу
            view.move(-window.mapPixelToCoords(delta));
            window.setView(view);

            // Обновляем последнее положение мыши
            lastMousePos = mousePos;
        }

        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
