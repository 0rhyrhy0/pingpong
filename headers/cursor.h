#ifndef CURSOR_H
#define CURSOR_H

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

char getchar_();
void moveTo(int, int);
void hidecursor();
void showcursor();

#endif
