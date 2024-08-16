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

    void Show() const {
        Node<T>* current = head;
        while (current) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
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
    list.Show();

    list.DeleteFromHead();
    list.Show();

    list.DeleteFromTail();
    list.Show();

    list.DeleteAll();
    list.Show();
}
