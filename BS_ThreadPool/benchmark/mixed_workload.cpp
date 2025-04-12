#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <future>
#include <cstdlib>
#include "../include/BS_thread_pool.hpp"  // Make sure this header is available in your project

#define CHUNK_SIZE 1000000   // Numbers per chunk
#define NUMBERS_TO_GENERATE 250000000 // Total random numbers (e.g., ~8GB of 32-bit ints)

#define FILE_NAME "large_random_numbers.txt"
#define SORTED_FILE "sorted_large_random_numbers.txt"

// Function to compare two integers (used by qsort)
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Generate a large file with random numbers
void generate_large_file() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < NUMBERS_TO_GENERATE; i++) {
        fprintf(file, "%d\n", rand() % 1000000);
    }

    fclose(file);
}

// Sort a chunk of numbers from the large file
void sort_chunk(int chunk_number) {
    int numbers[CHUNK_SIZE];
    char chunk_filename[100];

    snprintf(chunk_filename, sizeof(chunk_filename), "chunk_%d.txt", chunk_number);
    FILE *chunk_file = fopen(chunk_filename, "w");
    if (chunk_file == NULL) {
        perror("Failed to open chunk file for writing");
        exit(1);
    }

    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Failed to open large file for reading");
        exit(1);
    }

    // Seek to appropriate chunk location
    fseek(file, 0, SEEK_SET);
    int line_num = 0;
    int start_line = chunk_number * CHUNK_SIZE;
    int end_line = start_line + CHUNK_SIZE;
    char line[20];

    // Skip lines before our chunk
    while (line_num < start_line && fgets(line, sizeof(line), file)) {
        line_num++;
    }

    // Read the chunk
    int i = 0;
    while (line_num < end_line && fgets(line, sizeof(line), file)) {
        numbers[i++] = atoi(line);
        line_num++;
    }
    fclose(file);

    // Sort
    qsort(numbers, i, sizeof(int), compare);

    // Write sorted numbers
    for (int j = 0; j < i; j++) {
        fprintf(chunk_file, "%d\n", numbers[j]);
    }
    fclose(chunk_file);
}

// Merge sorted chunks
void merge_sorted_chunks() {
    FILE *sorted_file = fopen(SORTED_FILE, "w");
    if (sorted_file == NULL) {
        perror("Failed to open sorted file for writing");
        exit(1);
    }

    int num_chunks = NUMBERS_TO_GENERATE / CHUNK_SIZE;
    FILE *chunk_files[num_chunks];
    int current_values[num_chunks];

    for (int i = 0; i < num_chunks; i++) {
        char chunk_filename[100];
        snprintf(chunk_filename, sizeof(chunk_filename), "chunk_%d.txt", i);
        chunk_files[i] = fopen(chunk_filename, "r");
        if (chunk_files[i] == NULL) {
            perror("Failed to open chunk file");
            exit(1);
        }

        fscanf(chunk_files[i], "%d", &current_values[i]);
    }

    while (true) {
        int min_index = -1;
        int min_value = INT32_MAX;

        for (int i = 0; i < num_chunks; i++) {
            if (chunk_files[i] != NULL && current_values[i] < min_value) {
                min_value = current_values[i];
                min_index = i;
            }
        }

        if (min_index == -1) break;

        fprintf(sorted_file, "%d\n", min_value);

        if (fscanf(chunk_files[min_index], "%d", &current_values[min_index]) != 1) {
            fclose(chunk_files[min_index]);
            chunk_files[min_index] = NULL;
        }
    }

    fclose(sorted_file);
}

int main(int argc, char* argv[]) {
    // Step 1: Generate random numbers file
    generate_large_file();
    std::cout << "Generated large random number file.\n";

    auto start = std::chrono::high_resolution_clock::now();

    int num_chunks = NUMBERS_TO_GENERATE / CHUNK_SIZE;

    // Step 2: Initialize thread pool with desired number of threads
    BS::thread_pool pool(std::atoi(argv[1]));  // or specify fixed thread count
    std::vector<std::future<void>> futures;

    // Step 3: Submit sorting tasks
    for (int chunk = 0; chunk < num_chunks; ++chunk) {
        futures.push_back(pool.submit_task([chunk]() {
            sort_chunk(chunk);
        }));
    }

    // Step 4: Wait for all tasks to complete
    for (auto &f : futures) {
        f.get();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time passed for parallel sorting: " << duration_ms << " ms\n";

    // Step 5: Merge sorted chunks
    merge_sorted_chunks();
    std::cout << "Merged all sorted chunks into final sorted file.\n";

    return 0;
}

