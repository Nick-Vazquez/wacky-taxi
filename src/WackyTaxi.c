//
// Created by Nick Vazquez on 4/18/21.
//
#include "symbols.h"
#include "GUI.h"

#include <ncurses.h>
#include <stdlib.h>

int main(void) {
  startWindow();
  int i = titleScreen();
  printw("%d", i);
  getch();
  endwin();
  return EXIT_SUCCESS;
}