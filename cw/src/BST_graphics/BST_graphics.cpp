#include <BST_graphics.h>

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

    sf::FloatRect textBounds = root->get_global_bounds();
    sf::Vector2f textPosition(
            root->getPosition().x
                    + (root->getRadius() - textBounds.width / 2.0f)
                    - root->get_character_size() / 12,
            root->getPosition().y
                    + (root->getRadius() - textBounds.height / 2.0f)
                    - root->get_character_size() / 3);
    root->set_text_position(textPosition);

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

void BST_graphics::calculate_positions(Node_graphics* node, int current_depth)
{
    if (current_depth == 0)
        return;
    sf::Vector2f node_position = node->get_position();
    float radius = node->getRadius();
    if (node->get_right()) {
        node->get_right()->setPosition(node_position);
        node->get_right()->move(std::pow(2, current_depth) * radius, 4 * radius);

        sf::FloatRect textBounds = node->get_right()->get_global_bounds();
        sf::Vector2f textPosition(
                node->get_right()->get_position().x
                        + (radius - textBounds.width / 2.0f)
                        - root->get_character_size() / 12,
                node->get_right()->get_position().y
                        + (radius - textBounds.height / 2.0f)
                        - root->get_character_size() / 3);
        node->get_right()->set_text_position(textPosition);

        lines.push_back(
                line(node_position.x + radius,
                     node_position.y + radius,
                     node->get_right()->getPosition().x + radius,
                     node->get_right()->getPosition().y + radius));
        calculate_positions(node->get_right(), current_depth - 1);
    }
    if (node->get_left()) {
        node->get_left()->setPosition(node_position);
        node->get_left()->move(-(std::pow(2, current_depth) * radius), 4 * radius);

        sf::FloatRect textBounds = node->get_left()->get_global_bounds();
        sf::Vector2f textPosition(
                node->get_left()->getPosition().x + (radius - textBounds.width / 2.0f)
                        - root->get_character_size() / 12,
                node->get_left()->getPosition().y
                        + (radius - textBounds.height / 2.0f)
                        - root->get_character_size() / 3);

        node->get_left()->set_text_position(textPosition);

        lines.push_back(
                line(node_position.x + radius,
                     node_position.y + radius,
                     node->get_left()->getPosition().x + radius,
                     node->get_left()->getPosition().y + radius));

        calculate_positions(node->get_left(), current_depth - 1);
    }
}
void BST_graphics::recursive_draw_tree(
        Node_graphics* node, sf::RenderWindow& window)
{
    window.draw(node->get_CircleShape());
    window.draw(node->get_text());
    if (node->get_right())
        recursive_draw_tree(node->get_right(), window);
    if (node->get_left())
        recursive_draw_tree(node->get_left(), window);
}
void BST_graphics::recursive_change_color(Node_graphics* node, sf::Color color)
{
    node->setFillColor(color);
    if (node->get_right())
        recursive_change_color(node->get_right(), color);
    if (node->get_left())
        recursive_change_color(node->get_left(), color);
}
void BST_graphics::recursive_change_font(Node_graphics* node, std::string font_name)
{
    node->set_font(font_name);
    if (node->get_right())
        recursive_change_font(node->get_right(), font_name);
    if (node->get_left())
        recursive_change_font(node->get_left(), font_name);
}
int BST_graphics::get_nodes_count()
{
    return nodes_count;
}

float BST_graphics::get_radius()
{
    return root->getRadius();
}