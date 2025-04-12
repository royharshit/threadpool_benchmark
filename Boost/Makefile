# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11
LDLIBS = -lboost_system -lboost_thread

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
	./io_workload 1;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./io_workload 4;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./io_workload 8;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./io_workload 16;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./io_workload 32;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./io_workload 64;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	@echo "Running matrix_mul:"
	./matrix_mul 1;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./matrix_mul 4;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./matrix_mul 8;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./matrix_mul 16;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./matrix_mul 32;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./matrix_mul 64;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	@echo "Running os_scheduling:"
	./os_scheduling 1;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./os_scheduling 4;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./os_scheduling 8;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./os_scheduling 16;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./os_scheduling 32;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./os_scheduling 64;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	@echo "Running thread_overhead:"
	./thread_overhead 1;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./thread_overhead 4;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./thread_overhead 8;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./thread_overhead 16;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./thread_overhead 32;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./thread_overhead 64;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	@echo "Running mixed_workload:"
	./mixed_workload 1;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./mixed_workload 4;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./mixed_workload 8;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./mixed_workload 16;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./mixed_workload 32;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*
	./mixed_workload 64;rm -f chunk_*;rm -f file_*;rm -f large_random_numbers.txt;rm -f sorted_large_random_numbers.txt;rm -f output_file.dat;rm -f test*

# Clean up
clean:
	rm -f $(EXECUTABLES)
	rm -f chunk_*
	rm -f file_*
	rm -f large_random_numbers.txt
	rm -f sorted_large_random_numbers.txt
	rm -f output_file.dat
	rm -f test*

