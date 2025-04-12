# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11
LDLIBS = -ltbb

# Source files and corresponding executables
SOURCES = io_workload.cpp matrix_mul.cpp os_scheduling.cpp thread_overhead.cpp mixed_workload.cpp
EXECUTABLES = io_workload matrix_mul os_scheduling thread_overhead mixed_workload

# Default target
all: $(EXECUTABLES)

io_workload: io_workload.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

matrix_mul: matrix_mul.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

os_scheduling: os_scheduling.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

thread_overhead: thread_overhead.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

mixed_workload: mixed_workload.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

# Run all executables sequentially
run: all
	@echo "Running io_workload:"
	./io_workload 1;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./io_workload 4;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./io_workload 8;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./io_workload 15;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	@echo "Running matrix_mul:"
	./matrix_mul 1;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./matrix_mul 4;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./matrix_mul 8;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./matrix_mul 15;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	@echo "Running os_scheduling:"
	./os_scheduling 1;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./os_scheduling 4;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./os_scheduling 8;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./os_scheduling 15;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	@echo "Running thread_overhead:"
	./thread_overhead 1;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./thread_overhead 4;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./thread_overhead 8;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./thread_overhead 15;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	@echo "Running mixed_workload:"
	./mixed_workload 1;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./mixed_workload 4;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./mixed_workload 8;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat
	./mixed_workload 15;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat

# Clean up
clean:
	rm -f $(EXECUTABLES)
	rm -f chunk_*
	rm -f file_*
	rm -f large_random_numbers.txt
	rm -f sorted_large_random_numbers.txt
	rm -f output_file.dat

