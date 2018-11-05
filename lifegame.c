#include <stdio.h>
#include <windows.h>

#define Mark '*'
#define Blank ' '

#define GARDEN_ROW 25
#define GARDEN_COLUMNS 50
#define WAIT_TIME 1000

enum Threshold {
  Depopulation = 1,
  Born = 3,
  Overpopulation = 4
};

typedef char LifeGameState[GARDEN_ROW][GARDEN_COLUMNS];

int get_adjacent_count(LifeGameState, int, int);

char *garden[GARDEN_ROW] = {
  "##################################################",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "#               ***                              #",
  "#              *                                 #",
  "#                 *                              #",
  "#              ****                              #",
  "#              *                                 #",
  "#                                                #",
  "#              *                                 #",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "#                                                #",
  "##################################################"
};

LifeGameState lifeState = { Blank };

int main(void) {
  int year = 0;
  int life;

  do {
    life = 0;
    printf("\x1b[2J\n     ***** L I F E G A M E ( year=%d ) *****\n\n", year);
    for (int index = 0; index < GARDEN_ROW; index++) {
      printf("%s\n", garden[index]);
      strcpy(lifeState[index], garden[index]);
    }

    for (int row = 1; row < GARDEN_ROW - 1; row++) {
      for (int column = 1; column < GARDEN_COLUMNS - 1; column++) {
        int count = get_adjacent_count(lifeState, row, column);

        switch (lifeState[row][column]) {
          // Dead
          case Mark: {
            garden[row][column] = ((count <= Depopulation) || (Overpopulation <= count)) ? Blank : Mark;
            break;
          }
          // Born
          case Blank:
            garden[row][column] = (count == Born) ? Mark : Blank;
            break;
        }

        if (garden[row][column] == Mark) life++;

      }
    }
    Sleep(WAIT_TIME);
    year++;
  } while (life > 0);

  printf("All of lives dead in %d years\n", year);
  return 0;
}

int get_adjacent_count(char state[][GARDEN_COLUMNS], int row, int column) {
  int count = 0;

  // Upside
  if (state[row - 1][column - 1] == Mark) count++;
  if (state[row - 1][column] == Mark) count++;
  if (state[row - 1][column + 1] == Mark) count++;

  // Side
  if (state[row][column - 1] == Mark) count++;
  if (state[row][column + 1] == Mark) count++;

  // Downside
  if (state[row + 1][column - 1] == Mark) count++;
  if (state[row + 1][column] == Mark) count++;
  if (state[row + 1][column + 1] == Mark) count++;

  return count;
}
