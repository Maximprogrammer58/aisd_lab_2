#ifndef LAB_2_INCLUDE_LINKEDLIST_H
#define LAB_2_INCLUDE_LINKEDLIST_H

#include <iostream>
#include <filesystem>
#include <fstream>

#include "Node.h"
#include "Random.h"

template<typename T>
class LinkedList {
    Node<T> *head_, *tail_;
    size_t size_;
 
public:
    LinkedList();

    LinkedList(int length, std::string disk, std::string file_name);

    LinkedList(const LinkedList& other);

    LinkedList& operator=(const LinkedList& other);

    void pushHead(T data);

    void pushHead(const LinkedList& other);

    void pushTail(T data);

    void pushTail(const LinkedList& other);

    void popHead();

    void popTail();

    Node<T>* at(int index);

    size_t size() const;

    T& operator[](int index);

    const T& operator[](int index) const;

    void insert(int index, T data);

    Node<T>* erase(int index);

    void deleteNode(T data);
    
    Node<T>* head() const;

    void clear();

    ~LinkedList();
};

template<typename T>
LinkedList<T>::LinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

template<typename T>
LinkedList<T>::LinkedList(int length, std::string disk, std::string file_name) : LinkedList() {
    pushTail(disk);
    for (int i = 0; i < length - 2; ++i)
        pushTail(generateRandomString(generateRandomNumber(1, 10)));
    pushTail(file_name);
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
    Node<T>* tmp = other.head_;
    while (tmp) {
        pushTail(tmp->data);
        tmp = tmp->next;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {
        clear();
        Node<T>* tmp = other.head_;
        while (tmp) {
            pushTail(tmp->data);
            tmp = tmp->next;
        }
    }
    return *this;
}

template<typename T>
void LinkedList<T>::pushHead(T data) {
    Node<T>* ptr = new Node<T>(data);
    ptr->next = head_;
    if (head_)
        head_->prev = ptr;
    if (!tail_)
        tail_ = ptr;
    head_ = ptr;
    size_++;
}

template<typename T>
void LinkedList<T>::pushHead(const LinkedList<T>& other) {
    Node<T>* tmp = other.tail_;
    while (tmp) {
        pushHead(tmp->data);
        tmp = tmp->prev;
    }
}

template<typename T>
void LinkedList<T>::pushTail(T data) {
    Node<T>* ptr = new Node<T>(data);
    ptr->prev = tail_;
    if (tail_)
        tail_->next = ptr;
    if (!head_)
        head_ = ptr;
    tail_ = ptr;
    size_++;
}

template<typename T>
void LinkedList<T>::pushTail(const LinkedList<T>& other) {
    Node<T>* tmp = other.head_;
    while (tmp) {
        pushTail(tmp->data);
        tmp = tmp->next;
    }
}

template<typename T>
void LinkedList<T>::popHead() {
    if (!head_) return;
    Node<T>* ptr = head_->next;
    if (ptr)
        ptr->prev = nullptr;
    else
        tail_ = nullptr;
    delete head_;
    head_ = ptr;
    size_--;
}

template<typename T>
void LinkedList<T>::popTail() {
    if (!tail_) return;
    Node<T>* ptr = tail_->prev;
    if (ptr)
        ptr->next = nullptr;
    else
        head_ = nullptr;
    delete tail_;
    tail_ = ptr;
    size_--;
}

template<typename T>
size_t  LinkedList<T>::size() const {
    return size_;
}

template<typename T>
Node<T>* LinkedList<T>::head() const {
    return head_;
}

template<typename T>
Node<T>* LinkedList<T>::at(int index) {
    if ((index < 0) && (index >= size_)) 
        throw std::out_of_range("Index out of range");
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
        return pushTail(data);
    Node<T>* left = right->prev;
    if (!left)
        return pushHead(data);

    Node<T>* ptr = new Node<T>(data);
    ptr->prev = left;
    ptr->next = right;
    left->next = ptr;
    right->prev = ptr;
}

template<typename T>
Node<T>* LinkedList<T>::erase(int index) {
    Node<T>* ptr = at(index);
    if (!ptr) {
        return nullptr;
    }
    if (!ptr->prev) {
        popHead();
        return head_;
    }
    if (!ptr->next) {
        popTail();
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
void LinkedList<T>::deleteNode(T data) {
    Node<T>* tmp = head_;
    int index = 0;
    while (tmp) {
        if (tmp->data == data) {
            tmp = erase(index);
            continue;
        }
        index++;
        tmp = tmp->next;
    }
}

template<typename T>
void LinkedList<T>::clear() {
    size_ = 0;
    while (head_)
        popHead();
}

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

#endif