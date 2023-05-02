#include "game.hpp"
#include "player.hpp"

int main(int, char **) {
  { // Play to expect the color player to win
    auto g = Graph();
    g.add_edge(0, 1);
    g.set_special_nodes(0, 1);

    auto game = Game(g, CodePlayer<ColorPlayer>(), CodePlayer<CutPlayer>(),
                     StartPlayer::COLOR);
    auto color_player = game.get_color_player();
    auto cut_player = game.get_cut_player();

    color_player->set_desired_action(0, 1);
    game.execute_turn();

    assert(game.winner() == Winner::COLOR);
  }

  { // Play to expect the cut player to win
    auto g = Graph();
    g.add_edge(0, 1);
    g.set_special_nodes(0, 1);

    auto game = Game(g, CodePlayer<ColorPlayer>(), CodePlayer<CutPlayer>(),
                     StartPlayer::CUT);
    auto color_player = game.get_color_player();
    auto cut_player = game.get_cut_player();

    cut_player->set_desired_action(0, 1);
    game.execute_turn();

    assert(game.winner() == Winner::CUT);
  }
}