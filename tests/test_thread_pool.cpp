// tests/test_thread_pool.cpp
#include "thread_pool.h"
#include <cassert>
#include <iostream>
#include <atomic>
#include <thread>

void test_single_task_execution() {
    ThreadPool pool(1);
    std::atomic<bool> taskExecuted(false);

    pool.enqueue([&taskExecuted]() {
        taskExecuted = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for task to execute
    assert(taskExecuted.load());
}

void test_multiple_tasks_execution() {
    ThreadPool pool(2);
    std::atomic<int> taskCount(0);

    pool.enqueue([&taskCount]() { taskCount++; });
    pool.enqueue([&taskCount]() { taskCount++; });

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for tasks to execute
    assert(taskCount.load() == 2);
}

void test_stop_thread_pool() {
    ThreadPool pool(2);
    pool.enqueue([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    });

    // The pool will be destroyed and all threads should be joined
}

int main() {
    test_single_task_execution();
    test_multiple_tasks_execution();
    test_stop_thread_pool();
    std::cout << "ThreadPool tests passed!" << std::endl;
    return 0;
}