#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <random>

using namespace std;
template<typename T>
class LinckedList {
    struct Node {

        T value;
        Node* next, * prev;
        Node() :next(nullptr), prev(nullptr), value(T = {}) {};
        Node(const T& value) :next(nullptr), prev(nullptr), value(value) {};
    };
    Node* _head;
    Node* _tail;
public:
    LinckedList() :_head(nullptr), _tail(nullptr) {}
    LinckedList(const LinckedList& other) {
        Node* tmp = other._head;
        push_tail(tmp->value);
        tmp = tmp->next;
        while (tmp != other._head) {
            push_tail(tmp->value);
            tmp = tmp->next;
        }
    }
    ~LinckedList() {
        while (_head != _tail) {
            Node* tmp = _head;
            _head = _head->next;
            delete tmp;
        }
    }

    void push_tail(const T& value) {
        Node* tmp = new Node(value);
        if (!_head) {
            _tail = _head = tmp;
            _head->next = _head->prev = tmp;
        }
        else {
            _tail->next = tmp;
            _head->prev = tmp;
            tmp->next = _head;
            tmp->prev = _tail;
            _tail = tmp;
            _head = _tail->next;
        }
    }

    void push_tail(const LinckedList& other) {
        if (!other._head) {
            throw length_error("List is empty");
        }
        Node* current = other._head;
        while (current != other._tail) {
            push_tail(current->value);
            current = current->next;
        }
        push_tail(other._tail->value);
    }

    void push_head(const T& value) {
        Node* tmp = new Node(value);
        if (!_head) {
            _tail = _head = tmp;
        }
        else {
            _tail->next = tmp;
            _head->prev = tmp;
            tmp->next = _head;
            tmp->prev = _tail;
            _head = tmp;
            _tail = _head->prev;
        }
    }

    void push_head(const LinckedList& other) {
        if (!other._head) {
            throw length_error("List is empty");
        }
        Node* current = other._tail;
        while (current != other._head) {
            push_head(current->value);
            current = current->prev;
        }
        push_head(other._head->value);
    }
  
    void pop_head() {
        if (_head) {
            Node* tmp = _head;

            if (_head == _tail) {
                _head = nullptr;
                _tail = nullptr;
            }
            else {
                _head = _head->next;
                _head->prev = _tail;
                _tail->next = _head;
            }

            delete tmp;
        }

    }
    void pop_tail() {
        if (_tail) {
            Node* tmp = _tail;

            if (_head == _tail) {
                _head = nullptr;
                _tail = nullptr;
            }
            else {
                _tail = _tail->prev;
                _tail->next = _head;
                _head->prev = _tail;
            }

            delete tmp;
        }

    }
    friend ostream& operator<<(ostream& os, const LinckedList<T>& other) {
        Node* tmp = other._head;
        if (!other._head) {
            cout << "Empty list!";
        }
        else {
             while (tmp != other._tail)
             {
                 os << (tmp->value)<< " ";
                 tmp = tmp->next;
             }
             os << (other._tail->value);
       
        }
        return os;

    }

    LinckedList& operator =(const LinckedList<T>& other) {
        if (this != &other) {
            LinckedList tmp(other);
            swap(tmp._head, _head);
            swap(tmp._tail, _tail);
        }
        return *this;
    }

    void delete_node(const T& value) {
        Node* tmp = _head->next;
        if (_head->value == value)
            this->pop_head();
        while (tmp != _head) {
            if (tmp->value == value) {
                if (tmp == _tail)
                    this->pop_tail();
                else{
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                    tmp = tmp->next;
                }
            }
            else
                tmp = tmp->next;
        }
        
    }

    T operator[](int index) const {
        Node* tmp = _head;
        size_t n = 0;
        while (n != index) {
            tmp = tmp->next;
            n++;
        }
        return tmp->value;
    }

    T& operator[](int index) {
        Node* tmp = _head;
        size_t n = 0;
        while (n != index) {
            tmp = tmp->next;
            n++;
        }
        return tmp->value;
    }
};
int main() {

    LinckedList<int> list1;
    list1.push_tail(1);
    list1.push_tail(2);
    list1.push_tail(3);
    LinckedList<int> list2;
    list2.push_head(4);
    list2.push_head(5);
    list2.push_head(6);
    cout << list1 << endl;
    cout << list2 << endl;
    list1.push_tail(list2);
    list1.push_head(list2);
    cout << list1 << endl;
    cout << list1 << endl;
    list1.pop_head();
    list2.pop_tail();
    cout << list1 << endl;
    cout << list2 << endl;
    LinckedList<int> list3(list2);
    cout << list3 << endl;
    list1.delete_node(6);
    cout << list1 << endl;








}