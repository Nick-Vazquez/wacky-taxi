//
// Created by Nick Vazquez on 4/18/21.
//

#include "WackyHighScore.h"

int main() {
  add_HighScore("scores.txt", "Nick", 13);
  add_HighScore("scores.txt", "Jongmin", 14);
  add_HighScore("scores.txt", "John", 15);
  add_HighScore("scores.txt", "Dave", 12);

  HighScore* highScores = get_HighScores("scores.txt");
  for (int i = 0; i < NUM_SCORES; i++) {
    printHighScore((highScores + i));
  }
}