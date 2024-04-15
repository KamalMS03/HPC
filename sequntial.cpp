#include <iostream>
#include <chrono>
#include <cmath>
#include <math.h>

using namespace std;
using namespace chrono;

double function(double x) {
  return (pow(x, 4) - 3 * pow(x, 3) + 2 * pow(x, 2) + x - 5);
}


double simpsonsRule(double a, double b, int n) {
  double h = (b - a) / n; 
  double sum = function(a); 

 
  for (int i = 1; i < n - 1; i += 2) {
    sum += 4 * function(a + i * h);
  }

  for (int i = 2; i < n - 1; i += 2) {
    sum += 2 * function(a + i * h);
  }

  sum += function(b); 

  return h * sum / 3.0; 
}


int main() {
  double lower_bound = 0.0;
  double upper_bound = 10.0;
  int num_intervals = 1000000;
  auto start = std::chrono::high_resolution_clock::now();
  double integral_result = simpsonsRule(lower_bound, upper_bound, num_intervals);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::nano> elapsed = end - start;
  cout << "Integral result: " << integral_result << integral_result <<endl;
  std::cout << "Elapsed time: " << elapsed.count() * 1e-6 << " milliseconds" << std::endl;

  return 0;
}
