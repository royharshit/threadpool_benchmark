# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20

# Source files and corresponding executables
SOURCES = io_workload.cpp matrix_mul.cpp os_scheduling.cpp thread_overhead.cpp mixed_workload.cpp
EXECUTABLES = io_workload matrix_mul os_scheduling thread_overhead mixed_workload

# Default target
all: $(EXECUTABLES)

io_workload: io_workload.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

matrix_mul: matrix_mul.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

os_scheduling: os_scheduling.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

thread_overhead: thread_overhead.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

mixed_workload: mixed_workload.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Run all executables sequentially
run: all
	@echo "Running io_workload:"
	./io_workload 6
	@echo "Running matrix_mul:"
	./matrix_mul 6
	@echo "Running os_scheduling:"
	./os_scheduling 6
	@echo "Running thread_overhead:"
	./thread_overhead 6
	@echo "Running mixed_workload:"
	./mixed_workload 6

# Clean up
clean:
	rm -f $(EXECUTABLES)

