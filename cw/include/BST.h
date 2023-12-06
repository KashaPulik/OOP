#pragma once

#include <cstring>
#include <iostream>

#include <SFML/Graphics.hpp>

class Node {
public:
    virtual void set_data(int data) = 0;
    virtual int get_data() = 0;
};

class Node_graphics : public Node, public sf::CircleShape {
protected:
    int data;
    Node_graphics* right;
    Node_graphics* left;
    sf::Text key_text;
    sf::Font font;

public:
    Node_graphics(){};
    Node_graphics(int value) : data(value), right(nullptr), left(nullptr)
    {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }
        key_text.setFont(font);
        key_text.setFillColor(sf::Color::White);
        key_text.setCharacterSize(24);
        key_text.setString(std::to_string(value));
        key_text.setPosition(0, 0);
        this->setRadius(25.0f);
        this->setFillColor(sf::Color::Red);
    };
    ~Node_graphics(){};

    void set_font(std::string font_name);
    void set_data(int new_data) override;
    int get_data() override;
    void set_right(Node_graphics* new_right);
    Node_graphics* get_right();
    void set_left(Node_graphics* new_left);
    Node_graphics* get_left();
    sf::FloatRect get_global_bounds();
    unsigned int get_character_size();
    void set_text_position(sf::Vector2f &new_position);
    sf::Vector2f get_position();
    sf::Text get_text();

    sf::CircleShape get_CircleShape();
};

class BST : public Node_graphics {
protected:
    Node_graphics* root;

public:
    BST() : root(nullptr){};
    BST(int value) : root(new Node_graphics(value)){};
    ~BST();

    virtual void insert(int value);

    virtual void delete_node(int value);

    int min();

    int max();

    int depth();

    int count();

private:
    int compare(const int& a, const int& b);

    int count_depth(Node_graphics* root, int depth);

    void restore_prop(Node_graphics* prev, Node_graphics* current, int compare_result);

    void delete_tree(Node_graphics* root);

    int count_nodes(Node_graphics* root, int count);
};
