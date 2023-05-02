#pragma once

#include "graph.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

Graph parse_graph_file(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Could not open file " + filename);
  }

  size_t num_nodes = 0;
  std::pair<size_t, size_t> special_nodes;
  Graph graph;

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    char type;
    iss >> type;
    if (type == 'N') {
      std::getline(file, line);
      iss.str(line);
      iss >> num_nodes;
      continue;
    } else if (type == 'S') {
      std::getline(file, line);
      iss.str(line);
      size_t node1, node2;
      iss >> node1 >> node2;
      graph.set_special_nodes(node1, node2);
      continue;
    } else if (type == 'E') {
      while (std::getline(file, line)) {
        iss.str(line);
        size_t node1, node2;
        char comma;
        iss >> node1 >> comma >> node2;
        graph.add_edge(node1, node2);
      }

    }
  }

  if (num_nodes == 0) {
    throw std::runtime_error("Missing number of nodes in file " + filename);
  }
  return graph;
}