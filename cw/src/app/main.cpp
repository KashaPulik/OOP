#include <BST_graphics.h>
#include <BST.h>
#include <line.h>

int main()
{
    BST_graphics tree(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(17);
    tree.insert(23);
    tree.insert(27);
    tree.insert(33);
    tree.insert(37);

    tree.set_position(375, 100);

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Text Example");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        tree.draw_tree(window);

        window.display();
        // int number;
        // std::cin >> number;
        // tree.insert(number);
    }
}