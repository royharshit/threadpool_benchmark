#include <iostream>
#include <chrono>
#include <vector>
#include <future>
#include "../include/BS_thread_pool.hpp"  // Make sure this header is available
#include <cstdlib>

// A simple no-op task
void no_op_task(int) {
    // Intentionally left blank
}

double calculate_thread_pool_overhead_with_bs(size_t num_threads) {
    BS::thread_pool pool(num_threads);

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::future<void>> futures;

    for (int i = 0; i < 1000; ++i) {
        // Submit no-op tasks to the thread pool
        futures.push_back(pool.submit_task([i]() {
            no_op_task(i);
        }));
    }

    // Wait for all tasks to complete
    for (auto& future : futures) {
        future.get();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    return duration.count();  // Return time in seconds
}

int main(int argc, char* argv[]) {
    size_t num_threads = 12;

    double overhead_time = calculate_thread_pool_overhead_with_bs(std::atoi(argv[1]));
    std::cout << "Thread pool overhead time (with " << num_threads << " threads): "
              << overhead_time << " seconds" << std::endl;

    return 0;
}

