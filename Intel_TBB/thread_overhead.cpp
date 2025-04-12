#include <tbb/tbb.h>
#include <iostream>
#include <chrono>
#include <cstdio>

// A simple no-op function to simulate minimal workload (just to measure thread overhead)
void no_op_task(int) {
    // No operation here, just to simulate thread usage
}

double calculate_thread_pool_overhead_with_tbb(size_t num_threads) {
    // Create a task arena with the specified number of threads
    tbb::task_arena arena(num_threads);

    // Start measuring the time before starting the task
    auto start = std::chrono::high_resolution_clock::now();

    // Use the task arena to execute parallel_for inside the arena scope
    arena.execute([&]() {
        // Execute no-op tasks in parallel
        tbb::parallel_for(0, 1000, 1, [](int) {
            no_op_task(0); // No-op task, just to measure thread overhead
        });
    });

    // End measuring time after task execution
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the overhead (time difference)
    std::chrono::duration<double> duration = end - start;
    return duration.count(); // Return time in seconds
}

int main(int argc, char* argv[]) {

    // Calculate the thread pool overhead using TBB and output the result
    double overhead_time = calculate_thread_pool_overhead_with_tbb(std::atoi(argv[1]));
    std::cout << "Thread pool overhead time (with " << std::atoi(argv[1]) << " threads): " 
              << overhead_time << " seconds" << std::endl;

    return 0;
}

