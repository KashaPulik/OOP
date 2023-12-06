#include <BST.h>

void Node_graphics::set_data(int new_data)
{
    data = new_data;
}

int Node_graphics::get_data()
{
    return data;
}

void Node_graphics::set_right(Node_graphics* new_right)
{
    right = new_right;
}

void Node_graphics::set_left(Node_graphics* new_left)
{
    left = new_left;
}

Node_graphics* Node_graphics::get_right()
{
    return right;
}

Node_graphics* Node_graphics::get_left()
{
    return left;
}

void Node_graphics::set_font(std::string font_name)
{
    if (!font.loadFromFile(font_name)) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    key_text.setFont(font);
}

sf::FloatRect Node_graphics::get_global_bounds()
{
    return key_text.getGlobalBounds();
}

unsigned int Node_graphics::get_character_size()
{
    return key_text.getCharacterSize();
}

void Node_graphics::set_text_position(sf::Vector2f &new_position)
{
    key_text.setPosition(new_position);
}

sf::Vector2f Node_graphics::get_position()
{
    return this->getPosition();
}

sf::Text Node_graphics::get_text()
{
    return key_text;
}

sf::CircleShape Node_graphics::get_CircleShape()
{
    return *this;
}

BST::~BST()
{
    delete_tree(root);
};

void BST::insert(int value)
{
    Node_graphics* new_Node_graphics = new Node_graphics(value);
    if (root == nullptr) {
        root = new_Node_graphics;
        return;
    }

    Node_graphics* current = root;
    Node_graphics* prev = nullptr;

    int compare_result;

    while (current) {
        compare_result = compare(value, current->get_data());
        if (compare_result == 1) {
            prev = current;
            current = current->get_right();
        }
        if (compare_result == -1) {
            prev = current;
            current = current->get_left();
        }
        if (compare_result == 0) {
            new_Node_graphics->~Node_graphics();
            return;
        }
    }
    switch (compare_result) {
    case 1:
        prev->set_right(new_Node_graphics);
        break;
    case -1:
        prev->set_left(new_Node_graphics);
        break;
    }
}

void BST::delete_node(int value)
{
    if (root == nullptr) {
        std::cout << "delete_Node_graphics() called on an empty tree\n";
        return;
    }
    Node_graphics* current = root;
    Node_graphics* prev = nullptr;

    int compare_result;
    while (current) {
        compare_result = compare(value, current->get_data());
        if (compare_result == 1) {
            prev = current;
            current = current->get_right();
        }
        if (compare_result == -1) {
            prev = current;
            current = current->get_left();
        }
        if (compare_result == 0) {
            if (prev == nullptr) {
                restore_prop(prev, current, compare_result);
                return;
            }
            compare_result = compare(value, prev->get_data());
            restore_prop(prev, current, compare_result);
            current->~Node_graphics();
            return;
        }
    }
}

int BST::min()
{
    if (root == nullptr) {
        std::cout << "min() called on an empty tree\n";
        return 0;
    }

    Node_graphics* current = root;

    while (current->get_left())
        current->set_left(current->get_left());
    return current->get_data();
}

int BST::max()
{
    if (root == nullptr) {
        std::cout << "max() called on an empty tree\n";
        return 0;
    }

    Node_graphics* current = root;

    while (current->get_right())
        current->set_right(current->get_right());
    return current->get_data();
}

int BST::depth()
{
    return count_depth(root, 1);
}

int BST::count()
{
    return count_nodes(root, 1);
}

int BST::compare(const int& a, const int& b)
{
    if (a < b)
        return -1;
    if (a > b)
        return 1;

    return 0;
}

int BST::count_depth(Node_graphics* root, int depth)
{
    if (root == nullptr)
        return 0;
    int left = depth, right = depth;
    if (root->get_left())
        left = count_depth(root->get_left(), depth + 1);
    if (root->get_right())
        right = count_depth(root->get_right(), depth + 1);
    return right > left ? right : left;
}

void BST::restore_prop(
        Node_graphics* prev, Node_graphics* current, int compare_result)
{
    Node_graphics* right = current->get_right();
    Node_graphics* left = current->get_left();
    if (right) {
        current = current->get_right();
        if (left) {
            while (current->get_left())
                current = current->get_left();
            current->set_left(left);
        }
    } else {
        right = left;
    }
    switch (compare_result) {
    case -1:
        prev->set_left(right);
        break;
    case 1:
        prev->set_right(right);
        break;
    case 0:
        root = right;
    }
}

void BST::delete_tree(Node_graphics* root)
{
    if (root == nullptr)
        return;
    if (root->get_right())
        delete_tree(root->get_right());
    if (root->get_left())
        delete_tree(root->get_left());
    delete root;
}

int BST::count_nodes(Node_graphics* root, int count)
{
    if (root == nullptr)
        return 0;
    if (root->get_right())
        count = count_nodes(root->get_right(), count + 1);
    if (root->get_left())
        count = count_nodes(root->get_left(), count + 1);
    return count;
}
