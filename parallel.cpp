#include <iostream>
#include <vector>
#include <thread>

#include <chrono>
#include <cmath>


using namespace std;
using namespace chrono;

// Function to be integrated
double f(double x) {
  return x * x;
}

// Simpson's rule for a single subinterval
double integrate_subinterval(double a, double b) {
  double h = (b - a) / 2.0;
  return (h / 3.0) * (f(a) + 4.0 * f((a + b) / 2.0) + f(b));
}

// Worker function for parallel integration
void integrate_parallel(double a, double b, int num_threads, double* result, int thread_id) {
  double step = (b - a) / num_threads;
  double local_a = a + thread_id * step;
  double local_b = local_a + step;
  result[thread_id] = integrate_subinterval(local_a, local_b);
}

// Main function for parallel integration with load balancing
double integrate_simpson_parallel(double a, double b, int num_threads) {
  // Check for invalid number of threads
  if (num_threads <= 0) {
    std::cerr << "Error: Number of threads must be positive." << std::endl;
    return -1.0;
  }

  // Allocate result array
  std::vector<double> partial_results(num_threads);

  // Spawn threads and integrate subintervals
  std::vector<std::thread> threads(num_threads);
  for (int i = 0; i < num_threads; ++i) {
    threads[i] = std::thread(integrate_parallel, a, b, num_threads, partial_results.data(), i);
  }

  // Wait for threads to finish
  for (auto& thread : threads) {
    thread.join();
  }

  // Combine partial results
  double final_result = 0.0;
  for (double value : partial_results) {
    final_result += value;
  }

  return final_result;
}

int main() {
  double a = 0.0;
  double b = 1.0;
  int num_threads = 10000;
  
  auto start = std::chrono::high_resolution_clock::now();
  double result = integrate_simpson_parallel(a, b, num_threads);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::nano> elapsed = end - start;

  std::cout << "Parallel integration result: " << result << std::endl;
  std::cout << "Elapsed time: " << elapsed.count() * 1e-6 << " milliseconds" << std::endl;
  return 0;
}
