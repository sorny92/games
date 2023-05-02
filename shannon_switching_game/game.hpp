#pragma once
#include "player.hpp"

namespace {
enum class Winner { CUT, COLOR, NOT_FINISHED };
enum class StartPlayer { CUT, COLOR, RANDOM };

template <typename PlayerType1, typename PlayerType2> class Game {
public:
  Game(Graph &graph, const PlayerType1 &color_player,
       const PlayerType2 &cut_player,
       StartPlayer start_player = StartPlayer::RANDOM)
      : m_color_player(std::make_shared<PlayerType1>(color_player)),
        m_cut_player(std::make_shared<PlayerType2>(cut_player)),
        m_graph(graph) {
    switch (start_player) {
    case StartPlayer::CUT:
      plays_color = false;
      break;
    case StartPlayer::COLOR:
      plays_color = true;
      break;
    case StartPlayer::RANDOM:
      plays_color = (rand() % 100) >= 50;
    }
  }

  Result execute_turn() {
    auto result = Result::ACTION_INVALID;
    if (plays_color) {
      result = m_color_player->take_action(m_graph);
    } else {
      result = m_cut_player->take_action(m_graph);
    }
    if (result == Result::ACTION_OK) {
      plays_color = !plays_color;
    } else {
    }
    return result;
  }

  std::shared_ptr<PlayerType1> get_color_player() { return m_color_player; }

  std::shared_ptr<PlayerType2> get_cut_player() { return m_cut_player; }

  Winner winner() const {
    if (m_graph.is_win_for_cut()) {
      return Winner::CUT;
    }
    if (m_graph.is_win_for_color()) {
      return Winner::COLOR;
    }
    return Winner::NOT_FINISHED;
  }

private:
  std::shared_ptr<PlayerType1> m_color_player;
  std::shared_ptr<PlayerType2> m_cut_player;
  Graph &m_graph;
  bool plays_color{};
};
} // namespace
