#include <iostream>
#include <cstring>
#include <cmath>

#include <SFML/Graphics.hpp>

class line : public sf::VertexArray
{
public:
    line()
    {
        this->setPrimitiveType(sf::Lines);
        this->resize(2);
        set_color(sf::Color::Red);
    }
    line(float x1, float y1, float x2, float y2)
    {
        this->setPrimitiveType(sf::Lines);
        this->resize(2);
        set_color(sf::Color::Red);
        set_position(x1, y1, x2, y2);
    }
    void set_position(float x1, float y1, float x2, float y2)
    {
        (*this)[0].position = sf::Vector2f(x1, y1);
        (*this)[1].position = sf::Vector2f(x2, y2);
    }
    void set_color(const sf::Color &color)
    {
        (*this)[0].color = color;
        (*this)[1].color = color;
    }
    sf::VertexArray get_VertexArray()
    {
        return *this;
    }
};

template <typename T>
class Node : public sf::CircleShape
{
public:
    T data;
    Node *right;
    Node *left;
    sf::Text key_text;
    sf::Font font;

    Node(T value) : data(value), right(nullptr), left(nullptr)
    {
        if (!font.loadFromFile("arial.ttf"))
        {
            std::cerr << "Failed to load font!" << std::endl;
        }
        key_text.setFont(font);
        key_text.setFillColor(sf::Color::White);
        key_text.setCharacterSize(25);
        key_text.setString(std::to_string(value));
        key_text.setPosition(0, 0);
        this->setRadius(25.0f);
        this->setFillColor(sf::Color::Red);
    };
    ~Node() {}

    sf::CircleShape get_CircleShape()
    {
        return *this;
    }
};

template <typename T>
class BST
{
protected:
    Node<T> *root;

public:
    BST() : root(nullptr){};
    BST(T value) : root(new Node<T>(value)){};
    ~BST()
    {
        delete_tree(root);
    }

    virtual void insert(T value)
    {
        Node<T> *new_node = new Node<T>(value);
        if (root == nullptr)
        {
            root = new_node;
            return;
        }

        Node<T> *current = root;
        Node<T> *prev = nullptr;

        int compare_result;

        while (current)
        {
            compare_result = compare(value, current->data);
            if (compare_result == 1)
            {
                prev = current;
                current = current->right;
            }
            if (compare_result == -1)
            {
                prev = current;
                current = current->left;
            }
            if (compare_result == 0)
            {
                new_node->~Node();
                return;
            }
        }
        switch (compare_result)
        {
        case 1:
            prev->right = new_node;
            break;
        case -1:
            prev->left = new_node;
            break;
        }
    }

    virtual void delete_node(T value)
    {
        if (root == nullptr)
        {
            std::cout << "delete_node() called on an empty tree\n";
            return;
        }
        Node<T> *current = root;
        Node<T> *prev = nullptr;

        int compare_result;
        while (current)
        {
            compare_result = compare(value, current->data);
            if (compare_result == 1)
            {
                prev = current;
                current = current->right;
            }
            if (compare_result == -1)
            {
                prev = current;
                current = current->left;
            }
            if (compare_result == 0)
            {
                if (prev == nullptr)
                {
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

    T min()
    {
        if (root == nullptr)
        {
            std::cout << "min() called on an empty tree\n";
            return 0;
        }

        Node<T> *current = root;

        while (current->left)
            current = current->left;
        return current->data;
    }

    T max()
    {
        if (root == nullptr)
        {
            std::cout << "max() called on an empty tree\n";
            return nullptr;
        }

        Node<T> *current = root;

        while (current->right)
            current = current->right;
        return current->data;
    }

    int depth()
    {
        return count_depth(root, 1);
    }

    int count()
    {
        return count_nodes(root, 1);
    }

private:
    int compare(const T &a, const T &b)
    {
        if (a < b)
            return -1;
        if (a > b)
            return 1;

        return 0;
    }

    int compare(const char *a, const char *b)
    {
        int compare_result = strcmp(a, b);
        if (compare_result > 0)
            return 1;
        if (compare_result < 0)
            return -1;

        return 0;
    }

    int count_depth(Node<T> *root, int depth)
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

    void restore_prop(Node<T> *prev, Node<T> *current, int compare_result)
    {
        Node<T> *right = current->right;
        Node<T> *left = current->left;
        if (right)
        {
            current = current->right;
            if (left)
            {
                while (current->left)
                    current = current->left;
                current->left = left;
            }
        }
        else
        {
            right = left;
        }
        switch (compare_result)
        {
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

    void delete_tree(Node<T> *root)
    {
        if (root->right)
            delete_tree(root->right);
        if (root->left)
            delete_tree(root->left);
        delete root;
    }

    int count_nodes(Node<T> *root, int count)
    {
        if (root == nullptr)
            return 0;
        if (root->right)
            count = count_nodes(root->right, count + 1);
        if (root->left)
            count = count_nodes(root->left, count + 1);
        return count;
    }
};

class BST_graphics : public BST<int>
{
protected:
    std::vector<line> lines;
    int nodes_count;
    int tree_depth;

public:
    BST_graphics() : BST<int>(), nodes_count(0), tree_depth(0){};
    BST_graphics(int value) : BST<int>(value), nodes_count(1), tree_depth(1){};

    void insert(int value)
    {
        BST::insert(value);
        tree_depth = this->depth();
        nodes_count = this->count();
        lines.clear();
        calculate_positions(root, tree_depth - 1);
    }
    void delete_node(int value)
    {
        BST::delete_node(value);
        tree_depth = this->depth();
        nodes_count = this->count();
        lines.clear();
        calculate_positions(root, tree_depth - 1);
    }
    void set_position(float x, float y)
    {
        root->setPosition(sf::Vector2f(x, y));

        sf::FloatRect textBounds = root->key_text.getGlobalBounds();
        sf::Vector2f textPosition(
            root->getPosition().x + (root->getRadius() - textBounds.width / 2.0f) - 2,
            root->getPosition().y + (root->getRadius() - textBounds.height / 2.0f) - 8);
        root->key_text.setPosition(textPosition);

        lines.clear();
        calculate_positions(root, tree_depth - 1);
    }
    void draw_tree(sf::RenderWindow &window)
    {
        for (auto &line : lines)
        {
            window.draw(line.get_VertexArray());
        }
        recursive_draw_tree(root, window);
    }

private:
    void calculate_positions(Node<int> *node, int current_depth)
    {
        if (current_depth == 0)
            return;
        sf::Vector2f node_position = node->getPosition();
        float radius = node->getRadius();
        if (node->right)
        {
            node->right->setPosition(node_position);
            node->right->move(std::pow(2, current_depth) * radius, 4 * radius);

            sf::FloatRect textBounds = node->right->key_text.getGlobalBounds();
            sf::Vector2f textPosition(
                node->right->getPosition().x + (radius - textBounds.width / 2.0f) - 2,
                node->right->getPosition().y + (radius - textBounds.height / 2.0f) - 8);
            node->right->key_text.setPosition(textPosition);

            lines.push_back(line(node_position.x + radius,
                                 node_position.y + radius,
                                 node->right->getPosition().x + radius,
                                 node->right->getPosition().y + radius));
            calculate_positions(node->right, current_depth - 1);
        }
        if (node->left)
        {
            node->left->setPosition(node_position);
            node->left->move(-(std::pow(2, current_depth) * radius), 4 * radius);

            sf::FloatRect textBounds = node->left->key_text.getGlobalBounds();
            sf::Vector2f textPosition(
                node->left->getPosition().x + (radius - textBounds.width / 2.0f) - 2,
                node->left->getPosition().y + (radius - textBounds.height / 2.0f) - 8);

            node->left->key_text.setPosition(textPosition);

            lines.push_back(line(node_position.x + radius,
                                 node_position.y + radius,
                                 node->left->getPosition().x + radius,
                                 node->left->getPosition().y + radius));

            calculate_positions(node->left, current_depth - 1);
        }
    }
    void recursive_draw_tree(Node<int> *node, sf::RenderWindow &window)
    {
        window.draw(node->get_CircleShape());
        window.draw(node->key_text);
        if (node->right)
            recursive_draw_tree(node->right, window);
        if (node->left)
            recursive_draw_tree(node->left, window);
    }
};

int main()
{
    BST_graphics tree(20);
    // tree.insert(10);
    // tree.insert(30);
    // tree.insert(5);
    // tree.insert(15);
    // tree.insert(25);
    // tree.insert(35);
    // tree.insert(3);
    // tree.insert(7);
    // tree.insert(13);
    // tree.insert(17);
    // tree.insert(23);
    // tree.insert(27);
    // tree.insert(33);
    // tree.insert(37);

    tree.set_position(375, 100);

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Text Example");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        tree.draw_tree(window);

        window.display();
        int number;
        std::cin >> number;
        tree.insert(number);
    }
}