#pragma once

#include <atomic>
#include <memory>

const int UNLOCKED = 0;
const int LOCKED = 1;

class AtomicLock
{
    std::atomic<bool> flag;
public:
    AtomicLock () : flag(false) { }
    void lock()
    {
        while (flag.exchange(true, std::memory_order_relaxed));
        std::atomic_thread_fence(std::memory_order_acquire);
    }

    void unlock()
    {
        std::atomic_thread_fence(std::memory_order_release);
        flag.store(false, std::memory_order_relaxed);
    }
};
