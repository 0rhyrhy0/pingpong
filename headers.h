#ifndef HEADERS_H
#define HEADERS_H

#define NANOSECONDS_PER_SECOND 1000000000L

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "headers/cursor.h"
#include "headers/game.h"
#include "headers/records.h"

extern pthread_mutex_t mutex;
extern pthread_cond_t cond;
extern volatile int terminate;

void updateGame();
void *gameLoop(void*);
void *keyboardInputs(void*);
void game_over();


#endif
