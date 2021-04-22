//
// Created by Nick Vazquez on 4/18/21.
//
#include "symbols.h"
#include "GUI.h"

#include <ncurses.h>
#include <stdlib.h>

#define NUM_LANES 3

int main(void) {
  startWindow();
  int i = titleScreen();
  printLanes(stdscr);
  endwin();
  return EXIT_SUCCESS;
}