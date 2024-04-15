#include <iostream>
#include <vector>
#include <numeric>
#include <omp.h>
#include <chrono>
using namespace std;
using namespace chrono;

double f(double x) {

    return (pow(x, 4) - 3 * pow(x, 3) + 2 * pow(x, 2) + x - 5);
}

double simpson_rule(double a, double b, int n) {
    vector<double> x(n+1);
    vector<double> y(n+1);

    #pragma omp parallel for
    for (int i = 0; i <= n; i++) {
        x[i] = a + i*(b-a)/n;
        y[i] = f(x[i]);
    }

    double result = 0;
    if (n > 1) {
        double h = (b-a)/n;
        result = y[0] + y[n] + 4*accumulate(y.begin()+1, y.begin()+n/2+1, 0.0, [h](double sum, double y_i) { return sum + y_i; }) + 2*accumulate(y.begin()+n/2+1, y.end()-1, 0.0, [h](double sum, double y_i) { return sum + y_i; }) + 4*accumulate(y.begin()+1, y.end()-1, 0.0, [h](double sum, double y_i) { return sum + y_i; });
        result = result*h/3;
    }

    return result;
}

int main() {
    int n = 10000; 
    double a = 0.0; 
    double b = 10.0; 
    auto start = std::chrono::high_resolution_clock::now();
    double result = simpson_rule(a, b, n);
    auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::nano> elapsed = end - start;
    cout << "The result of the Simpson's rule calculation is: " << result << endl;
     std::cout << "Elapsed time: " << elapsed.count() * 1e-6 << " milliseconds" << std::endl;
    return 0;
}
