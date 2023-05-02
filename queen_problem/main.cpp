#include <iostream>
#include <array>
#include <optional>
#include <functional>
#include <unordered_set>
#include "graph.hpp"

template<size_t N>
using checkboard = std::array<std::array<bool, N>, N>;
struct Position {
    int x;
    int y;
};

enum class Method {
    lexicographic_first,
    most_compatible_first,
    least_compatible_first
};

template<size_t N>
class QueenGame {
public:

    std::optional<std::vector<int>> solve(Method method) {
        return lexicographic_first();
    }

private:
    std::unordered_map<Method, std::function<std::optional<checkboard<N>>(void)>> dispatcher;

    std::optional<std::vector<int>> lexicographic_first() {
        std::stack<Node> nodes;
        std::optional<Node> last_removed_node;
        while (nodes.size() < N) {
            bool queen_located = true;

            for (auto i = 0; i < N; ++i) {
                auto p = Position{i, static_cast<int>(nodes.size())};
                if (!queens_in_column(p.x) && !queens_in_diagonal(p.x, p.y) && !queens_in_row(p.y)) {
                    std::vector<int> values;
                    if (!nodes.empty()) {
                        auto parent = nodes.top();
                        values = parent.values;
                    }
                    values.emplace_back(i);
                    nodes.push(Node{values});
                    board[values.size() - 1][values.back()] = true;
                    queen_located = false;
                    std::cout << nodes.top().values.back() << std::endl;
                    break;
                }
            }
            if (queen_located) {
                auto values = nodes.top().values;
                board[values.size() - 1][values.back()] = false;
                last_removed_node = nodes.top();
                nodes.pop();
                auto &parent = nodes.top();
                parent.values.back() += 1;
                if (parent.values.back() == N) {
                    break;
                }
            }
            for (const auto &r: board) {
                for (auto v: r) {
                    std::cout << (v ? "Q " : "X ");
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }
        if (nodes.size() == N) {
            return nodes.top().values;
        }
        return {};
    }

    bool queens_in_column(size_t column) const {
        for (auto j = 0; j < N; ++j) {
            if (board[j][column]) {
                return true;
            }
        }
        return false;
    }

    bool queens_in_row(size_t row) const {
        for (auto j = 0; j < N; ++j) {
            if (board[row][j]) {
                return true;
            }
        }
        return false;
    }

    bool queens_in_diagonal(size_t column, size_t row) const {
        const auto min_idx = std::min(column, row);
        {
            auto c = column - min_idx, r = row - min_idx;
            while (c < N && r < N) {
                if (board[r][c]) {
                    return true;
                }
                c++;
                r++;
            }
        }
        {
            auto c = column + min_idx, r = row - min_idx;
            while (c < N && r < N) {
                if (board[r][c]) {
                    return true;
                }
                c++;
                r--;
            }
        }
        return false;
    }

    checkboard<N> board;
    Graph g;
};


int main() {
    auto problem = QueenGame<4>();
    std::cout << "Hello, World!" << std::endl;
    auto solution = problem.solve(Method::lexicographic_first);
    if (solution.has_value()) {

    }
    return 0;
}
