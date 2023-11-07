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

    T& operator[](int index);

    const T& operator[](int index) const;

    void insert(int index, T data);

    Node<T>* earse(int index);

    void deleteNode(T data);
    
    void printPath() const;

    void createFileNotExist() const;

    std::string createPath() const;

    bool isCorrectPath() const;

    void clear();

    ~LinkedList();
};

template<typename T>
LinkedList<T>::LinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
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
Node<T>* LinkedList<T>::earse(int index) {
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
            tmp = earse(index);
            continue;
        }
        index++;
        tmp = tmp->next;
    }
}

template<typename T>
void LinkedList<T>::clear() {
    while (head_)
        popHead();
}

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
std::string LinkedList<T>::createPath() const {
    std::string path;
    Node<T>* tmp = head_;
    if (!tmp) {
        std::cout << "List is empty" << std::endl;
        return "";
    }
    path += tmp->data + ":\\";
    tmp = tmp->next;
    while (tmp) {
        if (!tmp->next) {
            path += tmp->data;
            break;
        }
        path += tmp->data + "\\";
        tmp = tmp->next;
    }
    return path;
}

template<typename T>
void LinkedList<T>::printPath() const {
    std::cout << createPath() << std::endl;
}

template<typename T>
bool LinkedList<T>::isCorrectPath() const {
    std::string path = createPath();
    if (std::filesystem::exists(path)) {
        std::cout << "File exists" << std::endl;
        return true;
    }
    std::cout << "File doesn't exist" << std::endl;
    return false;
}

template<typename T>
void LinkedList<T>::createFileNotExist() const {
    std::string filepath;
    Node<T>* tmp = head_;
    if (!tmp) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    filepath += tmp->data + ":\\";
    tmp = tmp->next;
    while (tmp) {
        if (!tmp->next)
            break;
        filepath += tmp->data + "\\";
        tmp = tmp->next;
    }
    std::filesystem::path path{ filepath };
    path /= tail_->data;
    std::filesystem::create_directories(path.parent_path());
    std::ofstream ofs(path);
    ofs.close();
}

#endif