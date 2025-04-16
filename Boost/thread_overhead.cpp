#include <boost/asio.hpp>
#include <iostream>
#include <chrono>

void min_workload() {
    // A simple no-op function to simulate a minimum workload
}

double calculate_thread_pool_overhead(size_t num_threads) {
    // Initialize the thread pool with the specified number of threads
    boost::asio::thread_pool pool(num_threads);

    // Start measuring the time before submitting the task
    auto start_time = std::chrono::high_resolution_clock::now();

    // Submit the minimum workload to the thread pool
    boost::asio::post(pool, min_workload);

    // Wait for all tasks in the pool to finish
    pool.join();

    // End measuring the time after the task is finished
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate the overhead (the time difference)
    std::chrono::duration<double> duration = end_time - start_time;
    return duration.count(); // Returns the time in seconds
}

int main(int argc, char* argv[]) {

    // Calculate the thread pool overhead and output the result
    double overhead_time = calculate_thread_pool_overhead(std::atoi(argv[1]));
    std::cout << "Thread pool overhead time (with " << std::atoi(argv[1]) << " threads): " 
              << overhead_time << " seconds" << std::endl;

    return 0;
}

