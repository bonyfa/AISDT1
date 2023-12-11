#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <random>

using namespace std;
template<typename T>
struct Node {

    T value;
    Node* next, * prev;
    Node() :next(nullptr), prev(nullptr), value(T = {}) {};
    Node(const T& value) :next(nullptr), prev(nullptr), value(value) {};
};
template<typename T>
class LinckedList {
    Node<T>* _tail;
    Node<T>* _head;
public:
    LinckedList() :_head(nullptr), _tail(nullptr) {}
    LinckedList(const LinckedList& other) {
        Node<T>* tmp = other._head;
        push_tail(tmp->value);
        tmp = tmp->next;
        while (tmp != other._head) {
            push_tail(tmp->value);
            tmp = tmp->next;
        }
    }
    ~LinckedList() {
        while (_head != _tail) {
            Node<T>* tmp = _head;
            _head = _head->next;
            delete tmp;
        }
    }
    

    void push_tail(const T& value) {
        Node<T>* tmp = new Node<T>(value);
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
        Node<T>* current = other._head;
        while (current != other._tail) {
            push_tail(current->value);
            current = current->next;
        }
        push_tail(other._tail->value);
    }

    void push_head(const T& value) {
        Node<T>* tmp = new Node<T>(value);
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
        Node<T>* current = other._tail;
        while (current != other._head) {
            push_head(current->value);
            current = current->prev;
        }
        push_head(other._head->value);
    }
  
    void pop_head() {
        if (_head) {
            Node<T>* tmp = _head;

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
            Node<T>* tmp = _tail;

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
        Node<T>* tmp = other._head;
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
        Node<T>* tmp = _head->next;
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

    T operator[](size_t index) const {
        Node* tmp = _head;
        size_t n = 0;
        while (n != index) {
            tmp = tmp->next;
            n++;
        }
        return tmp->value;
    }

    T& operator[](size_t index) {
        Node* tmp = _head;
        size_t n = 0;
        while (n != index) {
            tmp = tmp->next;
            n++;
        }
        return tmp->value;
    }


    void add(const T& value, int index) {
        Node<T>* tmp = _head;
        size_t n = 1;
        while (n != (index)) {
            tmp = tmp->next;
            n++;
        }
        tmp->value = value;
    }
    
    T generateRandom(random_device& randomDevice) {
        mt19937_64 generator(randomDevice());
        if constexpr (numeric_limits<T>::is_integer)
        {
            uniform_int_distribution<T> dice(-10, 10);
            return dice(generator);
        }
        else
        {
            uniform_real_distribution<T> dice(-10.0, 10.0);
            return dice(generator);
        }
    }
    LinckedList(int size, const T& min, const T& max) : _head(nullptr), _tail(nullptr) {
        random_device randomDevice;

        for (int i = 0; i < size; ++i) {
            T value = generateRandom(randomDevice);
            push_tail(value, i);
        }
    }
    Node<T>* getHead() const {
        return _head;
    }
    void setHead(Node<T>* other) {
        this->_head = other;
    }
};
template <typename T>
void reverseList(LinckedList<T>& dll) {
    Node<T>* head = dll.getHead();
    if (!head) {
        return;
    }
    LinckedList<T> tmp_list ;
    tmp_list.push_head(head->value);
    head = head->next;
    while (head != dll.getHead()) {
        tmp_list.push_head(head->value);
        head = head->next;
    }
    dll = tmp_list;

}
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
    list1.add(6, 3);
    cout << list1 << endl;
    LinckedList<int> list5;
    list5.push_tail(1);
    list5.push_tail(2);
    list5.push_tail(3);
    list5.push_tail(5);
    list5.push_tail(6);
    list5.push_tail(7);
    cout << list5 << endl;
    reverseList<int>(list5);
    cout << list5 << endl;



}