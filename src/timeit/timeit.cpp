#include "timeit.hpp"

#include <iostream>

void timeit(std::function<void()> function, std::string function_name) {
    auto start = std::chrono::high_resolution_clock::now();
    function();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << function_name << " took: " << duration.count()/(1e6) << " seconds" << std::endl;
}
