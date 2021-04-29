//
// Created by Nick Vazquez on 4/29/21.
//
#include "GUI.h"
#include "WackyHighScore.h"
#include <ncurses.h>
#include <time.h>


#define NUM_ROWS 20
#define NUM_COLS 4

void processKeyPress(int* lane, int userChar);
bool showScores(WINDOW* scoresWindow, WINDOW* screen);
void startGame();
void endGame();

int main() {
  int userChoice;
  WINDOW* scoresWin = NULL;

  startWindow();
  userChoice = titleScreen();
  // Start game
  if (userChoice == 0) startGame();
    // Show scores
  else if (userChoice == 1) {
    userChoice = showScores(scoresWin, stdscr);
    if (userChoice == 1) {
      startGame();
    }
  }
  endwin();
  return EXIT_SUCCESS;
}

void startGame() {
  int         lane, userKey, score;
  bool        running;
  WINDOW*     gameWindow;
  WINDOW*     laneWindow;
  WINDOW*     scoreWindow;
  GameBoard*  gameBoard;
  Object*     newLine;
  point*      windowCenter;

  srand(clock());
  startWindow();
  refresh();

  score         = 10;
  running       = true;
  lane          = NUM_LANES / 2;
  gameBoard     = generateBoard(NUM_ROWS, NUM_COLS);
  windowCenter  = offsetCenter(stdscr, gameBoard->boardRows * 2,
                              gameBoard->boardColumns * 10);

  for (int i = 0; running && userKey != 'q'; i++) {
    newLine = generateNewLine(NUM_LANES, (i % 3 == 0));
    advanceBoard(gameBoard, newLine);
    scoreWindow = printScoreInGame(score);
    running     = setCarLane(gameBoard, lane);
    gameWindow  = printBoardInteractive(gameBoard, windowCenter->y, windowCenter->x);
    laneWindow  = printLanes(gameWindow);
    refresh();
    if (running) {
      userKey = getch();
      processKeyPress(&lane, userKey);
      score += 10;
    }
  }

  delwin(scoreWindow);
  delwin(gameWindow);
  delwin(laneWindow);
  endGame(score);
}

void endGame(int score) {
  WINDOW* scoresWin = NULL;
  char*   name;
  name = "Maruf";
  add_HighScore("scores.txt", name, score);
  showScores(scoresWin, stdscr);
  delwin(scoresWin);
  endwin();
}

void processKeyPress(int* lane, int userChar) {
  if (userChar == KEY_LEFT && *lane > 0) {
    (*lane)--;
  }
  else if (userChar == KEY_RIGHT && *lane < NUM_LANES - 1){
    (*lane)++;
  }
}

bool showScores(WINDOW* scoresWindow, WINDOW* screen) {
  int userChar;

  clear();
  refresh();

  HighScore *scores = get_HighScores("scores.txt");
  scoresWindow = printHighScores(scores);
  userChar = wgetch(stdscr);
  while (userChar != 'q') {
    if (userChar == 's') {
      delwin(scoresWindow);
      wclear(screen);
      return true;
    }
    userChar = wgetch(stdscr);
  }
  return false;
}