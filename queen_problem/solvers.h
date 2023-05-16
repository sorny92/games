//
// Created by esteve on 16/05/23.
//
#include <vector>
#include <optional>
#include <unordered_set>
#include "node.hpp"

#pragma once

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

class QueenGame {
public:
    QueenGame(size_t board_size) : N(board_size) {
        auto zeros = std::vector(N, 0);
        board = std::vector(N, zeros);
    }

    std::optional<checkboard> solve(Method method) {
        return dispatcher.at(method)();
    }

    void print_board() {
        for (const auto &r: board) {
            for (auto v: r) {
                std::cout << (v ? "Q " : "· ");
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

private:
    std::unordered_map<Method, std::function<std::optional<checkboard>(void)>> dispatcher{
            {Method::lexicographic_first,    [&] { return lexicographic_first(); }},
            {Method::most_compatible_first,  [&] { return most_compatible_first(); }},
            {Method::least_compatible_first, [&] { return least_compatible_first(); }},
    };

    std::optional<checkboard> lexicographic_first() {
        while (nodes.size() < N) {
            auto idx = nodes.size();

            bool queen_conflict = add_node(visited, nodes, idx);
            if (nodes.empty()) {
                return {};
            }
            if (queen_conflict) {
                board[nodes.top().values.back().first][nodes.top().values.back().second] = 0;
                nodes.pop();
                if (nodes.size() == N - 1) {
                    break;
                }
            }
        }
        if (nodes.size() == N) {
            return board;
        }
        return {};
    }

    std::optional<checkboard> most_compatible_first() {
        while (nodes.size() < N) {
            auto conflicts = get_row_conflicts(nodes);
            auto it = std::min_element(conflicts.begin(), conflicts.end());
            for (auto c: conflicts) {
            }

            auto idx = it->first;
            bool queen_conflict = add_node(visited, nodes, idx);
            if (nodes.empty()) {
                return {};
            }
            if (queen_conflict) {
                board[nodes.top().values.back().first][nodes.top().values.back().second] = 0;
                nodes.pop();
                if (nodes.size() == N - 1) {
                    break;
                }
            }
        }
        if (nodes.size() == N) {
            return board;
        }
        return {};
    }

    std::optional<checkboard> least_compatible_first() {
        while (nodes.size() < N) {
            auto conflicts = get_row_conflicts(nodes);
            auto it = std::max_element(conflicts.begin(), conflicts.end());

            for (auto c: conflicts) {
            }

            auto idx = it->first;

            bool queen_conflict = add_node(visited, nodes, idx);
            if (nodes.empty()) {
                return {};
            }
            if (queen_conflict) {
                board[nodes.top().values.back().first][nodes.top().values.back().second] = 0;
                nodes.pop();
                if (nodes.size() == N - 1) {
                    break;
                }
            }
        }
        if (nodes.size() == N) {
            return board;
        }
        return {};
    }

    std::unordered_map<int, int> get_row_conflicts(std::stack<Node> &nodes) const {
        std::unordered_map<int, int> conflicts;
        for (auto j = 0; j < N; ++j) {
            conflicts.try_emplace(j, 0);
            if (nodes.empty()) {
                break;
            }
            auto values = nodes.top().values;
            auto in_nodes = false;
            for (const auto &v: values) {
                if (v.first == j) {
                    conflicts.erase(j);
                    in_nodes = true;
                    break;
                }
            }
            if (in_nodes) {
                continue;
            }
            for (auto i = 0; i < N; ++i) {
                auto p = Position{i, j};
                if (queens_in_column(p.x) || queens_in_row(p.y) ||
                    queens_in_diagonal(p.x, p.y)) {
                    conflicts[j] += 1;
                }
            }
        }
        return conflicts;
    }

    bool add_node(std::unordered_set<Node, Node::HashLexic> &visited, std::stack<Node> &nodes, unsigned long idx) {
        bool queen_conflict;
        for (auto i = 0; i < N; ++i) {
            auto p = Position{i, static_cast<int>(idx)};
            std::vector<std::pair<int, int>> values;
            if (!nodes.empty()) {
                auto parent = nodes.top();
                values = parent.values;
            }
            values.emplace_back(idx, i);
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
        return queen_conflict;
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

    std::unordered_set<Node, Node::HashLexic> visited;
    std::stack<Node> nodes;
};