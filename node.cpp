#pragma once

template<typename T>
struct Node
{ 
    T data;
    Node<T>* next;
    Node(const T& data) : data(data), next(nullptr) {}
};

template<typename T>
struct AtomicNode
{
    T data;
    AtomicNode<T>* next;
    AtomicNode(const T& data) : data(data), next(nullptr) {}
};
 