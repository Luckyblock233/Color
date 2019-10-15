#include <ctime>
#include <cstdio>
#include <cstring>
#include <windows.h>
#include "controlc.h"

const option long_options[] = {
  {"height", 1, NULL, 'h'},
  {"width", 1, NULL, 'w'},
  {NULL, 0, NULL, 0}
};
const char dtoh[] = "0123456789ABCDEF";
const char title[] = "Color !";
int CWheight = 13, CWwidth = 35;
int CWcB = 15, CWcF = 0;
std::mt19937 rnd(time(0));

void HideCursor() {
  HANDLE h;
  CONSOLE_CURSOR_INFO c;
  h = GetStdHandle(STD_OUTPUT_HANDLE);
  if (GetConsoleCursorInfo(h, &c)) {
    c.bVisible = FALSE;
    SetConsoleCursorInfo(h, &c);
  }
}

int RandomRange(int l, int r) {
  return (unsigned)rnd() % (r - l + 1) + l;
}

void ChangeConsoleWindowSize(int argc, char *argv[]) {
  int result;
  while (~(result = getopt_long(argc, argv, "h:w:", long_options, NULL))) {
    if (result == 'h') {
      CWheight = atoi(optarg);
    } else if (result == 'w') {
      CWwidth = atoi(optarg);
    }
  }
  char s[40];
  sprintf(s, "mode con lines=%d cols=%d", CWheight, CWwidth);
  system(s); system("cls");
}

void SetConsoleWindowName() {
  char s[30] = "title ";
  strcat(s, title);
  system(s); system("echo off"); system("cls");
}

void SetAllColor() {
  char s[10] = "color   ";
  s[6] = dtoh[CWcB], s[7] = dtoh[CWcF];
  system(s); system("cls");
}

void ChangeFontColor(int color = CWcF) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (CWcB << 4) | color);
}

void SetConsoleCursorPos(int x, int y) {
  COORD rhs; rhs.X = y, rhs.Y = x;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rhs);
}

void PrintText(const char *text, int color, int line, int pos = 0) {
  int len = strlen(text), col;
  switch (pos) {
    case -1 : col = 0; break;
    case 0  : col = (CWwidth - len) / 2; break;
    case 1  : col = CWwidth - len - 1; break;
  }
  SetConsoleCursorPos(line, col);
  if (color >= 0 && color < 15) {
    ChangeFontColor(color);
    printf("%s", text);
    ChangeFontColor(); 
  } else {
    for (int i = 0; i < len; ++i) {
      ChangeFontColor(RandomRange(0, 14));
      putchar(text[i]);
    }
    ChangeFontColor();
  }
}