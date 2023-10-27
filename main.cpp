#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include "atomic-stack.cpp"
#include "stack.cpp"
#include <time.h> 
#include <iomanip>
#include <benchmark/benchmark.h>

using namespace std; 

const int NUM_THREADS = 10;
const int NUM_OBJS = 10000;

static void BM_AtomicStack(benchmark::State& state) {
  // Perform setup here
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

BENCHMARK(BM_AtomicStack);

static void BM_Stack(benchmark::State& state) {
  // Perform setup here
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

BENCHMARK(BM_Stack);

BENCHMARK_MAIN();
