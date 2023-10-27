#include <atomic>
#include <memory>
#include "node.cpp"

template<typename T>
class Stack
{
private:
    Node<T>* head;
    std::mutex m;
    std::atomic_int size;
public:
    Stack() : size(0) { }
    void push(const T& data)
    {
        Node<T>* new_node = new Node<T>(data);

        m.lock();
        new_node->next = head;
        head = new_node;
        m.unlock();

        size += 1;
    }
    int get_size() { return size; }
};