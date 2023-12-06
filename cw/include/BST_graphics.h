#pragma once

#include <cmath>
#include <cstring>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <BST.h>
#include <line.h>

class BST_graphics : public BST{
protected:
    std::vector<line> lines;
    int nodes_count;
    int tree_depth;

public:
    BST_graphics() : BST(), nodes_count(0), tree_depth(0){};
    BST_graphics(int value) : BST(value), nodes_count(1), tree_depth(1){};

    void insert(int value);
    void delete_node(int value);
    void set_position(float x, float y);
    void draw_tree(sf::RenderWindow& window);
    void change_color(sf::Color color);
    void change_font(std::string font_name);
    int get_nodes_count();
    float get_radius();

private:
    void calculate_positions(Node_graphics* node, int current_depth);
    void recursive_draw_tree(Node_graphics* node, sf::RenderWindow& window);
    void recursive_change_color(Node_graphics* node, sf::Color color);
    void recursive_change_font(Node_graphics* node, std::string font_name);
};