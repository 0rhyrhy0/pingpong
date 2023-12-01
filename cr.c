#include <stdio.h>

int main() {
  printf("\033[?25h");
  printf("\033[0m");
  return 0;
}