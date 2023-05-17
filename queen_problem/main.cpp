#include <iostream>
#include "solvers.h"

std::unordered_map<Method, std::string> translations{
        {Method::lexicographic_first,    "lexicographic_first"},
        {Method::most_compatible_first,  "most_compatible_first"},
        {Method::least_compatible_first, "least_compatible_first"},
};


int main() {
    std::vector<Method> methods = {Method::lexicographic_first, Method::most_compatible_first,
                                   Method::least_compatible_first};
    for (auto size = 4; size <= 21; ++size) {
        const auto reps = 5;
        for (auto method: methods) {
            auto accum = 0.0f;
            for (auto i = 0; i < reps; ++i) {
                auto start = std::chrono::high_resolution_clock::now();
                auto problem = QueenGame(size);

                auto board = problem.solve(method);
                //problem.print_board();
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                accum += duration.count();
            }
            std::cout << translations[method] << " \twith " << size << " queens.\tAVG time ms: "
                      << (accum / reps) / 1000 << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
