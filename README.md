# Team Members:
  Harsh Kumar - 21011101047
  
  Kamalnath M S - 21011101056

# Problem Statement
Develop a parallel implementation of Simpson's rule to achieve significant speedup in computation time.

# Parallelzation of Numerical Integration

| No. of Process(sub intervals)  | Time taken for Sequential Compution(ms) | Time taken for parallel(GPU) Compution(ms)|
| ------------------------------ | --------------------------------------- | ------------------------------------------|
| 1                              | 0.0192216                               | 0.055009                                  |
| 100                            | 0.0491                                  | 0.0581                                    |
| 1000                           | 0.2125                                  | 0.0943                                    |
| 10000                          | 1.8896                                  | 0.28119                                   |
| 100000                         | 6.60008                                 | 2.19155                                   |
| 1000000                        | 47.008                                  | 20.524                                    |


### To run sequntial.cpp code

  ```bash
  g++ sequntial.cpp -o seq
  ./seq
  ```

### To run gpu.cu code

```bash
sudo apt install nvidia-cuda-toolkit
nvcc gpu.cu -o gpu1 -lcuda -lcudart -std=c++11
./gpu1
```
