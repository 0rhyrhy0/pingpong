#ifndef TYPES_H
#define TYPES_H

// Ű���� �Է°�
typedef enum {
  NONE = 0,
  LEFT_1P, RIGHT_1P,
  LEFT_2P, RIGHT_2P
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
