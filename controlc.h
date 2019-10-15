
#ifndef _CONTROLC_H
#define _CONTROLC_H

#include <random>
#include <getopt.h>

extern const option long_options[];
extern const char dtoh[];
extern const char title[];
extern int CWheight, CWwidth;
extern int CWcB, CWcF;
extern std::mt19937 rnd;

void HideCursor();
int RandomRange(int l, int r);
void ChangeConsoleWindowSize(int argc, char *argv[]);
void SetConsoleWindowName();
void SetAllColor();
void ChangeFontColor(int color);
void SetConsoleCursorPos(int x, int y);
void PrintText(const char *text, int color, int line, int pos);

#endif