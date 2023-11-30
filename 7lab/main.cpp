#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;

    Node(T val) : data(val), prev(nullptr), next(nullptr) {}

    ~Node() {
        // Добавим деструктор для освобождения памяти
        std::cout << "Node Destructor called for data: " << data << std::endl;
    }
};

template <typename T>
class DoublyLinkedList {
protected:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr) {
        copyFrom(other);
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    void push_back(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void push_front(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void print() const {
        Node<T>* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~DoublyLinkedList() {
        clear();
    }

    // Статический элемент класса
    static int instanceCount;

protected:
    void copyFrom(const DoublyLinkedList& other) {
        Node<T>* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }

    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
};

// Инициализация статического элемента класса
template <typename T>
int DoublyLinkedList<T>::instanceCount = 0;

template <typename T>
class Stack : public DoublyLinkedList<T> {
public:
    Stack() : DoublyLinkedList<T>() {
        // Увеличиваем счетчик при создании объекта Stack
        DoublyLinkedList<T>::instanceCount++;
    }

    Stack(const Stack& other) : DoublyLinkedList<T>(other) {}

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            DoublyLinkedList<T>::operator=(other);
        }
        return *this;
    }

    void push(T val) {
        this->push_back(val);
    }

    void pop() {
        if (this->tail) {
            Node<T>* temp = this->tail;
            this->tail = this->tail->prev;
            if (this->tail) {
                this->tail->next = nullptr;
            } else {
                this->head = nullptr;
            }
            delete temp;
        } else {
            throw std::out_of_range("pop() called on an empty stack");
        }
    }

    T top() const {
        if (this->tail) {
            return this->tail->data;
        } else {
            throw std::out_of_range("top() called on an empty stack");
        }
    }

    ~Stack() {
        // Деструктор по умолчанию будет вызван для базового класса
        // Уменьшаем счетчик при уничтожении объекта Stack
        DoublyLinkedList<T>::instanceCount--;
    }
};

template <typename T>
class Queue : public DoublyLinkedList<T> {
public:
    Queue() : DoublyLinkedList<T>() {}

    Queue(const Queue& other) : DoublyLinkedList<T>(other) {}

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            DoublyLinkedList<T>::operator=(other);
        }
        return *this;
    }

    void enqueue(T val) {
        this->push_back(val);
    }

    void dequeue() {
        if (this->head) {
            Node<T>* temp = this->head;
            this->head = this->head->next;
            if (this->head) {
                this->head->prev = nullptr;
            } else {
                this->tail = nullptr;
            }
            delete temp;
        } else {
            throw std::out_of_range("dequeue() called on an empty queue");
        }
    }

    T front() const {
        if (this->head) {
            return this->head->data;
        } else {
            throw std::out_of_range("front() called on an empty queue");
        }
    }

    ~Queue() {
        // Деструктор по умолчанию будет вызван для базового класса
    }
};

int main() {
    try {
        Stack<int> stack1;
        Stack<int> stack2;

        std::cout << "Stack Instance Count: " << DoublyLinkedList<int>::instanceCount << std::endl;

        stack1.push(1);
        stack1.push(2);
        stack1.push(3);

        stack2 = stack1;

        std::cout << "Stack Instance Count: " << DoublyLinkedList<int>::instanceCount << std::endl;

        stack1.pop();

        std::cout << "Stack Instance Count: " << DoublyLinkedList<int>::instanceCount << std::endl;

        Queue<int> queue;
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);

        std::cout << "Queue Instance Count: " << DoublyLinkedList<int>::instanceCount << std::endl;

        queue.dequeue();

        std::cout << "Queue Instance Count: " << DoublyLinkedList<int>::instanceCount << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
