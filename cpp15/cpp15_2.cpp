#include <iostream>

using namespace std;

template<typename T>
class Node {
public:
    T value;
    Node* next;
    Node* prev;

    Node(T value, Node* next = nullptr, Node* prev = nullptr)
        : value{ value }, next{ next }, prev{ prev } {}
};

template<typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoublyLinkedList() : head{ nullptr }, tail{ nullptr }, size{ 0 } {}

    ~DoublyLinkedList() {
        DeleteAll();
    }

    void AddToHead(T value) {
        Node<T>* newNode = new Node<T>(value, head);
        if (head) {
            head->prev = newNode;
        } head = newNode;
        if (!tail) {
            tail = head;
        } size++;
    }

    void AddToTail(T value) {
        Node<T>* newNode = new Node<T>(value, nullptr, tail);
        if (tail) {
            tail->next = newNode;
        } tail = newNode;
        if (!head) {
            head = tail;
        } size++;
    }

    void DeleteFromHead() {
        if (!head) return;

        Node<T>* tmp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        } delete tmp; size--;
    }

    void DeleteFromTail() {
        if (!tail) return;

        Node<T>* tmp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        } delete tmp; size--;
    }

    void DeleteAll() {
        while (head) {
            DeleteFromHead();
        }
    }

    void InsertAt(int position, T value) {
        if (position < 0 || position > size) return;

        if (position == 0) {
            AddToHead(value);
            return;
        }

        if (position == size) {
            AddToTail(value);
            return;
        }

        Node<T>* current = head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }

        Node<T>* newNode = new Node<T>(value, current->next, current);
        current->next->prev = newNode;
        current->next = newNode;
        size++;
    }

    void DeleteAt(int position) {
        if (position < 0 || position >= size) return;

        if (position == 0) {
            DeleteFromHead();
            return;
        }

        if (position == size - 1) {
            DeleteFromTail();
            return;
        }

        Node<T>* current = head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current; size--;
    }

    int Find(T value) {
        Node<T>* current = head;
        int position = 0;
        while (current) {
            if (current->value == value) {
                return position;
            } current = current->next; position++;
        } return -1;
    }

    int Replace(T oldValue, T newValue) {
        Node<T>* current = head;
        int replaceCount = 0;
        while (current) {
            if (current->value == oldValue) {
                current->value = newValue;
                replaceCount++;
            } current = current->next;
        } return replaceCount > 0 ? replaceCount : -1;
    }

    void Reverse() {
        Node<T>* current = head;
        Node<T>* tmp = nullptr;

        while (current) {
            tmp = current->prev;
            current->prev = current->next;
            current->next = tmp;
            current = current->prev;
        }

        if (tmp) {
            tmp = tmp->prev;
            head = tmp;
            tail = tmp;
            while (tmp->next) {
                tmp = tmp->next;
            } tail = tmp;
        }
    }

    void Show() const {
        if (!head) {
            cout << "(empty list)" << endl;
        }
        else {
            Node<T>* current = head;
            while (current) {
                cout << current->value << " ";
                current = current->next;
            } cout << endl;
        }
    }


    int GetSize() const {
        return size;
    }
};

int main() {
    DoublyLinkedList<int> list;

    list.AddToHead(10);
    list.AddToHead(20);
    list.AddToTail(30);
    list.InsertAt(1, 25);
    list.Show();

    list.DeleteAt(2);
    list.Show();

    int position = list.Find(25);
    cout << "Position of 25: " << position << endl;

    int replaceCount = list.Replace(25, 50);
    cout << "Replaced 25 with 50: " << replaceCount << " times" << endl;

    list.Reverse();
    list.Show();

    list.DeleteAll();
    list.Show();
}
