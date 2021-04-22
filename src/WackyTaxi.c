//
// Created by Nick Vazquez on 4/18/21.
//
#include "symbols.h"
#include "GUI.h"

#include <ncurses.h>
#include <stdlib.h>

#define NUM_LANES 4

int main(void) {
  int userSelection, userChar;
  int lane = NUM_LANES / 2;
  startWindow();
  userSelection = titleScreen();
  if (userSelection == 0) {
    printLanes(stdscr);
    refresh();
    printCar(stdscr, lane);
    userChar = wgetch(stdscr);
    while (userChar == 'a' || userChar == 'd') {
      if (userChar == 'a' && lane > 0) {
        lane--;
      }
      else if (userChar == 'd' && lane < NUM_LANES - 1){
        lane++;
      }
      printCar(stdscr, lane);
      userChar = wgetch(stdscr);
      refresh();
    }
  }
  else if (userSelection == 1) {

  }
  else {
    exit(1);
  }

  endwin();
  return EXIT_SUCCESS;
}