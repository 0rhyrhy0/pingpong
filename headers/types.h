#ifndef TYPES_H
#define TYPES_H



// ��ũ�� �Լ�
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// ����Ű ���� ��� (UP, DOWN�� ���� ������� ����)
#define ARROW_DETECT_1 27
#define ARROW_DETECT_2 91
#define UP    65
#define DOWN  66
#define RIGHT 67
#define LEFT  68

// Ű���� �Է°�
typedef enum {
  NONE = 0,
  LEFT_1P, RIGHT_1P, UP_1P, DOWN_1P,
  LEFT_2P, RIGHT_2P, UP_2P, DOWN_2P,
  ENTER
} Dir;

// ��ǥ ����
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
