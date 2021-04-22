//
// Created by Nick Vazquez on 4/18/21.
//

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#ifndef SE185_SYMBOLS_H
#define SE185_SYMBOLS_H

typedef struct sym{
    char* data;
    int height;
    int width;
} symbol;


const char* player = {
        "        _________\n"
        "       |         |\n"
        " _o_  _| ___=___ |_  _o_\n"
        "/`-'( )         ( ) /`-'\\\n"
        "|   |-|  ___*___  |-|   |\n"
        "|   | | (-+-+-+-) | |   |\n"
        "|   |--\\_SE185JN_/--|   |\n"
        " ---                 ---"
};
int carHeight = 8, carWidth = 26;

const char* yoda = {
        " ___/     \\___\n"
        "`-._)     (_,-`\n"
        "    \\O _ O/\n"
        "     \\ - / \n"
        "      `-(\n"
        "       ||\n"
        "      _||_\n"
        "     |-..-|\n"
        "     |/. \\|\n"
        "     |\\__/|\n"
        "   ._|//\\\\|_,\n"
        "   `-((  ))-'\n"
        "    __\\\\//__\n"
        "    >_ /\\ _<,\n"
        "      '  '"
};
int yodaHeight = 16, yodaWidth = 15;

const char* bike = {
        "              __\n"
        "   ,--.      <__)\n"
        "   `- |________7\n"
        "      |`.      |\\\n"
        "   .--|. \\     |.\\--.\n"
        "  /   j \\ `.7__j__\\  \\\n"
        " |   o   | (o)____O)  |\n"
        "  \\     /   J  \\     /\n"
        "   `---'        `---'\n"
};
int bikeHeight = 9, bikeWidth = 24;

const char* blinkerFluid = {
        "      _\n"
        "     /_\\\n"
        "    .'-'.\n"
        "  .'     '.\n"
        " '_________'\n"
        "(           )\n"
        "|.---------.|\n"
        "|: Blinker :|\n"
        "|:  Fluid  :|\n"
        "|'---------'|\n"
        "(___________)"
};
int blinkerFluidHeight = 11, blinkerFluidWidth = 14;

const char* creditCar = {
        "                                              _____________\n"
        "                                  ..---:::::::-----------. ::::;;.\n"
        "                               .'\"\"\"\"\"\"                  ;;   \\  \":.\n"
        "                            .''                          ;     \\   \"\\__.\n"
        "                          .'                            ;;      ;   \\\\\";\n"
        "                        .'                              ;   _____;   \\\\/\n"
        "                      .'                               :; ;\"     \\ ___:'.\n"
        "                    .'--...........................    : =   ____:\"    \\ \\\n"
        "               ..-\"\"                               \"\"\"'  o\"\"\"     ;     ; :\n"
        "          .--\"\"  .----- ..----...    _.-    --.  ..-\"     ;       ;     ; ;\n"
        "       .\"\"_-     \"--\"\"-----'\"\"    _-\"        .-\"\"         ;        ;    .-.\n"
        "    .'  .'                      .\"         .\"              ;       ;   /. |\n"
        "   /-./'                      .\"          /           _..  ;       ;   ;;;|\n"
        "  :  ;-.______               /       _________==.    /_  \\ ;       ;   ;;;;\n"
        "  ;  / |      \"\"\"\"\"\"\"\"\"\"\".---.\"\"\"\"\"\"\"          :    /\" \". |;       ; _; ;;;\n"
        " /\"-/  |                /   /                  /   /     ;|;      ;-\" | ;';\n"
        ":-  :   \"\"\"----______  /   /              ____.   .  .\"'. ;;   .-\"..T\"   .\n"
        "'. \"  ___            \"\":   '\"\"\"\"\"\"\"\"\"\"\"\"\"\"    .   ; ;    ;; ;.\" .\"   '--\"\n"
        " \",   __ \"\"\"  \"\"---... :- - - - - - - - - ' '  ; ;  ;    ;;\"  .\"\n"
        "  /. ;  \"\"\"---___                             ;  ; ;     ;|.\"\"\n"
        " :  \":           \"\"\"----.    .-------.       ;   ; ;     ;:\n"
        "  \\  '--__               \\   \\        \\     /    | ;     ;;\n"
        "   '-..   \"\"\"\"---___      :   .______..\\ __/..-\"\"|  ;   ; ;\n"
        "       \"\"--..       \"\"\"--\"        n m v         .   \". . ;\n"
        "             \"\"------...          j m l   ..--\"\"      \" :\n"
        "                        \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"    \\        /\n"
        "                                               \"------\""
};
int creditCarHeight = 27, creditCarWidth = 76;

const char* title = {
        "$$\\      $$\\                     $$\\                       $$$$$$$$\\                  $$\\ \n"
        "$$ | $\\  $$ |                    $$ |                      \\__$$  __|                 \\__|\n"
        "$$ |$$$\\ $$ | $$$$$$\\   $$$$$$$\\ $$ |  $$\\ $$\\   $$\\          $$ | $$$$$$\\  $$\\   $$\\ $$\\ \n"
        "$$ $$ $$\\$$ | \\____$$\\ $$  _____|$$ | $$  |$$ |  $$ |         $$ | \\____$$\\ \\$$\\ $$  |$$ |\n"
        "$$$$  _$$$$ | $$$$$$$ |$$ /      $$$$$$  / $$ |  $$ |         $$ | $$$$$$$ | \\$$$$  / $$ |\n"
        "$$$  / \\$$$ |$$  __$$ |$$ |      $$  _$$<  $$ |  $$ |         $$ |$$  __$$ | $$  $$<  $$ |\n"
        "$$  /   \\$$ |\\$$$$$$$ |\\$$$$$$$\\ $$ | \\$$\\ \\$$$$$$$ |         $$ |\\$$$$$$$ |$$  /\\$$\\ $$ |\n"
        "\\__/     \\__| \\_______| \\_______|\\__|  \\__| \\____$$ |         \\__| \\_______|\\__/  \\__|\\__|\n"
        "                                           $$\\   $$ |                                     \n"
        "                                           \\$$$$$$  |                                     \n"
        "                                            \\______/                                      \n"
};
int titleHeight = 11, titleWidth = 91;

WINDOW* obstacle(int startY, int startX) {
  WINDOW *win;
  srand(time(NULL));
  int num = rand() % 45;
  // win = newwin(20, 20, 1, 1);
  switch (num) {
    case 0 ... 25:
      win = newwin(bikeHeight, bikeWidth, startY, startX);
      wprintw(win, bike);
      break;
    case 26 ... 35:
      win = newwin(blinkerFluidHeight, blinkerFluidWidth, startY, startX);
      wprintw(win, blinkerFluid);
      break;
    case 36 ... 45:
    default:
      win = newwin(yodaHeight, yodaWidth, startY, startX);
      wprintw(win, yoda);
      break;
  }
  wrefresh(win);
  return win;
}
#endif //SE185_SYMBOLS_H
