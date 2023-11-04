#ifndef LAB_2_INCLUDE_NODE_H
#define LAB_2_INCLUDE_NODE_H

template<typename T>
struct Node {
    T data;
    Node* prev, * next;

    Node(T data) : data(data), prev(nullptr), next(nullptr) {}
};

#endif