add_library(edge edge.hpp)
set_target_properties(edge PROPERTIES LINKER_LANGUAGE CXX)

add_library(graph graph.hpp)
set_target_properties(graph PROPERTIES LINKER_LANGUAGE CXX)

add_library(player player.hpp)
set_target_properties(player PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(player graph)

add_library(graph_parser graph_parser.hpp)
set_target_properties(graph_parser PROPERTIES LINKER_LANGUAGE CXX)

add_library(game game.hpp)
set_target_properties(game PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(game player)

add_executable(shannon_switching_game
        main.cpp
        utils.hpp
        )

ENABLE_TESTING()
add_subdirectory(tests)