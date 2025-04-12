#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

constexpr int NUM_TASKS = 50;
constexpr int THREAD_POOL_SIZE = 6;
constexpr size_t FILE_SIZE_MB = 100;
constexpr size_t FILE_SIZE_BYTES = FILE_SIZE_MB * 1024 * 1024;

void processFile(int id) {
    std::string filename = "file_" + std::to_string(id) + ".txt";

    // Write operation: Create a 100MB file
    std::ofstream outfile(filename, std::ios::binary);
    if (outfile.is_open()) {
        std::vector<char> buffer(FILE_SIZE_BYTES, 'A'); // 100MB of 'A'
        outfile.write(buffer.data(), buffer.size());
        outfile.close();
        std::cout << "Task " << id << " created a 100MB file.\n";
    } else {
        std::cerr << "Task " << id << " - Error writing file!\n";
    }

    // Read operation follows immediately after write
    std::ifstream infile(filename, std::ios::binary);
    if (infile.is_open()) {
        std::vector<char> readBuffer(FILE_SIZE_BYTES);
        infile.read(readBuffer.data(), FILE_SIZE_BYTES);
        infile.close();
        std::cout << "Task " << id << " successfully read the 100MB file.\n";
    } else {
        std::cerr << "Task " << id << " - Error reading file!\n";
    }
}

int main() {
    // Create Boost thread pool
    boost::asio::thread_pool pool(THREAD_POOL_SIZE);

    auto global_start = std::chrono::high_resolution_clock::now();

    // Submit tasks to thread pool
    for (int i = 0; i < NUM_TASKS; ++i) {
        boost::asio::post(pool, [i]() { processFile(i); });
    }

    pool.join(); // Wait for all tasks to finish

    auto global_end = std::chrono::high_resolution_clock::now();
    auto global_duration = std::chrono::duration_cast<std::chrono::milliseconds>(global_end - global_start);

    std::cout << "Total execution time for thread pool: " << global_duration.count() << " ms.\n";

    return 0;
}

