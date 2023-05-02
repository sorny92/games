#include <cstdlib>

#include "game.hpp"
#include "graph.hpp"
#include "graph_parser.hpp"
#include "player.hpp"
#include "utils.hpp"

int main() {
  srand(time(NULL));

  auto g = parse_graph_file("../shannon_switching_game/graphs/simple_game.txt");

  auto color_player = ConsolePlayer<ColorPlayer>();
  auto cut_player = RandomPlayer<CutPlayer>();

  auto game = Game(g, color_player, cut_player);

  while (game.winner() == Winner::NOT_FINISHED) {
    console::print::unused_nodes(g);
    auto result = game.execute_turn();
    if (result == Result::ACTION_OK) {
      std::cout << "Accepted move!" << std::endl;
    } else {
      std::cout << "The move was invalid! Try Again!" << std::endl;
    }
  }
  console::print::endgame(g);
  return 0;
}
