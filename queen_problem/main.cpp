#include <iostream>
#include <array>
#include <optional>
#include <functional>
#include <unordered_set>
#include "graph.hpp"

using checkboard = std::vector<std::vector<int>>;
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
    QueenGame(size_t board_size) : N(board_size) {
        auto zeros = std::vector(N, 0);
        board = std::vector(N, zeros);
    }

    std::optional<checkboard> solve(Method method) {
        return dispatcher.at(method)();
    }

private:
    std::unordered_map<Method, std::function<std::optional<checkboard>(void)>> dispatcher{
            {Method::lexicographic_first,    [&] { return lexicographic_first(); }},
            {Method::most_compatible_first,  [&] { return most_compatible_first(); }},
            {Method::least_compatible_first, [&] { return least_compatible_first(); }},
    };

    std::optional<checkboard> lexicographic_first() {
        std::unordered_set<Node, Node::HashLexic> unvisited;
        std::unordered_set<Node, Node::HashLexic> visited;
        std::stack<Node> nodes;
        while (nodes.size() < N) {
            bool queen_conflict = true;

            for (auto i = 0; i < N; ++i) {
                auto p = Position{i, static_cast<int>(nodes.size())};
                std::vector<int> values;
                if (!nodes.empty()) {
                    auto parent = nodes.top();
                    values = parent.values;
                }
                values.emplace_back(i);
                if (visited.find(Node{values}) == visited.end() && !queens_in_column(p.x) && !queens_in_row(p.y) &&
                    !queens_in_diagonal(p.x, p.y)) {
                    visited.insert(Node{values});
                    nodes.push(Node{values});
                    board[p.y][p.x] = 1;
                    queen_conflict = false;
                    break;
                }
                visited.insert(Node{values});
            }
            if (nodes.empty()) {
                return {};
            }
            if (queen_conflict) {
                board[nodes.size() - 1][nodes.top().values.back()] = 0;
                nodes.pop();
                if (nodes.size() == N - 1) {
                    break;
                }
            }
            for (const auto &r: board) {
                for (auto v: r) {
                }
            }
        }
        if (nodes.size() == N) {
            return board;
        }
        return {};
    }

    std::optional<checkboard> most_compatible_first() {
        return board;
    }

    std::optional<checkboard> least_compatible_first() {
        return board;
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
            while (c < N && r < N) {
                if (board[r][c]) {
                    return true;
                }
                c--;
                r++;
            }
        }
        return false;
    }

    size_t N{};
    checkboard board;
    Graph g;
};


int main() {
    auto problem = QueenGame<25>();
    auto board = problem.solve(Method::lexicographic_first);
    if (board.has_value()) {
        for (const auto &r: *board) {
            for (auto v: r) {
                std::cout << (v ? "Q " : "· ");
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
