#include <iostream>
#include "solvers.h"

std::unordered_map<Method, std::string> translations{
        {Method::lexicographic_first,    "lexicographic_first"},
        {Method::most_compatible_first,  "most_compatible_first"},
        {Method::least_compatible_first, "least_compatible_first"},
};




int main() {
    std::vector<int> game_sizes = {7};
    //std::vector<int> game_sizes = {4, 7, 8, 10, 11, 13, 15, 16, 18, 19, 21, 23, 25};
    //std::vector<int> game_sizes = {4, 7, 8, 10, 11, 13, 15, 16, 18, 19, 21, 22, 23, 25};
    //std::vector<Method> methods = {Method::lexicographic_first, Method::most_compatible_first,
    //                               Method::least_compatible_first};
    std::vector<Method> methods = {Method::most_compatible_first};
    for (const auto size: game_sizes) {
        const auto reps = 1;
        for (auto method: methods) {
            auto accum = 0.0f;
            for (auto i = 0; i < reps; ++i) {
                auto start = std::chrono::high_resolution_clock::now();
                auto problem = QueenGame(size);

                auto board = problem.solve(method);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                accum += duration.count();
            }
            std::cout << translations[method] << " SOLVING FOR " << size << ". AVG time ms: " << (accum / reps) / 1000 << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
