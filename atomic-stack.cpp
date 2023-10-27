#pragma once

#include <atomic>
#include <memory>
#include "node.cpp"

template<typename T>
class AtomicStack
{
private:
    std::atomic<AtomicNode<T>*> head;
    std::atomic_int size;
public:
    AtomicStack() : size(0) { }
    void push(const T& data)
    {
        AtomicNode<T>* new_AtomicNode = new AtomicNode<T>(data);
        AtomicNode<T>* old_head = head.load(std::memory_order_relaxed);

        while(!head.compare_exchange_weak(old_head, new_AtomicNode, std::memory_order_release, std::memory_order_relaxed));

        new_AtomicNode->next = old_head;

        size += 1;
    }
    int get_size() { return size; }
};