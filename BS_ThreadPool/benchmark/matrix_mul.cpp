#include "../include/BS_thread_pool.hpp"     // BS::thread_pool
#include <chrono>                 // std::chrono
#include <future>                 // std::future
#include <iostream>               // std::cout
#include <random>                // std::mt19937, std::uniform_int_distribution
#include <vector>                 // std::vector
#include <cstdlib>

constexpr int MATRIX_SIZE = 1000;
constexpr int NUM_THREADS = 24;

void multiply_rows(const std::vector<std::vector<int>>& A,
                   const std::vector<std::vector<int>>& B,
                   std::vector<std::vector<int>>& C,
                   int row_start, int row_end)
{
    for (int i = row_start; i < row_end; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            int sum = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k)
            {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main(int argc, char* argv[])
{
    // Initialize matrices
    std::vector<std::vector<int>> A(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE));
    std::vector<std::vector<int>> B(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE));
    std::vector<std::vector<int>> C(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE, 0));

    // Fill A and B with random integers
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(1, 10);
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
        }
    }

    BS::thread_pool pool(std::atoi(argv[1]));
    std::vector<std::future<void>> futures;

    const auto start = std::chrono::high_resolution_clock::now();

    // Divide work into row chunks
    int chunk_size = MATRIX_SIZE / NUM_THREADS;
    for (int t = 0; t < NUM_THREADS; ++t)
    {
        int row_start = t * chunk_size;
        int row_end = (t == NUM_THREADS - 1) ? MATRIX_SIZE : row_start + chunk_size;

        futures.push_back(pool.submit_task(
            [&, row_start, row_end]
            {
                multiply_rows(A, B, C, row_start, row_end);
            }));
    }

    // Wait for all tasks to complete
    for (auto& fut : futures)
    {
        fut.wait();
    }

    const auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time passed: " << duration << " milliseconds\n";
    std::cout << "C[0][0] = " << C[0][0] << '\n';

    return 0;
}

