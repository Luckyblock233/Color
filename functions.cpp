#include <cmath>
#include <ctime>
#include <cstdio>
#include <conio.h>
#include <windows.h>
#include "controlc.h"
#include "functions.h"

const int colorsize = 8;
const int gamingcolor[] = {0, 2, 3, 4, 5, 6, 8, 9};
const char *color_name[] = {
  "Black",
  "Green",
  "Turquoise",
  "Red",
  "Purple",
  "Yellow",
  "Grey",
  "Blue"
};

bool GameMenu() {
  while (true) {
    clock_t start = clock();
    PrintText(title, -1, CWheight / 3, 0);
    PrintText("Press Enter to start...", -1, CWheight / 3 * 2, 0);
    while (!kbhit() && 1. * (clock() - start) / CLOCKS_PER_SEC < 1);
    if (kbhit()) {
      int c = getch();
      if (c == 13 || c == 27) return c == 13;
    }
  }
}

void GameScene() {
  clock_t start = clock();
  char s[20];
  int score = 0;
  int isright, c1, c2;
  isright = RandomRange(0, 1);
  if (isright) c1 = c2 = RandomRange(0, colorsize - 1);
  else c1 = RandomRange(0, colorsize - 1), c2 = RandomRange(0, colorsize - 1);
  if (!isright && c1 == c2) c2 += c2 ? -1 : 1;
  while (1. * (clock() - start) / CLOCKS_PER_SEC < 30) {
    sprintf(s, "%.2fs", 1. * (clock() - start) / CLOCKS_PER_SEC);
    PrintText(s, 0, CWheight - 1, 1);
    PrintText(color_name[c1], gamingcolor[c2], CWheight / 2, 0);
    if (kbhit()) {
      int c = getch();
      if (c == 27) return;
      if (c == 75 || c == 77) {
        if ((c == 75) ^ isright) score++;
        else start -= 3 * CLOCKS_PER_SEC;
        isright = RandomRange(0, 1);
        if (isright) c1 = c2 = RandomRange(0, colorsize - 1);
        else c1 = RandomRange(0, colorsize - 1), c2 = RandomRange(0, colorsize - 1);
        if (!isright && c1 == c2) c2 += c2 ? -1 : 1;
        system("cls");
      }
    }
  }
  sprintf(s, "Your score : %d", score);
  PrintText(s, 0, CWheight / 2, 0);
  for (int c; c != 27 && c != 13; c = getch());
}

bool GameMainLoop() {
  SetAllColor();
  if (!GameMenu()) return false;
  system("cls");
  GameScene();
  return true;
}