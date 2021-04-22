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
  refresh();
  printCar(stdscr, 0);
  getch();
  printCar(stdscr, 1);
  getch();
  printCar(stdscr, 2);
  getch();
  endwin();
  return EXIT_SUCCESS;
}