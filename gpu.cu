#include <iostream>
#include <cuda_runtime.h>
#include <chrono>
#include <cmath>
#include <math.h>


using namespace std;
using namespace chrono;


__device__ double f(double x) {
    return pow(x, 4) - 3 * pow(x, 3) + 2 * pow(x, 2) + x - 5;
}


__global__ void simpson(double* x, int n, double lower_limit, double upper_limit) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        double x0 = lower_limit + i * (upper_limit - lower_limit) / n;
        double x1 = x0 + (upper_limit - lower_limit) / n;
        double h = (x1 - x0) / 2.0;
        double y0 = f(x0);
        double y1 = f(x1);
        if (i == 0 || i == n-1) {
            x[i] = y0 + y1;
        } else if (i % 2 == 0) {
            x[i] = 4.0 * y0 + 2.0 * y1;
        } else {
            x[i] = 2.0 * y0 + y1;
        }
    }
}

int main() {
    int n = 1000000; 
    double lower_limit = 0.0;
    double upper_limit = 10.0; 
    double h = (upper_limit - lower_limit) / n;
    double* x;
    double result = 0.0;
    

    x = new double[n];

    double* d_x;
    cudaMalloc((void**)&d_x, sizeof(double) * n);
    auto start = std::chrono::high_resolution_clock::now();
    
    simpson<<<(n + 255) / 256, 256>>>(d_x, n, lower_limit, upper_limit);

    cudaMemcpy(x, d_x, sizeof(double) * n, cudaMemcpyDeviceToHost);

    for (int i = 0; i < n; i++) {
        result += x[i];
    }
    result *= h / 4.5;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() * 1e-6 << " milliseconds" << std::endl;
    
    std::cout << "The area under the curve from " << lower_limit << " to " << upper_limit << " is: " << result << std::endl;


    delete[] x;
    cudaFree(d_x);

    return 0;
}

