#pragma once

#include "node.hpp"
#include <unordered_set>
#include <vector>

class Graph {
public:
    using node_storage = std::vector<Node>;

    void add_node(Node &dad, const std::vector<int>& value) {
        auto new_node = Node{value};
        m_unused.emplace_back(std::move(new_node));
    };

    Node &get_root() {
        return used[0];
    }


    const node_storage &get_unused_nodes() const { return m_unused; }

private:

    bool transform_edge(node_storage &set_to_insert, const Node &edge) {
        auto iter_edge = std::find(m_unused.begin(), m_unused.end(), edge);
        if (iter_edge != m_unused.end()) {
            m_unused.erase(iter_edge);
//            set_to_insert.insert(edge);
            return true;
        }
        return false;
    }


    node_storage used{Node{{-1}}};
    node_storage m_unused;
};
