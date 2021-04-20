//
// Created by Nick Vazquez on 4/18/21.
//
// Functions for obtaining and setting new high scores in a Wacky Taxi Game
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_SCORES 5
#define NAME_LENGTH 10

#ifndef SE185_WACKYHIGHSCORE_H
#define SE185_WACKYHIGHSCORE_H

typedef struct {
    int score;
    char name[NAME_LENGTH];
} HighScore;

void printHighScore(HighScore* score) {
  printf("Name:  %s\nScore: %d\n", score->name, score->score);
}

FILE* openFile(char* filename, char* code, bool create) {
  FILE* scoreFile = fopen(filename, code);
  // Creates a file and populates it with base scores if not selected
  if (scoreFile != NULL) return scoreFile;
  else if (scoreFile == NULL && !create) {
    // If the file is nonexistent and the create flag is not true exit 100 (File error)
    exit(100);
  }
  else {
    scoreFile = fopen(filename, "w");
    for (int i = 0; i < NUM_SCORES; i++) {
      // Fill all high scores with a min of 10
      fputs("Jo Mama   ", scoreFile);
      fprintf(scoreFile, "%d\n", 10);
    }
    // Close and open with appropriate value
    fclose(scoreFile);
    scoreFile = fopen(filename, code);
  }
  return scoreFile;
}

/**
 * Returns the Highest Score
 * @param filename
 * @return
 */
HighScore* get_HighScores(char* filename) {
  HighScore* scores = malloc(sizeof(HighScore) * NUM_SCORES);
  FILE* file = openFile(filename, "r", false);

  for (int i = 0; i < NUM_SCORES; i++) {
    fgets((scores + i)->name, NAME_LENGTH, file);
    fscanf(file, "%d ", &(scores + i)->score);
  }
  return scores;
}

/**
 *
 * @param filename Filename where high scores are stored
 * @param name Name of player
 * @param score Score
 * @return 0 if score was not a high score, 1 if high score was added
 */
int add_HighScore(char* filename, char* name, int score) {
  FILE* originalFile;
  FILE* newFile;
  char* tempName = malloc(sizeof(char) * NAME_LENGTH);
  int tempScore;
  bool written = false;

  // Doing this file open differently to account for if there is no starting file.
  originalFile = openFile(filename, "r", true);
  newFile = openFile("scores.tmp", "w", true);

  for (int i = 0; i < NUM_SCORES; i++) {
    fgets(tempName, NAME_LENGTH, originalFile);
    fscanf(originalFile, "%d ", &tempScore);
    // If this score is higher than the one just found
    if (score > tempScore && !written) {
      fprintf(newFile, "%-10s %d\n", name, score);
      i++;
      written = true;
    }
    fprintf(newFile, "%-10s %d\n", tempName, tempScore);
  }
  fclose(originalFile);
  fclose(newFile);
  rename("scores.tmp", filename);
  return 1;
}

#endif //SE185_WACKYHIGHSCORE_H
