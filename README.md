# Benchmarking Stack Performance in C++

I was curious what the performance difference was between using atomics and mutexes as a locking mechanism in C++, so that data reads/writes can occur in multithreaded situations without data races.

I implemented two stacks, one with a mutex and one with atomics, and benchmarked with Google Benchmark to see how long it would take to add ints to the stack in different settings. So far, mutex locks perform better than atomics, and so as of 10/27/23 I am looking into why this is the case.

### 1 Thread, 10000 Objects Each

![1 Thread, 10000 Objects Each](results/1Thread10000Obj.png)

### 10 Threads, 1000 Objects Each

![10 Threads, 1000 Objects Each](results/10Thread1000Obj.png)

### 100 Threads, 1000 Objects Each

![100 Threads, 1000 Objects Each](results/100Thread1000Obj.png)

## Installation

1. Install [Google Benchmark](https://github.com/google/benchmark) to the root directory
2. Run `make`