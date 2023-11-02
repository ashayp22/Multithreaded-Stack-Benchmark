#pragma once

#include <atomic>
#include <memory>
#include "node.cpp"

template<typename T>
class AtomicStack
{
private:
    std::atomic<AtomicNode<T>*> head;
    std::atomic<int> counter{};
public:
    AtomicStack() : head(nullptr) { }
    void push(const T& data)
    {
        AtomicNode<T>* new_AtomicNode = new AtomicNode<T>(data);
        AtomicNode<T>* old_head = head.load(std::memory_order_relaxed);

        while(!head.compare_exchange_weak(old_head, new_AtomicNode, std::memory_order_release, std::memory_order_relaxed));

        new_AtomicNode->next = old_head;
    }
    int get_size() { 
        AtomicNode<T>* curr = head.load(std::memory_order_relaxed);

        int size = 0;
        while (curr != nullptr) {
            size += 1;
            curr = curr->next;
        }

        return size;
    }
    void increment() {
        counter++;
    }
    int get_counter() {
        return counter;
    }
};