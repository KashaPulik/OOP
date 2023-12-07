#include <BST_graphics.h>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

enum { x_size = 800, y_size = 600 };

int main()
{
    BST_graphics tree;

    sf::ContextSettings settings;

    settings.antialiasingLevel = 8;

    sf::RenderWindow window(
            sf::VideoMode(x_size, y_size),
            "BST_graphics",
            sf::Style::Default,
            settings);
    window.setPosition(sf::Vector2i(0, 0));

    if (!ImGui::SFML::Init(window)) {
        std::cout << "Can't open ImGUI!\n";
        return 1;
    }

    sf::View view;
    view.reset(sf::FloatRect(0, 0, x_size, y_size));
    window.setView(view);

    sf::Vector2f prev_mouse_pos;
    bool is_dragging = false;

    int input_value = 0;
    bool add_node_button_pressed = false;
    bool delete_node_button_pressed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    if (tree.get_nodes_count() == 0) {
                        tree.insert(input_value);
                        tree.set_position(
                                x_size / 2 - tree.get_radius(),
                                tree.get_radius() * 2);
                    } else {
                        tree.insert(input_value);
                    }
                    input_value = 0;
                }
                if (event.key.code == sf::Keyboard::Delete) {
                    if (tree.get_nodes_count() != 0) {
                        tree.delete_node(input_value);
                        if (tree.get_nodes_count() != 0)
                            tree.set_position(
                                    x_size / 2 - tree.get_radius(),
                                    tree.get_radius() * 2);
                    }
                    input_value = 0;
                }
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    is_dragging = true;
                    prev_mouse_pos = window.mapPixelToCoords(
                            sf::Mouse::getPosition(window));
                }

            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    is_dragging = false;
                }

            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    view.zoom(0.9f);
                } else if (event.mouseWheelScroll.delta < 0) {
                    view.zoom(1.1f);
                }

                window.setView(view);
            }
        }

        if (is_dragging) {
            sf::Vector2f mousePos
                    = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::Vector2f delta = prev_mouse_pos - mousePos;
            view.move(delta);
            window.setView(view);
        }

        ImGui::SFML::Update(window, sf::seconds(1.f / 60.f));

        ImGui::Begin("Menu");

        ImGui::InputInt("Value", &input_value);

        if (ImGui::Button("Add Node"))
            add_node_button_pressed = true;

        if (ImGui::Button("Delete Node"))
            delete_node_button_pressed = true;

        ImGui::End();

        if (add_node_button_pressed) {
            if (tree.get_nodes_count() == 0) {
                tree.insert(input_value);
                tree.set_position(
                        x_size / 2 - tree.get_radius(), tree.get_radius() * 2);
            } else {
                tree.insert(input_value);
            }
            add_node_button_pressed = false;
            input_value = 0;
        }

        if (delete_node_button_pressed) {
            if (tree.get_nodes_count() != 0) {
                tree.delete_node(input_value);
                if (tree.get_nodes_count() != 0)
                    tree.set_position(
                            x_size / 2 - tree.get_radius(),
                            tree.get_radius() * 2);
            }

            delete_node_button_pressed = false;
            input_value = 0;
        }

        window.clear();

        if (tree.get_nodes_count() != 0)
            tree.draw_tree(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
