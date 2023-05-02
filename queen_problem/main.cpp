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
        std::unordered_set<Node, Node::HashLexic> unvisited;
        std::unordered_set<Node, Node::HashLexic> visited;
        std::stack<Node> nodes;
        while (nodes.size() < N) {
            bool queen_conflict = true;

            for (auto i = 0; i < N; ++i) {
                auto p = Position{i, static_cast<int>(nodes.size())};
                std::cout << p.x << "," << p.y;
                std::vector<int> values;
                if (!nodes.empty()) {
                    auto parent = nodes.top();
                    values = parent.values;
                }
                values.emplace_back(i);
                std::cout << "- " << values.size() << std::endl;
                if (visited.find(Node{values}) == visited.end() && !queens_in_column(p.x) && !queens_in_row(p.y) &&
                    !queens_in_diagonal(p.x, p.y)) {
                    visited.insert(Node{values});
                    nodes.push(Node{values});
                    board[p.y][p.x] = true;
                    queen_conflict = false;
                    std::cout << nodes.top().values.back() << "," << nodes.size()-1 << std::endl;
                    break;
                }
                visited.insert(Node{values});
            }
            if (nodes.empty()) {
                return {};
            }
            if (queen_conflict) {
                std::cout << "NUKE: " << nodes.top().values.back()  << "," << nodes.size()-1 << std::endl;
                board[nodes.size() - 1][nodes.top().values.back()] = false;
                nodes.pop();
                if (nodes.size() == N - 1) {
                    break;
                }
            }
            for (const auto &r: board) {
                for (auto v: r) {
                    std::cout << (v ? "Q " : "· ");
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        if (nodes.size() == N) {
            return nodes.top().values;
        }
        return {};
    }

    bool queens_in_column(size_t column) const {
        for (auto i = 0; i < N; ++i) {
            if (board[i][column]) {
                return true;
            }
        }
        return false;
    }

    bool queens_in_row(size_t row) const {
        for (auto i = 0; i < N; ++i) {
            if (board[row][i]) {
                return true;
            }
        }
        return false;
    }

    bool queens_in_diagonal(size_t column, size_t row) const {
        {
            const auto min_idx = std::min(column, row);
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
            const auto min_idx = std::min(N - column - 1, row);
            auto c = column + min_idx, r = row - min_idx;
            while (c >= 0 && r < N) {
                if (board[r][c]) {
                    return true;
                }
                c--;
                r++;
            }
        }
        return false;
    }

    checkboard<N> board;
    Graph g;
};


int main() {
    auto problem = QueenGame<90>();
    std::cout << "Hello, World!" << std::endl;
    auto solution = problem.solve(Method::lexicographic_first);
    if (solution.has_value()) {

    }
    return 0;
}
