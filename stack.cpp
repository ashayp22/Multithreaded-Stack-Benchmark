#include <atomic>
#include <memory>
#include "node.cpp"

template<typename T>
class Stack
{
private:
    Node<T>* head;
    std::mutex m;
    int counter = 0;
public:
    Stack() : head(nullptr) { } 
    void push(const T& data)
    {
        Node<T>* new_node = new Node<T>(data);

        m.lock();
        new_node->next = head;
        head = new_node;
        m.unlock();
    }
    int get_size() { 
        int size = 0;
        Node<T>* curr = head;

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