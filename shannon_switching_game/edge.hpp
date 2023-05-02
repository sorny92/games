#pragma once

#include <bits/stdc++.h>

struct Edge {
  size_t node1, node2;

  bool operator==(const Edge &e2) const {
    return ((this->node1 == e2.node1) && (this->node2 == e2.node2)) ||
           ((this->node1 == e2.node2) && (this->node2 == e2.node1));
  }

  bool operator!=(const Edge &e2) const { return !(*this == e2); };

  struct HashFunc {
  public:
    size_t operator()(const Edge &e) const {
      return e.node1 < e.node2 ? e.node1 * 100 + e.node2
                               : e.node2 * 100 + e.node1;
    }
  };
};