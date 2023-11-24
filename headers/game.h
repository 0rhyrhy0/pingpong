#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#include "cursor.h"
#include "types.h"

// ��ũ�� �Լ�
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// ���Ӻ��� ������
#define BOARD_WIDTH  34
#define BOARD_HEIGHT 11

// ����Ű ���� ��� (UP, DOWN�� ���� ������� ����)
#define ARROW_DETECT_1 27
#define ARROW_DETECT_2 91
// #define UP    65
// #define DOWN  66
#define RIGHT 67
#define LEFT  68

// ����� �����ϱ� ���� ��ũ��
#define BALL      '@'
#define BLANK     ' '
#define BAR       '='
#define BAR_LEFT  '<'
#define BAR_RIGHT '>'

#define P1COLOR "\033[1;31m" // ���� & ����
#define P2COLOR "\033[1;34m" // �Ķ� & �Ʒ���
#define RESET   "\033[0m"    // �ʱ�ȭ

// ���� �ʱ� ��ġ(�߾�), ����(������)
#define BALL_INIT_X BOARD_WIDTH/2
#define BALL_INIT_Y BOARD_HEIGHT/2
#define BALL_INIT_DIR_X 1
#define BALL_INIT_DIR_Y 1

#define BAR_STRETCH 3 // �� �߽����κ��� ���� �������� �Ÿ�
#define BAR_MOVE    2 // �̵� �� ���� �̵� �Ÿ�



extern Point  ball;
extern Vector ball_dir;
extern int p1bar, p2bar; // ���� x��ǥ
extern int p1right, p1left, p2right, p2left; // �̵� ����
extern player player1, player2;
extern int fps;

void initializeBoard();
int  updateBoard();
Dir  getInput(char);
void moveBar(Dir);


#endif
