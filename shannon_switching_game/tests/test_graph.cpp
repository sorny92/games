#include "graph.hpp"

int main(int, char **) {
  { // Test coloring the connecting edge between specials wins for color
    auto g = Graph();

    g.add_edge(0, 1);
    g.set_special_nodes(0, 1);

    assert(!g.is_win_for_color());
    assert(!g.is_win_for_cut());

    g.color_edge({0, 1});

    assert(g.is_win_for_color());
    assert(!g.is_win_for_cut());
  }

  { // Test non connected special nodes wins for cut
    auto g = Graph();

    g.add_edge(0, 1);
    g.add_edge(3, 2);
    g.set_special_nodes(0, 3);

    assert(!g.is_win_for_color());
    assert(g.is_win_for_cut());
  }

  { // Test cutting an edge between specials nodes wins for cut
    auto g = Graph();

    g.add_edge(0, 1);
    g.add_edge(2, 1);
    g.set_special_nodes(0, 2);

    assert(!g.is_win_for_color());
    assert(!g.is_win_for_cut());

    g.cut_edge({0, 1});

    assert(!g.is_win_for_color());
    assert(g.is_win_for_cut());
  }

  { // Test coloring cut edges as invalid
    auto g = Graph();

    g.add_edge(0, 1);
    g.set_special_nodes(0, 1);

    g.cut_edge({0, 1});
    assert(!g.color_edge({0, 1}));

    assert(!g.is_win_for_color());
    assert(g.is_win_for_cut());
  }

  { // Test cut colored edges as invalid
    auto g = Graph();

    g.add_edge(0, 1);
    g.set_special_nodes(0, 1);

    g.color_edge({0, 1});
    assert(!g.cut_edge({0, 1}));

    assert(g.is_win_for_color());
    assert(!g.is_win_for_cut());
  }
}