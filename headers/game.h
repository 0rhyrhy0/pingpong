#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "cursor.h"
#include "types.h"

#define NANOSECONDS_PER_SECOND 1000000000L

// 게임보드 사이즈
#define BOARD_WIDTH  70
#define BOARD_HEIGHT 23

// 출력을 조정하기 위한 매크로
#define BALL      '@'
#define BLANK     ' '
#define BAR       '='
#define BAR_LEFT  '<'
#define BAR_RIGHT '>'

// 공의 초기 위치(중앙), 방향(우하향)
#define BALL_INIT_X BOARD_WIDTH/2
#define BALL_INIT_Y BOARD_HEIGHT/2
#define BALL_INIT_DIR_X 1
#define BALL_INIT_DIR_Y 1

#define BAR_STRETCH 3 // 바 중심으로부터 양쪽 끝까지의 거리
#define BAR_MOVE    2 // 이동 시의 바의 이동 거리

#define GAMEBOARD_Y_OFFSET 10


extern Point  ball;
extern Vector ball_dir;
extern int p1bar, p2bar; // 바의 x좌표
extern int p1right, p1left, p2right, p2left; // 이동 방향
extern player player1, player2;
extern int fps;

extern pthread_mutex_t mutex;
extern pthread_cond_t cond;
extern volatile int terminate;

void initializeBoard();
int  updateBoard();
Dir  getInput(char);
void moveBar(Dir);

void updateGame();
void *gameLoop(void*);
void *keyboardInputs(void*);
void game_over();

void ascii();
void gameStart();


#endif
