project(games)
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_subdirectory(queen_problem)
add_subdirectory(shannon_switching_game)