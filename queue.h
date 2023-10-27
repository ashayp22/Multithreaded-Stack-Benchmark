#pragma once

template <typename T>
class LockFreeQueue
{
private:
    struct Node
    {
        std::shared_ptr<T> data;
        std::atomic<node *> next;
        node(T const &data_) : data(std::make_shared<T>(data_))
        {
        }
    };
    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:
    void push(T const &data);
    std::shared_ptr<T> pop();
};