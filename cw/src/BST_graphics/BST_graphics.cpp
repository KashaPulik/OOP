#include <cmath>
#include <cstring>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <BST.h>
#include <BST_graphics.h>
#include <line.h>

void BST_graphics::insert(int value)
{
    BST::insert(value);
    tree_depth = this->depth();
    nodes_count = this->count();
    lines.clear();
    calculate_positions(root, tree_depth - 1);
}
void BST_graphics::delete_node(int value)
{
    BST::delete_node(value);
    tree_depth = BST::depth();
    nodes_count = BST::count();
    lines.clear();
    if (root != nullptr)
        calculate_positions(root, tree_depth - 1);
}
void BST_graphics::set_position(float x, float y)
{
    root->setPosition(sf::Vector2f(x, y));

    sf::FloatRect textBounds = root->key_text.getGlobalBounds();
    sf::Vector2f textPosition(
            root->getPosition().x
                    + (root->getRadius() - textBounds.width / 2.0f)
                    - root->key_text.getCharacterSize() / 12,
            root->getPosition().y
                    + (root->getRadius() - textBounds.height / 2.0f)
                    - root->key_text.getCharacterSize() / 3);
    root->key_text.setPosition(textPosition);

    lines.clear();
    calculate_positions(root, tree_depth - 1);
}
void BST_graphics::draw_tree(sf::RenderWindow& window)
{
    for (auto& line : lines)
        window.draw(line.get_VertexArray());

    recursive_draw_tree(root, window);
}
void BST_graphics::change_color(sf::Color color)
{
    for (auto& line : lines)
        line.set_color(color);
    recursive_change_color(root, color);
}
void BST_graphics::change_font(std::string font_name)
{
    recursive_change_font(root, font_name);
}

void BST_graphics::calculate_positions(Node<int>* node, int current_depth)
{
    if (current_depth == 0)
        return;
    sf::Vector2f node_position = node->getPosition();
    float radius = node->getRadius();
    if (node->right) {
        node->right->setPosition(node_position);
        node->right->move(std::pow(2, current_depth) * radius, 4 * radius);

        sf::FloatRect textBounds = node->right->key_text.getGlobalBounds();
        sf::Vector2f textPosition(
                node->right->getPosition().x
                        + (radius - textBounds.width / 2.0f)
                        - root->key_text.getCharacterSize() / 12,
                node->right->getPosition().y
                        + (radius - textBounds.height / 2.0f)
                        - root->key_text.getCharacterSize() / 3);
        node->right->key_text.setPosition(textPosition);

        lines.push_back(
                line(node_position.x + radius,
                     node_position.y + radius,
                     node->right->getPosition().x + radius,
                     node->right->getPosition().y + radius));
        calculate_positions(node->right, current_depth - 1);
    }
    if (node->left) {
        node->left->setPosition(node_position);
        node->left->move(-(std::pow(2, current_depth) * radius), 4 * radius);

        sf::FloatRect textBounds = node->left->key_text.getGlobalBounds();
        sf::Vector2f textPosition(
                node->left->getPosition().x + (radius - textBounds.width / 2.0f)
                        - root->key_text.getCharacterSize() / 12,
                node->left->getPosition().y
                        + (radius - textBounds.height / 2.0f)
                        - root->key_text.getCharacterSize() / 3);

        node->left->key_text.setPosition(textPosition);

        lines.push_back(
                line(node_position.x + radius,
                     node_position.y + radius,
                     node->left->getPosition().x + radius,
                     node->left->getPosition().y + radius));

        calculate_positions(node->left, current_depth - 1);
    }
}
void BST_graphics::recursive_draw_tree(
        Node<int>* node, sf::RenderWindow& window)
{
    window.draw(node->get_CircleShape());
    window.draw(node->key_text);
    if (node->right)
        recursive_draw_tree(node->right, window);
    if (node->left)
        recursive_draw_tree(node->left, window);
}
void BST_graphics::recursive_change_color(Node<int>* node, sf::Color color)
{
    node->setFillColor(color);
    if (node->right)
        recursive_change_color(node->right, color);
    if (node->left)
        recursive_change_color(node->left, color);
}
void BST_graphics::recursive_change_font(Node<int>* node, std::string font_name)
{
    node->set_font(font_name);
    if (node->right)
        recursive_change_font(node->right, font_name);
    if (node->left)
        recursive_change_font(node->left, font_name);
}
int BST_graphics::get_nodes_count()
{
    return nodes_count;
}

float BST_graphics::get_radius()
{
    return root->getRadius();
}