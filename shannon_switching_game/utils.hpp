#pragma once
#include <iostream>

class Graph;

namespace console::print {
void unused_nodes(const Graph &g) {
  std::cout << "Unused edges:" << std::endl;
  for (const auto &edge : g.get_unused_edges()) {
    std::cout << edge.node1 << ", " << edge.node2 << std::endl;
  }
}

void endgame(const Graph &g) {
  if (g.is_win_for_color()) {
    std::cout << "Color won!" << std::endl;
  }
  if (g.is_win_for_cut()) {
    std::cout << "Cut won!" << std::endl;
  }
}

} // namespace console::print
