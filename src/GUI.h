//
// Created by Nick Vazquez on 4/20/21.
//

#include "WackyHighScore.h"
#include "MatrixFunctions.h"
#include "strings.h"

#define MIN_SCREEN_X 30
#define MIN_SCREEN_Y 20
#define SPACING_MARGIN 1

#define LANE_WIDTH 10
#define NUM_LANES 4

#ifndef SE185_GUI_H
#define SE185_GUI_H

typedef struct {
    int x;
    int y;
} point;

void startWindow() {
  int xSize, ySize;
  // Start curses
  initscr();
  clear();
  noecho();
  cbreak();
  refresh();

  // Enable Keypad
  keypad(stdscr, TRUE);
  // Screen Size Checking
  getmaxyx(stdscr, xSize, ySize);
  if (xSize < MIN_SCREEN_X) exit(200);
  if (ySize < MIN_SCREEN_Y) exit(201);
}

/**
 * Returns the center of the provided screen
 *
 * @param screen
 * @return point struct of screen center coordinates
 */
point *cent(WINDOW *screen) {
  int scrXSize, scrYSize;
  point *center = malloc(sizeof(point));

  getmaxyx(screen, scrYSize, scrXSize);
  center->y = scrYSize / 2;
  center->x = scrXSize / 2;
  return center;
}

/**
 * Returns a point for an object to be placed where the object will be centered on the screen.
 * Eases relative positioning.
 *
 * @param screen Window to measure width/height. This is most likely going to be stdscr, but can be nested.
 * @param objectHeight Height of object to be centered
 * @param objectWidth Width of object to be centered
 * @return Point pointer for window location
 */
point *offsetCenter(WINDOW *screen, int objectHeight, int objectWidth) {
  point *center = cent(screen);
  point *offset = malloc(sizeof(point));
  offset->y = center->y - (objectHeight / 2);
  offset->x = center->x - (objectWidth / 2);
  return offset;
}

void getLaneCols(int* colArray, int numLanes, int screenCols) {
  for (int i = 0; i < numLanes; i++) {
    *(colArray + i) = (screenCols / 2) - ((LANE_WIDTH * NUM_LANES) / 2) + (LANE_WIDTH * i);
  }
}

/**
 * Displays the WackyTaxi title screen
 *
 * @return Selection of user (0 for start game, 1 for high scores)
 */
int titleScreen() {
  WINDOW *titleWindow;
  int windowWidth;
  int windowHeight;
  int c;

  windowWidth = titleWidth;
  windowHeight = titleHeight + creditCarHeight + (SPACING_MARGIN * 2) + 2;

  // Point where the title window is centered. Sum all heights and max width.
  point *titleCenter = offsetCenter(stdscr, windowHeight, windowWidth);
  // Create the window with the new coordinates
  titleWindow = newwin(windowHeight, windowWidth, titleCenter->y, titleCenter->x);
  // Print the player directly to the window
  wprintw(titleWindow, creditCar);
  // Move cursor to start of new line
  wmove(titleWindow, creditCarHeight + SPACING_MARGIN, 0);
  // Print Title and add prompts
  wprintw(titleWindow, title);
  wmove(titleWindow, creditCarHeight + titleHeight + (SPACING_MARGIN * 2), offsetCenter(titleWindow, 1, 50)->x);
  wprintw(titleWindow, "%-20s %-20s", "PRESS S TO BEGIN", "PRESS L TO VIEW LEADERBOARD");
  // Refresh the window
  wrefresh(titleWindow);

  // Return int based on keypress
  while (c != 'l' && c != 's') {
    c = wgetch(titleWindow);
    switch (c) {
      case 's':
        clear();
        return 0;
      case 'l':
        clear();
        return 1;
      default:
        continue;
    }
  }
  return -1;
}

/**
 * Prints the lanes
 * @param screen
 */
WINDOW* printLanes(WINDOW* screen) {
  int     screenHeight, screenWidth;
  WINDOW* laneWindow;
  point*  windowLocation;
  char*   laneSeparator;

  laneSeparator = malloc(1 * sizeof(char));

  getmaxyx(screen, screenHeight, screenWidth);
  strcpy(laneSeparator, "|");

  windowLocation  = offsetCenter(screen, screenHeight, LANE_WIDTH * NUM_LANES + NUM_LANES);
  laneWindow      = newwin(screenHeight, (LANE_WIDTH * NUM_LANES) + NUM_LANES, windowLocation->y, windowLocation->x);

  for (int row = 0; row < screenHeight; row++) {
    for (int lane = 0; lane <= NUM_LANES; lane++) {
      wmove(laneWindow, row, LANE_WIDTH * lane);
      wprintw(laneWindow, laneSeparator);
    }
  }
  wrefresh(laneWindow);
  return laneWindow;
}

WINDOW* printCar(int startY, int startX) {
  WINDOW *car;
  car    = newwin(carHeight, carWidth, startY, startX);
  wprintw(car, player);
  wrefresh(car);
  return car;
}

WINDOW** printBoardToScreen(GameBoard* gameBoard, WINDOW* screen) {
  int       screenWidth, screenHeight;
  int       cellHeight;
  int*      laneColumns;
  WINDOW**  sprites;
  WINDOW*   sprite;
  Object*   boardRow;
  Object    currentCell;

  laneColumns = (int*)      malloc(NUM_LANES * sizeof(int));
  sprites     = (WINDOW**)  malloc(gameBoard->boardRows * gameBoard->boardColumns);

  // Screen sizing things
  getmaxyx(screen, screenHeight, screenWidth);
  cellHeight = (screenHeight - carHeight) / (gameBoard->boardRows - 1);
  getLaneCols(laneColumns, NUM_LANES, screenWidth);

  // Prints lanes
  printLanes(screen);

  // Iterates through board
  for (int row = 0; row < gameBoard->boardRows; row++) {
    boardRow = *(gameBoard->board + row);
    for (int col = 0; col < gameBoard->boardColumns; col++) {
      currentCell = *(boardRow + col);
      switch (currentCell) {
        case CAR:
          sprite = printCar(cellHeight * row, *(laneColumns + col) + 2);
          break;
        case OBSTACLE:
          sprite = obstacle(cellHeight * row, *(laneColumns + col) + 2);
          break;
        case EMPTY:
          sprite = NULL;
          break;
        default:
          break;
      }
      *(sprites + (row * gameBoard->boardColumns) + col) = sprite;
    }
  }
  wrefresh(stdscr);
  return sprites;
}

void clearSprites(WINDOW** sprites, int numItems) {
  for (int i = 0; i < numItems; i++) {
    if (*(sprites + i) != NULL) delwin(*(sprites + i));
  }
}

WINDOW *printHighScores(HighScore *scores) {
  int windowWidth, windowHeight;
  windowHeight = NUM_SCORES + HighScoreTitleHeight + 1;
  windowWidth = HighScoreTitleWidth;
  point *center = offsetCenter(stdscr, windowHeight, windowWidth);
  WINDOW *scoresWindow = newwin(windowHeight, windowWidth, center->y, center->x);
  wrefresh(scoresWindow);
  // Get the center of the window for the title
  point *titleCenter = offsetCenter(scoresWindow, HighScoreTitleHeight, HighScoreTitleWidth);
  // Get the center of the window for the scores
  point *scoresCenter = offsetCenter(scoresWindow, windowHeight, 15);
  // Add the High Score Title
  mvwaddstr(scoresWindow, 1, titleCenter->x, HighScoreTitle);
  // For each score returned, add to the window
  for (int scoreNum = 0; scoreNum < NUM_SCORES; scoreNum++) {
    char *scorer = (char *) malloc(20 * sizeof(char));
    sprintf(scorer, "%d: %-10s %d", scoreNum + 1, (scores + scoreNum)->name, (scores + scoreNum)->score);
    mvwaddstr(scoresWindow, HighScoreTitleHeight + scoreNum + 1, scoresCenter->x, scorer);
  }
  wrefresh(scoresWindow);
  return scoresWindow;
}

WINDOW* printScoreInGame(int score) {
  WINDOW* scoreWin;
  int     scoreLen, tempScore;
  char*   highScoreString;

  highScoreString = "Score: ";
  scoreLen        = 0;
  tempScore       = score;

  while (tempScore != 0) {
    tempScore /= 10;
    scoreLen++;
  }

  scoreWin        = newwin(0, 0, 1, ((int) strlen(highScoreString)) + scoreLen);
  mvwprintw(scoreWin, 0, 0, highScoreString);
  mvwprintw(scoreWin, 0, ((int) strlen(highScoreString) + 1), "%d", score);

  wrefresh(scoreWin);
  return scoreWin;
}

#endif //SE185_GUI_H
