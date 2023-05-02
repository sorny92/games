#include "edge.hpp"

int main(int, char **) {
  auto e = Edge({1, 1});
  assert(e == e);

  auto e1 = Edge({1, 1});
  assert(e == e1);

  auto e2 = Edge({1, 3});
  assert(e != e2);

  auto e3 = Edge({3, 1});
  assert(e3 == e2);
}