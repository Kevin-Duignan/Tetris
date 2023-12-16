#pragma once

/*
General class order:
Attributes
Constructor
Methods
Getters / Setters
Destructor
*/

#include "../headers/const.hpp"
#include <cmath>

class Score {
private:
  int total_score;
  const int tick_score;
  const int drop_score;
  const int clear_score;
  const int tetris_score;

public:
  // Constructor
  Score(int tick = static_cast<int>(std::ceil(ROWS * 0.1)), int drop = ROWS,
        int clear = ROWS * 2,
        int tetris = ROWS * 2) // based on rows so that is remains fair if you
                               // change the amount of rows.
      : tick_score(tick), drop_score(drop), clear_score(clear),
        tetris_score(tetris) // sets the private vars to the arguments given.
  {
    total_score = 0;
  }

  // Methods
  void tick() { total_score += tick_score; }
  void drop() { total_score += drop_score; }
  void clear(int cleared) { total_score += clear_score * cleared; }
  void tetris() { total_score += tetris_score; }

  // Getters, setters
  int get_total_score() const { return total_score; }
};