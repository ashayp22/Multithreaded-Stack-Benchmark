#pragma once

#include "node.cpp"
#include "atomic-lock.cpp"

template<typename T>
class AtomicLockStack
{
private:
    AtomicNode<T>* head;
    AtomicLock m;
    int counter = 0;
public:
    AtomicLockStack() : head(nullptr) { }
    void push(const T& data)
    {
        AtomicNode<T>* new_node = new AtomicNode<T>(data);

        m.lock();
        new_node->next = head;
        head = new_node;
        m.unlock();
    }
    int get_size() { 
        int size = 0;
        AtomicNode<T>* curr = head;

        while (curr != nullptr) {
            size += 1;
            curr = curr->next;
        }

        return size;
    }
    void increment() {
        m.lock();
        counter += 1;
        m.unlock();
    }
    int get_counter() {
        return counter;
    }
};