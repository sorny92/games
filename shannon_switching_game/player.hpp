#pragma once

#include "graph.hpp"

enum class Result { ACTION_OK, ACTION_INVALID };

class PlayerMode {
  virtual Result do_action(Graph &g, const Edge &edge) = 0;

protected:
  const std::string name;
};

class CutPlayer : public PlayerMode {
public:
  Result do_action(Graph &g, const Edge &edge) override {
    return g.cut_edge(edge) ? Result::ACTION_OK : Result::ACTION_INVALID;
  };
  const std::string name = "Cut player";
};

class ColorPlayer : public PlayerMode {
public:
  Result do_action(Graph &g, const Edge &edge) override {
    return g.color_edge(edge) ? Result::ACTION_OK : Result::ACTION_INVALID;
  };
  const std::string name = "Color player";
};

template <typename PlayerType> struct Actionable {
  virtual Result take_action(Graph &g) final {
    std::cout << "I'm " << this->player.name << " and it's my turn"
              << std::endl;
    return internal_action(g);
  };
  virtual Result internal_action(Graph &g) = 0;

protected:
  PlayerType player;
};

template <typename PlayerType>
class CodePlayer : public Actionable<PlayerType> {
public:
  void set_desired_action(size_t node1, size_t node2) {
    m_node1 = node1;
    m_node2 = node2;
  }

  Result internal_action(Graph &g) override {
    return this->player.do_action(g, {m_node1, m_node2});
  };

private:
  size_t m_node1{0}, m_node2{0};
};

template <typename PlayerType>
class ConsolePlayer : public Actionable<PlayerType> {
public:
  Result internal_action(Graph &g) override {
    size_t node1{0}, node2{0};
    char comma;
    std::cin >> node1 >> comma >> node2;
    if (node1 == node2) {
      return Result::ACTION_INVALID;
    }
    return this->player.do_action(g, {node1, node2});
  };
};

template <typename PlayerType>
class RandomPlayer : public Actionable<PlayerType> {
public:
  Result internal_action(Graph &g) override {
    const auto &nodes = g.get_unused_edges();
    auto out = std::vector<Edge>();
    std::sample(nodes.begin(), nodes.end(), std::back_inserter(out), 1,
                std::mt19937{std::random_device{}()});

    return this->player.do_action(g, out[0]);
  };
};