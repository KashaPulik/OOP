#include <SFML/Graphics.hpp>
#include <cassert>

int main()
{
    sf::RenderWindow sfmlWin(sf::VideoMode(600, 360), "Hello World SFML Window");
    sf::Font font;
    if(!font.loadFromFile("ItcCheltenhamLtBookCondensed.ttf")) {
        return -1;
    }
    sf::Text message("Hello, world !", font);

    while(sfmlWin.isOpen()) {
        sf::Event e;
        while (sfmlWin.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
            }
        }
        sfmlWin.clear();
        sfmlWin.draw(message);
        sfmlWin.display();
    }
    return 0;
}