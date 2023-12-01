#ifndef TYPES_H
#define TYPES_H



// 매크로 함수
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// 방향키 관련 상수 (UP, DOWN은 아직 사용하지 않음)
#define ARROW_DETECT_1 27
#define ARROW_DETECT_2 91
#define UP    65
#define DOWN  66
#define RIGHT 67
#define LEFT  68

// 키보드 입력값
typedef enum {
  NONE = 0,
  LEFT_1P, RIGHT_1P, UP_1P, DOWN_1P,
  LEFT_2P, RIGHT_2P, UP_2P, DOWN_2P,
  ENTER
} Dir;

// 좌표 관련
typedef struct {
  int x;
  int y;
} Point, Vector;

typedef struct {
  char name[50];
  int score;
} player;

typedef struct {
  player p1;
  player p2;
} gameResult;


#endif
