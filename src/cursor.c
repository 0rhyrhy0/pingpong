#include "../headers/cursor.h"

char getchar_() {
  struct termios original, modified;
  tcgetattr(STDIN_FILENO, &original);
  modified = original;
  modified.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &modified);

  char c = getchar();

  tcgetattr(STDIN_FILENO, &original);
  return c;
}

void moveTo(int y, int x) {
  printf("\033[%d;%dH", y, x);
}

void hidecursor() { printf("\033[?25l"); }
void showcursor() { printf("\033[?25h"); }
