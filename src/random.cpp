#include "../headers/random.h"
#include "../headers/tetromino.h"
#include <iostream>
#include <random>

void choose_random(std::array<TetrominoVariant, 7> pieces) {
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(1, pieces.size());

  std::cout << distrib(gen);
}
