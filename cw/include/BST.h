#pragma once

#include <cstring>
#include <iostream>

#include <SFML/Graphics.hpp>

template <typename T>
class Node : public sf::CircleShape {
public:
    T data;
    Node* right;
    Node* left;
    sf::Text key_text;
    sf::Font font;

    Node(T value) : data(value), right(nullptr), left(nullptr)
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
    ~Node(){};

    void set_font(std::string font_name);

    sf::CircleShape get_CircleShape();
};

template <typename T>
class BST {
protected:
    Node<T>* root;

public:
    BST() : root(nullptr){};
    BST(T value) : root(new Node<T>(value)){};
    ~BST();

    virtual void insert(T value);

    virtual void delete_node(T value);

    T min();

    T max();

    int depth();

    int count();

private:
    int compare(const T& a, const T& b);

    int compare(const char* a, const char* b);

    int count_depth(Node<T>* root, int depth);

    void restore_prop(Node<T>* prev, Node<T>* current, int compare_result);

    void delete_tree(Node<T>* root);

    int count_nodes(Node<T>* root, int count);
};

template <typename T>
void Node<T>::set_font(std::string font_name)
{
    if (!font.loadFromFile(font_name)) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    key_text.setFont(font);
}

template <typename T>
sf::CircleShape Node<T>::get_CircleShape()
{
    return *this;
}

template <typename T>
BST<T>::~BST()
{
    delete_tree(root);
};

template <typename T>
void BST<T>::insert(T value)
{
    Node<T>* new_node = new Node<T>(value);
    if (root == nullptr) {
        root = new_node;
        return;
    }

    Node<T>* current = root;
    Node<T>* prev = nullptr;

    int compare_result;

    while (current) {
        compare_result = compare(value, current->data);
        if (compare_result == 1) {
            prev = current;
            current = current->right;
        }
        if (compare_result == -1) {
            prev = current;
            current = current->left;
        }
        if (compare_result == 0) {
            new_node->~Node();
            return;
        }
    }
    switch (compare_result) {
    case 1:
        prev->right = new_node;
        break;
    case -1:
        prev->left = new_node;
        break;
    }
}

template <typename T>
void BST<T>::delete_node(T value)
{
    if (root == nullptr) {
        std::cout << "delete_node() called on an empty tree\n";
        return;
    }
    Node<T>* current = root;
    Node<T>* prev = nullptr;

    int compare_result;
    while (current) {
        compare_result = compare(value, current->data);
        if (compare_result == 1) {
            prev = current;
            current = current->right;
        }
        if (compare_result == -1) {
            prev = current;
            current = current->left;
        }
        if (compare_result == 0) {
            if (prev == nullptr) {
                restore_prop(prev, current, compare_result);
                return;
            }
            compare_result = compare(value, prev->data);
            restore_prop(prev, current, compare_result);
            current->~Node();
            return;
        }
    }
}

template <typename T>
T BST<T>::min()
{
    if (root == nullptr) {
        std::cout << "min() called on an empty tree\n";
        return 0;
    }

    Node<T>* current = root;

    while (current->left)
        current = current->left;
    return current->data;
}

template <typename T>
T BST<T>::max()
{
    if (root == nullptr) {
        std::cout << "max() called on an empty tree\n";
        return nullptr;
    }

    Node<T>* current = root;

    while (current->right)
        current = current->right;
    return current->data;
}

template <typename T>
int BST<T>::depth()
{
    return count_depth(root, 1);
}

template <typename T>
int BST<T>::count()
{
    return count_nodes(root, 1);
}

template <typename T>
int BST<T>::compare(const T& a, const T& b)
{
    if (a < b)
        return -1;
    if (a > b)
        return 1;

    return 0;
}

template <typename T>
int BST<T>::compare(const char* a, const char* b)
{
    int compare_result = strcmp(a, b);
    if (compare_result > 0)
        return 1;
    if (compare_result < 0)
        return -1;

    return 0;
}

template <typename T>
int BST<T>::count_depth(Node<T>* root, int depth)
{
    if (root == nullptr)
        return 0;
    int left = depth, right = depth;
    if (root->left)
        left = count_depth(root->left, depth + 1);
    if (root->right)
        right = count_depth(root->right, depth + 1);
    return right > left ? right : left;
}

template <typename T>
void BST<T>::restore_prop(Node<T>* prev, Node<T>* current, int compare_result)
{
    Node<T>* right = current->right;
    Node<T>* left = current->left;
    if (right) {
        current = current->right;
        if (left) {
            while (current->left)
                current = current->left;
            current->left = left;
        }
    } else {
        right = left;
    }
    switch (compare_result) {
    case -1:
        prev->left = right;
        break;
    case 1:
        prev->right = right;
        break;
    case 0:
        root = right;
    }
}

template <typename T>
void BST<T>::delete_tree(Node<T>* root)
{
    if (root->right)
        delete_tree(root->right);
    if (root->left)
        delete_tree(root->left);
    delete root;
}

template <typename T>
int BST<T>::count_nodes(Node<T>* root, int count)
{
    if (root == nullptr)
        return 0;
    if (root->right)
        count = count_nodes(root->right, count + 1);
    if (root->left)
        count = count_nodes(root->left, count + 1);
    return count;
}
