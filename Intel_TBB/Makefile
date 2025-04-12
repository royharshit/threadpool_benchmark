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
	./io_workload 1
	./io_workload 4
	./io_workload 8
	./io_workload 15
	@echo "Running matrix_mul:"
	./matrix_mul 1
	./matrix_mul 4
	./matrix_mul 8
	./matrix_mul 15
	@echo "Running os_scheduling:"
	./os_scheduling 1
	./os_scheduling 4
	./os_scheduling 8
	./os_scheduling 15
	@echo "Running thread_overhead:"
	./thread_overhead 1
	./thread_overhead 4
	./thread_overhead 8
	./thread_overhead 15
	@echo "Running mixed_workload:"
	./mixed_workload 1
	./mixed_workload 4
	./mixed_workload 8
	./mixed_workload 15

# Clean up
clean:
	rm -f $(EXECUTABLES)
	rm -f chunk_*
	rm -f file_*
	rm -f large_random_numbers.txt
	rm -f sorted_large_random_numbers.txt
	rm -f output_file.dat

