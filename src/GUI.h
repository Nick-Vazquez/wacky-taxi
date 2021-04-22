//
// Created by Nick Vazquez on 4/20/21.
//

#define MIN_SCREEN_X 30
#define MIN_SCREEN_Y 20
#define SPACING_MARGIN 1

#define LANE_WIDTH 25

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

  // Screen Size Checking
  getmaxyx(stdscr, xSize, ySize);
  if (xSize < MIN_SCREEN_X) exit(200);
  if (ySize < MIN_SCREEN_Y) exit(201);
}

point* cent(WINDOW *screen) {
  int scrXSize, scrYSize;
  point *center = malloc(sizeof(point));

  getmaxyx(screen, scrYSize, scrXSize);
  center->y = scrYSize / 2;
  center->x = scrXSize / 2;
  return center;
}

point* offsetCenter(WINDOW *screen, int objectHeight, int objectWidth) {
  point* center = cent(screen);
  point* offset = malloc(sizeof(point));
  offset->y = center->y - (objectHeight / 2);
  offset->x = center->x - (objectWidth / 2);
  return offset;
}

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
  // Print the car directly to the window
  wprintw(titleWindow, creditCar);
  // Move cursor to start of new line
  wmove(titleWindow, creditCarHeight + SPACING_MARGIN, 0);
  // Print Title and add prompts
  wprintw(titleWindow, title);
  wmove(titleWindow, creditCarHeight + titleHeight + (SPACING_MARGIN*2), offsetCenter(titleWindow, 1, 50)->x);
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

void printLanes(WINDOW* screen) {
  int cols, rows;
  int numLanes = 3;
  char laneSeparator = '|';

  getmaxyx(screen, rows, cols);
  for (int row = 0; row < rows; row++) {
    // move(row, (cols / 2) - ((LANE_WIDTH * numLanes) / 2));
    for (int lane = 0; lane <= numLanes; lane++) {
      move(row, (cols / 2) - ((LANE_WIDTH * numLanes) / 2) + (LANE_WIDTH * lane));
      printw("%c", laneSeparator);
    }
  }
}
#endif //SE185_GUI_H
