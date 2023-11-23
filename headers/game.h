#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#include "cursor.h"

// 매크로 함수
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// 게임보드 사이즈
#define BOARD_WIDTH  34
#define BOARD_HEIGHT 11

// 방향키 관련 상수 (UP, DOWN은 아직 사용하지 않음)
#define ARROW_DETECT_1 27
#define ARROW_DETECT_2 91
// #define UP    65
// #define DOWN  66
#define RIGHT 67
#define LEFT  68

// 출력을 조정하기 위한 매크로
#define BALL      '@'
#define BLANK     ' '
#define BAR       '='
#define BAR_LEFT  '<'
#define BAR_RIGHT '>'

#define P1COLOR "\033[1;31m" // 빨강 & 위쪽
#define P2COLOR "\033[1;34m" // 파랑 & 아래쪽
#define RESET   "\033[0m"    // 초기화

// 공의 초기 위치(중앙), 방향(우하향)
#define BALL_INIT_X BOARD_WIDTH/2
#define BALL_INIT_Y BOARD_HEIGHT/2
#define BALL_INIT_DIR_X 1
#define BALL_INIT_DIR_Y 1

#define BAR_STRETCH 3 // 바 중심으로부터 양쪽 끝까지의 거리
#define BAR_MOVE    2 // 이동 시 바의 이동 거리

// 키보드 입력값
typedef enum {
  NONE = 0,
  LEFT_1P, RIGHT_1P,
  LEFT_2P, RIGHT_2P
} Dir;

// 좌표 관련
typedef struct {
  int x;
  int y;
} Point, Vector;

extern Point  ball;
extern Vector ball_dir;
extern int p1bar, p2bar; // 바의 x좌표
extern int p1right, p1left, p2right, p2left; // 이동 방향
extern int score1, score2, fps;

void initializeBoard();
int  updateBoard();
Dir  getInput(char);
void moveBar(Dir);


#endif
