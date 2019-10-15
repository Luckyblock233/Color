#include <windows.h>
#include "controlc.h"
#include "functions.h"

int main(int argc, char *argv[]) {
  HideCursor();
  SetConsoleWindowName();
  ChangeConsoleWindowSize(argc, argv);
  while (GameMainLoop());
  return 0;
}