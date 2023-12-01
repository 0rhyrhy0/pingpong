#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <stdio.h>
#include <stdlib.h>

#include "cursor.h"
#include "types.h"
#include "game.h"

void displayMenu(int, int);

// records.c
extern void getPlayerNames();
extern void saveRecords();
extern int recordsCount();
void retrieveRecords(gameResult*, int);
void showRecords(gameResult*, int);


#endif