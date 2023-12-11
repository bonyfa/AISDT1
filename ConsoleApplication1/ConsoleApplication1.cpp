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
        }
    }
    void push_tail(const LinckedList& other) {
        if (!other._head) {
            
        }
        else
        {
            this->_tail->next = other->_head;
            other->_head->prev = this->_tail;
            this->_head->prev = other->_tail;
            other->_tail->next = this->_head;
            this->_tail = other->_tail;
        }
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
        }
    }
    void push_head(const LinckedList& other) {

        if (!other._head) {
            
        }
        else
        this->_tail->next = other->_head;
        other->_head->prev = this->_tail;
        this->_head->prev = other->_tail;
        other->_tail->next = this->_head;
        this->_tail = other->_tail;
    }
    friend ostream& operator<<(ostream& os, LinckedList<T>& other) {
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
    LinckedList & operator =(const LinckedList)
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
    
}