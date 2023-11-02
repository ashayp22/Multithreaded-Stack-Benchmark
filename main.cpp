#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include "atomic-stack.cpp"
#include "atomic-lock-stack.cpp"
#include "stack.cpp"
#include <time.h> 
#include <iomanip>
#include <benchmark/benchmark.h>

using namespace std; 

const int NUM_THREADS = 10;
const int NUM_OBJS = 1000;

static void BM_MutexIncrement(benchmark::State& state) {
  for (auto _ : state) {
    Stack<int> stack;

    std::vector<std::thread> threads;
    for (int i=0; i< NUM_THREADS; ++i) {
      threads.push_back(
      std::thread([&stack](){
        for (int i = 0; i < NUM_OBJS; i++) {
          stack.increment();
        }
      }));
    }
    for (auto& th : threads) th.join();

    assert(stack.get_counter() == NUM_THREADS*NUM_OBJS);
  }
}

static void BM_AtomicLockIncrement(benchmark::State& state) {
  for (auto _ : state) {
    AtomicLockStack<int> stack;

    std::vector<std::thread> threads;
    for (int i=0; i< NUM_THREADS; ++i) {
      threads.push_back(
      std::thread([&stack](){
        for (int i = 0; i < NUM_OBJS; i++) {
          stack.increment();
        }
      }));
    }
    for (auto& th : threads) th.join();

    assert(stack.get_counter() == NUM_THREADS*NUM_OBJS);
  }
}

static void BM_AtomicIncrement(benchmark::State& state) {
  for (auto _ : state) {
    AtomicStack<int> stack;

    std::vector<std::thread> threads;
    for (int i=0; i< NUM_THREADS; ++i) {
      threads.push_back(
      std::thread([&stack](){
        for (int i = 0; i < NUM_OBJS; i++) {
          stack.increment();
        }
      }));
    }
    for (auto& th : threads) th.join();

    assert(stack.get_counter() == NUM_THREADS*NUM_OBJS);
  }
}

static void BM_AtomicLockStack(benchmark::State& state) {
  for (auto _ : state) {
    AtomicLockStack<int> atomicStack;

    std::vector<std::thread> threads;
    for (int i=0; i< NUM_THREADS; ++i) {
      threads.push_back(
      std::thread([&atomicStack](){
        for (int i = 0; i < NUM_OBJS; i++) {
          atomicStack.push(1);
        }
      }));
    }
    for (auto& th : threads) th.join();

    assert(atomicStack.get_size() == NUM_THREADS*NUM_OBJS);
  }
}

static void BM_AtomicStack(benchmark::State& state) {
  for (auto _ : state) {
    AtomicStack<int> atomicStack;

    std::vector<std::thread> threads;
    for (int i=0; i< NUM_THREADS; ++i) {
      threads.push_back(
      std::thread([&atomicStack](){
        for (int i = 0; i < NUM_OBJS; i++) {
          atomicStack.push(1);
        }
      }));
    }
    for (auto& th : threads) th.join();

    assert(atomicStack.get_size() == NUM_THREADS*NUM_OBJS);
  }
}

static void BM_Stack(benchmark::State& state) {
  for (auto _ : state) {
    Stack<int> stack;

    std::vector<std::thread> threads;
    for (int i=0; i< NUM_THREADS; ++i) {
      threads.push_back(
      std::thread([&stack](){
        for (int i = 0; i < NUM_OBJS; i++) {
          stack.push(1);
        }
      }));
    }
    for (auto& th : threads) th.join(); 

    assert(stack.get_size() == NUM_THREADS*NUM_OBJS);
  }
}
BENCHMARK(BM_MutexIncrement);
BENCHMARK(BM_AtomicLockIncrement);
BENCHMARK(BM_AtomicIncrement);
BENCHMARK(BM_AtomicLockStack);
BENCHMARK(BM_AtomicStack);
BENCHMARK(BM_Stack);

BENCHMARK_MAIN();
