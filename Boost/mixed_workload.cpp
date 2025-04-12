#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <iostream>
#include <boost/asio.hpp>
#include <chrono>

#define CHUNK_SIZE 1000000   // Numbers to sort per chunk (around 4MB for 4-byte integers)
#define NUMBERS_TO_GENERATE 250000000 // 8GB of integers (2 billion random numbers)

#define FILE_NAME "large_random_numbers.txt"
#define SORTED_FILE "sorted_large_random_numbers.txt"

// Function to compare two integers (used for qsort)
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

    srand(time(NULL));  // Seed random number generator

    for (int i = 0; i < NUMBERS_TO_GENERATE; i++) {
        fprintf(file, "%d\n", rand() % 1000000);  // Random numbers between 0 and 999999
    }

    fclose(file);
}

// Sort a chunk of numbers from the file
void sort_chunk(int chunk_number) {
    int numbers[CHUNK_SIZE];
    char chunk_filename[100];
    
    // Open the chunk file for reading and sorting
    snprintf(chunk_filename, sizeof(chunk_filename), "chunk_%d.txt", chunk_number);
    FILE *chunk_file = fopen(chunk_filename, "w");
    if (chunk_file == NULL) {
        perror("Failed to open chunk file for writing");
        exit(1);
    }

    // Read the chunk from the large file
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Failed to open large file for reading");
        exit(1);
    }

    fseek(file, chunk_number * CHUNK_SIZE * sizeof(int), SEEK_SET);
    for (int i = 0; i < CHUNK_SIZE; i++) {
        fscanf(file, "%d", &numbers[i]);
    }

    fclose(file);

    // Sort the chunk of numbers
    qsort(numbers, CHUNK_SIZE, sizeof(int), compare);

    // Write the sorted numbers to the chunk file
    for (int i = 0; i < CHUNK_SIZE; i++) {
        fprintf(chunk_file, "%d\n", numbers[i]);
    }

    fclose(chunk_file);
}

// Merge sorted chunks into the final sorted file
void merge_sorted_chunks() {
    FILE *sorted_file = fopen(SORTED_FILE, "w");
    if (sorted_file == NULL) {
        perror("Failed to open sorted file for writing");
        exit(1);
    }

    FILE *chunk_files[NUMBERS_TO_GENERATE / CHUNK_SIZE];
    int numbers[NUMBERS_TO_GENERATE / CHUNK_SIZE];
    int num_chunks = NUMBERS_TO_GENERATE / CHUNK_SIZE;

    // Open all chunk files
    for (int i = 0; i < num_chunks; i++) {
        char chunk_filename[100];
        snprintf(chunk_filename, sizeof(chunk_filename), "chunk_%d.txt", i);
        chunk_files[i] = fopen(chunk_filename, "r");
        if (chunk_files[i] == NULL) {
            perror("Failed to open chunk file for reading");
            exit(1);
        }

        // Read the first number from each chunk file
        fscanf(chunk_files[i], "%d", &numbers[i]);
    }

    // Merge all chunks (using a simple priority approach)
    while (1) {
        int min_value = INT32_MAX;
        int min_index = -1;

        // Find the smallest number among the chunks
        for (int i = 0; i < num_chunks; i++) {
            if (chunk_files[i] != NULL && numbers[i] < min_value) {
                min_value = numbers[i];
                min_index = i;
            }
        }

        // If no more numbers are left in any chunk, stop merging
        if (min_index == -1) {
            break;
        }

        // Write the smallest number to the sorted file
        fprintf(sorted_file, "%d\n", min_value);

        // Read the next number from the selected chunk
        if (fscanf(chunk_files[min_index], "%d", &numbers[min_index]) != 1) {
            // If the chunk is exhausted, close the file
            fclose(chunk_files[min_index]);
            chunk_files[min_index] = NULL;
        }
    }

    fclose(sorted_file);
}

int main() {
    // Step 1: Generate the large file with random numbers
    generate_large_file();
    printf("Generated large random number file.\n");

    // Set the number of threads in the task arena
    const int num_threads = 24;
    boost::asio::thread_pool pool(num_threads);
    
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUMBERS_TO_GENERATE/CHUNK_SIZE; ++i) {
        boost::asio::post(pool, [i](){sort_chunk(i); });
    }

    pool.join(); // Wait for all tasks to complete

    auto end = std::chrono::high_resolution_clock::now();

    // Calculate and print the elapsed time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time passed: " << duration << " milliseconds" << std::endl;

    printf("Sorted all chunks in parallel.\n");

    // Step 4: Merge the sorted chunks into the final sorted file
    merge_sorted_chunks();
    printf("Merged sorted chunks into the final sorted file.\n");

    return 0;
}

