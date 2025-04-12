#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <tbb/tbb.h>
#include <thread>
#include <string>
#include <cstdio>
#include <future>

std::chrono::time_point<std::chrono::high_resolution_clock> main_start;

// Function to simulate a CPU-bound task (e.g., matrix multiplication)
void cpu_bound_task(int id) {
    auto start = std::chrono::high_resolution_clock::now();

    // Simulating a CPU-intensive task (calculating primes)
    const int matrix_size = 1000;  // 1000x1000 matrices
    std::vector<std::vector<int>> A(matrix_size, std::vector<int>(matrix_size, 1));  // Matrix A (initialized with 1)
    std::vector<std::vector<int>> B(matrix_size, std::vector<int>(matrix_size, 2));  // Matrix B (initialized with 2)
    std::vector<std::vector<int>> C(matrix_size, std::vector<int>(matrix_size, 0));  // Result matrix C

    // Perform matrix multiplication: C = A * B
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            for (int k = 0; k < matrix_size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    printf("CPU Task %d started at %ld ms, ended at %ld ms, duration: %.6f seconds.\n",
           id,
           std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch() - main_start.time_since_epoch()).count(),
           std::chrono::duration_cast<std::chrono::milliseconds>(end.time_since_epoch() - main_start.time_since_epoch()).count(),
           duration.count());
}

// Function to simulate a real I/O-bound task (reading and writing to a file character by character)
void io_bound_task(int id, const std::string& filename) {
    auto start = std::chrono::high_resolution_clock::now();

    // Open the file to read character by character
    std::ifstream input_file(filename, std::ios::in);
    std::ofstream output_file("output_file.dat", std::ios::out);

    if (input_file && output_file) {
        char ch;
        // Read character by character from the input file
        while (input_file.get(ch)) {
            // Write character by character to the output file
            output_file.put(ch);
        }
        input_file.close();
        output_file.close();
    } else {
        std::cerr << "Error opening files." << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    printf("I/O Task %d started at %ld ms, ended at %ld ms, duration: %.6f seconds.\n",
           id,
           std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch() - main_start.time_since_epoch()).count(),
           std::chrono::duration_cast<std::chrono::milliseconds>(end.time_since_epoch() - main_start.time_since_epoch()).count(),
           duration.count());
}

int main(int argc, char* argv[]) {
    const int num_tasks = 10;
    const int half_cpu_bound = num_tasks / 2;
    const int half_io_bound = num_tasks / 2;
    const std::string filename = "test_file.dat";  // Name of the test file for I/O-bound tasks

    auto main_start = std::chrono::high_resolution_clock::now();

    // Step 1: Create a large file (if it doesn't already exist)
    std::ofstream file(filename, std::ios::out);
    if (file) {
        size_t data_size = 1024 * 1024 * 512; // 512MB of data
        for (size_t i = 0; i < data_size; ++i) {
            file.put('A');  // Write one character at a time
        }
        file.close();
    } else {
        std::cerr << "Error creating test file." << std::endl;
        return 1;
    }

    // Step 2: Define the number of threads in the task arena
    tbb::task_arena arena(std::atoi(argv[1]));    // Step 3: Use the task arena to manage the execution of tasks
    arena.execute([&]() {
        // Using parallel_for to manage both CPU-bound and I/O-bound tasks

        tbb::parallel_invoke(
            [&]() {  // Task for method1 on a range of i
                tbb::parallel_for(0, half_cpu_bound, 1, [&](int i) {
                    cpu_bound_task(i);
                });
            },
            [&]() {  // Task for method2 on a different range of i
                tbb::parallel_for(0, half_io_bound, 1, [&](int i) {
                    io_bound_task(i, filename);
                });

                //std::vector<std::future<void>> futures;
                //for (int i = 0; i < half_io_bound; ++i) {
                //    futures.push_back(std::async(std::launch::async, io_bound_task, i, filename));
                //}

                //// Wait for all the I/O tasks to complete
                //for (auto& future : futures) {
                //    future.get();  // Blocks until each I/O task is finished
                //}
            }
        );

    });

    return 0;
}

