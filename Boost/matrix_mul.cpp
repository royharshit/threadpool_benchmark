#include <iostream>
#include <vector>
#include <random>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>
#include <chrono>

const int MATRIX_SIZE = 10000; // Size of the matrices (1000x1000 for high workload)

void matrix_multiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int row_start, int row_end) {
    for (int i = row_start; i < row_end; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // Initialize the matrices A, B, and C
    std::vector<std::vector<int>> A(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE));
    std::vector<std::vector<int>> B(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE));
    std::vector<std::vector<int>> C(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE, 0));

    // Random number generator to fill the matrices A and B
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);

    // Fill matrices A and B with random integers
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
        }
    }

    // Set up Boost thread pool
    boost::asio::thread_pool pool(24);  // Using 24 threads

    auto start = std::chrono::high_resolution_clock::now();

    // Submit tasks to the thread pool
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        boost::asio::post(pool, [&A, &B, &C, i]() {
            matrix_multiply(A, B, C, i, i + 1);  // Multiply one row at a time
        });
    }

    // Wait for all tasks to finish
    pool.join();

    auto end = std::chrono::high_resolution_clock::now();

    // Calculate and print the elapsed time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time passed: " << duration << " milliseconds" << std::endl;

    // Optionally, print a small part of the result for verification
    std::cout << "C[0][0] = " << C[0][0] << std::endl;

    return 0;
}

