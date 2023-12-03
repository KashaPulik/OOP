#include <iostream>
#include <cstring>

#include <SFML/Graphics.hpp>

template <typename T>
class Node
{
public:
    T data;
    Node *right;
    Node *left;

    Node(T value) : data(value), right(nullptr), left(nullptr){};
    ~Node() {}
};

template <typename T>
class BST
{
protected:
    Node<T> *root;

public:
    BST() : root(nullptr){};
    BST(T value) : root(new Node<T>(value)){};
    BST(const BST &other) : root(nullptr)
    {
        copy_from(other);
    }

    void insert(T value)
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

    void delete_node(T value)
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
        if(root == nullptr)
            return 0;
        int left = depth, right = depth;
        if(root->left)
            left = count_depth(root->left, depth + 1);
        if(root->right)
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
        }
    }
};

int main()
{
    BST<int> tree;
    tree.insert(100);
    tree.insert(50);
    tree.insert(150);
    tree.insert(25);
    tree.insert(75);
    tree.insert(125);
    tree.insert(175);
    tree.insert(8);
    tree.insert(9);
    std::cout << tree.depth() << std::endl;
}