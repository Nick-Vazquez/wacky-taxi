//
// Created by Nick Vazquez on 4/18/21.
//
#include "symbols.h"
#include "GUI.h"

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define NUM_LANES 3
#define NUM_ROWS  4

void startGame();
int showScores();

int main(void) {
  int userChoice;
  srand(time(NULL));

  startWindow();
  userChoice = titleScreen();
  // Start game
  if (userChoice == 0) startGame();
  // Show scores
  else if (userChoice == 1) {
    userChoice = showScores();
    if (userChoice == 1) {
      startGame();
    }
  }
  endwin();
  return EXIT_SUCCESS;
}

void startGame() {
  int         userChar;
  int         lane;
  GameBoard*  gameBoard;
  Object*     newLine;
  WINDOW**    boardSprites;
  bool        ran;

  lane        = NUM_LANES / 2;
  gameBoard   = generateBoard(NUM_ROWS, NUM_LANES);
  ran         = false;

  refresh();
  printBoardToScreen(gameBoard, stdscr);
  refresh();

  userChar = wgetch(stdscr);
  while (userChar != 'q') {
    if (userChar == KEY_LEFT && lane > 0) {
      lane--;
    }
    else if (userChar == KEY_RIGHT && lane < NUM_LANES - 1){
      lane++;
    }

    if (ran) {
      clearSprites(boardSprites, gameBoard->boardColumns * gameBoard->boardRows);
    }

    setCarLane(gameBoard, lane);
    newLine       = generateNewLine(NUM_LANES, true);
    advanceBoard(gameBoard, newLine);
    boardSprites  = printBoardToScreen(gameBoard, stdscr);
    wrefresh(stdscr);

    userChar  = wgetch(stdscr);
    ran       = true;
  }
}

int showScores(WINDOW* screen) {
  int userChar;
  HighScore *scores = get_HighScores("scores.txt");
  refresh();
  WINDOW* scoresWindow = printHighScores(scores);
  userChar = wgetch(stdscr);
  while (userChar != 'q') {
    if (userChar == 's') {
      delwin(scoresWindow);
      wclear(screen);
      return 1;
    }
    userChar = wgetch(stdscr);
  }
  return 0;
}