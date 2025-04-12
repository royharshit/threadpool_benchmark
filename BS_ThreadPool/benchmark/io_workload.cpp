#include "../include/BS_thread_pool.hpp"     // BS::thread_pool
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <future>

constexpr int NUM_TASKS = 50;
constexpr int THREAD_POOL_SIZE = 6;
constexpr size_t FILE_SIZE_MB = 100;
constexpr size_t FILE_SIZE_BYTES = FILE_SIZE_MB * 1024 * 1024;

void processFile(int id) {
    std::string filename = "file_" + std::to_string(id) + ".txt";

    // Write operation
    std::ofstream outfile(filename, std::ios::binary);
    if (outfile.is_open()) {
        std::vector<char> buffer(FILE_SIZE_BYTES, 'A'); // 100MB of 'A'
        outfile.write(buffer.data(), buffer.size());
        outfile.close();
        std::cout << "Task " << id << " created a 100MB file.\n";
    }

    // Read operation
    std::ifstream infile(filename, std::ios::binary);
    if (infile.is_open()) {
        std::vector<char> readBuffer(FILE_SIZE_BYTES);
        infile.read(readBuffer.data(), FILE_SIZE_BYTES);
        infile.close();
        std::cout << "Task " << id << " successfully read the 100MB file.\n";
    }
}

int main() {
    BS::thread_pool pool(THREAD_POOL_SIZE);
    std::vector<std::future<void>> futures;

    // Measure total execution time
    auto global_start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_TASKS; ++i) {
        futures.push_back(pool.submit_task([i]() {
            processFile(i);
        }));
    }

    for (auto& fut : futures) {
        fut.wait();
    }

    auto global_end = std::chrono::high_resolution_clock::now();
    auto global_duration = std::chrono::duration_cast<std::chrono::milliseconds>(global_end - global_start);

    std::cout << "Total execution time with BS::thread_pool: " << global_duration.count() << " ms.\n";

    return 0;
}

