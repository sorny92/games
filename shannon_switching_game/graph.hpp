#pragma once

#include "edge.hpp"
#include <unordered_set>
#include <vector>

class Graph {
public:
  using edge_storage = std::unordered_set<Edge, Edge::HashFunc>;
  void add_edge(size_t begin, size_t end) { m_unused.insert({begin, end}); }
  void set_special_nodes(size_t special_node_1, size_t special_node_2) {
    m_special_nodes = std::make_pair(special_node_1, special_node_2);
  };

  const edge_storage &get_unused_edges() const { return m_unused; }

  bool color_edge(const Edge &edge) { return transform_edge(m_colored, edge); }

  bool cut_edge(const Edge &edge) { return transform_edge(m_cut, edge); }

  bool is_win_for_color() const { return are_special_nodes_connected(); }
  bool is_win_for_cut() const { return !can_special_nodes_be_connected(); }

private:
  bool are_special_nodes_connected() const {
    // Perform DFS to check if the special nodes are connected
    std::unordered_set<size_t> visited;
    dfs(m_special_nodes.first, visited, m_colored);
    if (visited.find(m_special_nodes.second) != visited.end()) {
      return true;
    }
    return false;
  }

  bool can_special_nodes_be_connected() const {
    // Perform DFS to check if the special nodes are connected
    std::unordered_set<size_t> visited;
    edge_storage non_cut_edges;
    std::for_each(m_colored.begin(), m_colored.end(),
                  [&](const auto &edge) { non_cut_edges.insert(edge); });
    std::for_each(m_unused.begin(), m_unused.end(),
                  [&](const auto &edge) { non_cut_edges.insert(edge); });
    dfs(m_special_nodes.first, visited, non_cut_edges);
    if (visited.find(m_special_nodes.second) != visited.end()) {
      return true;
    }
    return false;
  }

  void dfs(size_t node, std::unordered_set<size_t> &visited,
           const edge_storage &nodes_to_visit) const {
    visited.insert(node);
    for (const auto &edge : nodes_to_visit) {
      if (edge.node1 == node && visited.find(edge.node2) == visited.end()) {
        dfs(edge.node2, visited, nodes_to_visit);
      }
      if (edge.node2 == node && visited.find(edge.node1) == visited.end()) {
        dfs(edge.node1, visited, nodes_to_visit);
      }
    }
  }

  bool transform_edge(edge_storage &set_to_insert, const Edge &edge) {
    auto iter_edge = std::find(m_unused.begin(), m_unused.end(), edge);
    if (iter_edge != m_unused.end()) {
      m_unused.erase(iter_edge);
      set_to_insert.insert(edge);
      return true;
    }
    return false;
  }

  edge_storage m_unused;
  edge_storage m_colored;
  edge_storage m_cut;
  std::pair<size_t, size_t> m_special_nodes;
};
