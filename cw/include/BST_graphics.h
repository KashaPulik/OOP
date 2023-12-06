#pragma once

#include <cmath>
#include <cstring>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <BST.h>
#include <line.h>

class BST_graphics : public BST<int>{
protected:
    std::vector<line> lines;
    int nodes_count;
    int tree_depth;

public:
    BST_graphics() : BST<int>(), nodes_count(0), tree_depth(0){};
    BST_graphics(int value) : BST<int>(value), nodes_count(1), tree_depth(1){};

    void insert(int value);
    void delete_node(int value);
    void set_position(float x, float y);
    void draw_tree(sf::RenderWindow& window);
    void change_color(sf::Color color);
    void change_font(std::string font_name);
    int get_nodes_count();
    float get_radius();

private:
    void calculate_positions(Node<int>* node, int current_depth);
    void recursive_draw_tree(Node<int>* node, sf::RenderWindow& window);
    void recursive_change_color(Node<int>* node, sf::Color color);
    void recursive_change_font(Node<int>* node, std::string font_name);
};