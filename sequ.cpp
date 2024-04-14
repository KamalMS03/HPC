#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

double function(double x) {
  return (x*x); // Example: Integrate x^2
}

double simpsonsRecursive(double a, double b, int n, double prevSum = 0.0) {
  if (n == 1) {
    return prevSum + function(a) + function(b);
  }

  double h = (b - a) / n;
  double mid = a + h / 2.0;

  double oddSum = 0.0;
  for (int i = 1; i < n - 1; i += 2) {
    oddSum += function(a + i * h);
  }

  double recursiveSum = simpsonsRecursive(a, mid, n / 2, prevSum + 4.0 * oddSum + function(mid));
  return recursiveSum + function(b);
}

double simpsonsRule(double a, double b, int n) {
  double h = (b - a) / n; // Interval width
  double sum = function(a); // Function value at lower bound

  // Even terms (except first and last)
  for (int i = 1; i < n - 1; i += 2) {
    sum += 4 * function(a + i * h);
  }

  // Odd terms
  for (int i = 2; i < n - 1; i += 2) {
    sum += 2 * function(a + i * h);
  }

  sum += function(b); // Function value at upper bound

  return h * sum / 3.0; // Final integration result
}

// Replace this function with your actual function to integrate

int main() {
  double lower_bound = 0.0;
  double upper_bound = 10.0;
  int num_intervals = 10000; // Number of intervals (adjust for accuracy)
  auto start = std::chrono::high_resolution_clock::now();
  double integral_result = simpsonsRule(lower_bound, upper_bound, num_intervals);
 // double integral_result1 = simpsonsRecursive(lower_bound, upper_bound, num_intervals);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::nano> elapsed = end - start;
  cout << "Integral result: " << integral_result << integral_result <<endl;
  std::cout << "Elapsed time: " << elapsed.count() * 1e-6 << " milliseconds" << std::endl;

  return 0;
}
