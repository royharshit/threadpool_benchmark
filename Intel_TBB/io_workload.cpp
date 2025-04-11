#include <tbb/tbb.h>
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

    // Write operation first
    std::ofstream outfile(filename, std::ios::binary);
    if (outfile.is_open()) {
        std::vector<char> buffer(FILE_SIZE_BYTES, 'A'); // 100MB of 'A'
        outfile.write(buffer.data(), buffer.size());
        outfile.close();
        std::cout << "Task " << id << " created a 100MB file.\n";
    }

    // Read operation follows immediately after write
    std::ifstream infile(filename, std::ios::binary);
    if (infile.is_open()) {
        std::vector<char> readBuffer(FILE_SIZE_BYTES);
        infile.read(readBuffer.data(), FILE_SIZE_BYTES);
        infile.close();
        std::cout << "Task " << id << " successfully read the 100MB file.\n";
    }
}

int main() {

    tbb::task_arena arena(THREAD_POOL_SIZE);

    std::vector<int> taskIDs(NUM_TASKS);
    for (int i = 0; i < NUM_TASKS; ++i) {
        taskIDs[i] = i;
    }

    // Measure total execution time
    auto global_start = std::chrono::high_resolution_clock::now();

    arena.execute([&]() {
        tbb::parallel_for(tbb::blocked_range<int>(0, NUM_TASKS), [&](const tbb::blocked_range<int>& range) {
            for (int i = range.begin(); i < range.end(); ++i) {
                processFile(taskIDs[i]);
            }
        });
    });

    auto global_end = std::chrono::high_resolution_clock::now();
    auto global_duration = std::chrono::duration_cast<std::chrono::milliseconds>(global_end - global_start);

    std::cout << "Total execution time for arena: " << global_duration.count() << " ms.\n";

    return 0;

}

