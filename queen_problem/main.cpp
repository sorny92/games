#include <iostream>
#include <array>
#include <optional>

template<size_t N>
using checkboard = std::array<std::array<bool, N>, N>;

template<size_t N>
class QueenGame {
public:
    enum class Method {
        lexicographic_first,
        most_compatible_first,
        least_compatible_first
    };

    std::optional<checkboard<N>> solve(Method method){
        auto n_queens{N};
    }

private:
    bool queens_in_column() const {
        for (auto i = 0; i < N; ++i) {
            int queens_count{0};
            for (auto j = 0; j < N; ++j) {
                if (board[j][i]) {
                    queens_count++;
                }
                if (queens_count > 1) {
                    return true;
                }
            }
        }
        return false;
    }

    bool queens_in_row() const {
        for (auto i = 0; i < N; ++i) {
            int queens_count{0};
            for (auto j = 0; j < N; ++j) {
                if (board[i][j]) {
                    queens_count++;
                }
                if (queens_count > 1) {
                    return true;
                }
            }
        }
        return false;
    }

    bool queens_in_diagonal() const {
        for (auto i = 0; i < N; ++i) {
            int queens_count{0};
            for (auto j = i; j < N; ++j, ++i) {
                if (board[i][j]) {
                    queens_count++;
                }
                if (queens_count > 1) {
                    return true;
                }
            }
        }
        for (auto i = 0; i < N; ++i) {
            for (auto j = i; j < N; ++j, ++i) {
                int queens_count{0};
                if (board[j][i]) {
                    queens_count++;
                }
                if (queens_count > 1) {
                    return true;
                }
            }
        }
        return false;
    }

    checkboard<N> board;
};


int main() {
    auto problem = QueenGame<3>();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
