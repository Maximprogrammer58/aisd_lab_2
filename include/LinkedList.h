#ifndef LAB_2_INCLUDE_LINKEDLIST_H
#define LAB_2_INCLUDE_LINKEDLIST_H

#include "Node.h"
#include "Random.h"

template<typename T>
class LinkedList {
    Node<T> *head_, *tail_;
  
public:
    LinkedList();

    LinkedList(const LinkedList& other);

    LinkedList& operator=(const LinkedList& other);

    void push_head(T data);

    void push_head(const LinkedList& other);

    void push_tail(T data);

    void push_tail(const LinkedList& other);

    void pop_head();

    void pop_tail();

    Node<T>* at(int index);

    T& operator[](int index);

    const T& operator[](int index) const;

    void insert(int index, T data);

    Node<T>* earse(int index);

    void delete_Node(T data);
    
    void print() const;

    void print_path() const;

    void clear();

    ~LinkedList();
};

template<typename T>
LinkedList<T>::LinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
    head_ = nullptr;
    tail_ = nullptr;
    Node<T>* tmp = other.head_;
    while (tmp) {
        push_tail(tmp->data);
        tmp = tmp->next;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {
        clear();
        Node<T>* tmp = other.head_;
        while (tmp) {
            push_tail(tmp->data);
            tmp = tmp->next;
        }
    }
    return *this;
}

template<typename T>
void LinkedList<T>::push_head(T data) {
    Node<T>* ptr = new Node<T>(data);
    ptr->next = head_;
    if (head_)
        head_->prev = ptr;
    if (!tail_)
        tail_ = ptr;
    head_ = ptr;
}

template<typename T>
void LinkedList<T>::push_head(const LinkedList<T>& other) {
    Node<T>* tmp = other.tail_;
    while (tmp) {
        push_head(tmp->data);
        tmp = tmp->prev;
    }
}

template<typename T>
void LinkedList<T>::push_tail(T data) {
    Node<T>* ptr = new Node<T>(data);
    ptr->prev = tail_;
    if (tail_)
        tail_->next = ptr;
    if (!head_)
        head_ = ptr;
    tail_ = ptr;
}

template<typename T>
void LinkedList<T>::push_tail(const LinkedList<T>& other) {
    Node<T>* tmp = other.head_;
    while (tmp) {
        push_tail(tmp->data);
        tmp = tmp->next;
    }
}

template<typename T>
void LinkedList<T>::pop_head() {
    if (!head_) return;
    Node<T>* ptr = head_->next;
    if (ptr)
        ptr->prev = nullptr;
    else
        tail_ = nullptr;
    delete head_;
    head_ = ptr;
}

template<typename T>
void LinkedList<T>::pop_tail() {
    if (!tail_) return;
    Node<T>* ptr = tail_->prev;
    if (ptr)
        ptr->next = nullptr;
    else
        head_ = nullptr;
    delete tail_;
    tail_ = ptr;
}

template<typename T>
Node<T>* LinkedList<T>::at(int index) {
    Node<T>* ptr = head_;
    int i = 0;
    while (i != index) {
        if (!ptr)
            return nullptr;
        ptr = ptr->next;
        i++;
    }
    return ptr;
}

template<typename T>
T& LinkedList<T>::operator[](int index) {
    return at(index)->data;
}

template<typename T>
const T& LinkedList<T>::operator[](int index) const {
    return at(index)->data;
}

template<typename T>
void LinkedList<T>::insert(int index, T data) {
    Node<T>* right = at(index);
    if (!right)
        return push_tail(data);
    Node<T>* left = right->prev;
    if (!left)
        return push_head(data);

    Node<T>* ptr = new Node<T>(data);
    ptr->prev = left;
    ptr->next = right;
    left->next = ptr;
    right->prev = ptr;
}

template<typename T>
Node<T>* LinkedList<T>::earse(int index) {
    Node<T>* ptr = at(index);
    if (!ptr) {
        return nullptr;
    }
    if (!ptr->prev) {
        pop_head();
        return head_;
    }
    if (!ptr->next) {
        pop_tail();
        return nullptr;
    }

    Node<T>* left = ptr->prev;
    Node<T>* right = ptr->next;
    left->next = right;
    right->prev = left;
    delete ptr;

    return right;
}

template<typename T>
void LinkedList<T>::delete_Node(T data) {
    Node<T>* tmp = head_;
    int index = 0;
    while (tmp) {
        if (tmp->data == data) {
            tmp = earse(index);
            continue;
        }
        index++;
        tmp = tmp->next;
    }
}

template<typename T>
void LinkedList<T>::print() const {
    Node<T>* tmp = head_;
    while (tmp) {
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

template<typename T>
void LinkedList<T>::print_path() const {
    Node<T>* tmp = head_;
    if (!tmp) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    std::cout << tmp->data << ":\\";
    tmp = tmp->next;
    while (tmp) {
        if (!tmp->next) {
            std::cout << tmp->data;
            break;
        }
        std::cout << tmp->data << "\\";
        tmp = tmp->next;
    }
}

template<typename T>
void LinkedList<T>::clear() {
    while (head_)
        pop_head();
}

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

#endif