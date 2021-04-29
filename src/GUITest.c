//
// Created by Nick Vazquez on 4/28/21.
//

#include "GUI.h"
#include "symbols.h"
#include <time.h>

#define NUM_LANES 3
#define NUM_ROWS  3

int main() {
  GameBoard*  board;
  Object*     newLine;
  srand(time(NULL));

  startWindow();
  printLanes(stdscr);
  refresh();
  getch();
  endwin();
}