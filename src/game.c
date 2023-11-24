#include "../headers/game.h"

Point ball;
Vector ball_dir;
int p1bar, p2bar; // ���� x��ǥ
int p1right, p1left, p2right, p2left; // �̵� ����
int score1, score2, fps;

void initializeBoard() {
  ball.x = BALL_INIT_X, ball.y = BALL_INIT_Y;
  ball_dir.x = BALL_INIT_DIR_X, ball_dir.y = BALL_INIT_DIR_Y;
  p1bar = BOARD_WIDTH/2+1 - BAR_MOVE;
  p2bar = BOARD_WIDTH/2+1;
  p1right = 0, p1left = 0;
  p2right = 0, p2left = 0;
  score1  = 0, score2 = 0;
  // fps : �Ź� ���
  system("clear");

  moveTo(1, 1); putchar('+');
  moveTo(1, BOARD_WIDTH+2); putchar('+');
  moveTo(BOARD_HEIGHT+2, 1); putchar('+');
  moveTo(BOARD_HEIGHT+2, BOARD_WIDTH+2); putchar('+');

  for(int i = 2; i < BOARD_WIDTH+2; i++) {
    moveTo(1, i); putchar('-');
    moveTo(BOARD_HEIGHT+2, i); putchar('-');
  }

  for(int i = 2; i < BOARD_HEIGHT+2; i++) {
    moveTo(i, 1); putchar('|');
    moveTo(i, BOARD_WIDTH+2); putchar('|');
  }

  updateBoard();
  moveBar(RIGHT_1P);
}

// ���� ����� 1 ��ȯ
int updateBoard() {
  int gameOver = 0;
  
  // ���� ���� ƨ��� ��Ȳ ���
  if(ball.x == 0 || ball.x == BOARD_WIDTH-1)
    ball_dir.x *= -1;

  // ���� �ٿ� ƨ��� ��Ȳ ����
  int nextX = ball.x + ball_dir.x;
  if(ball.y == 1 && (nextX >= p1bar - BAR_STRETCH && nextX <= p1bar + BAR_STRETCH))
    ball_dir.y *= -1, score1++;
  else if(ball.y == BOARD_HEIGHT-2 && (nextX >= p2bar - BAR_STRETCH && nextX <= p2bar + BAR_STRETCH))
    ball_dir.y *= -1, score2++;

  // ���� ���
  ball.x += ball_dir.x;
  ball.y += ball_dir.y;

  // ���ӿ��� ���
  if (ball.y == 0 || ball.y == BOARD_HEIGHT-1) gameOver = 1;

  // ������ ���
  for(int i = 1; i <= BOARD_HEIGHT-2; i++) { // �� ����� ���� ó��
    for(int j = 0; j < BOARD_WIDTH; j++) {
      moveTo(i+2, j+2);
      if(i == ball.y && j == ball.x)
        putchar(BALL);
      else
        putchar(BLANK);
    }
  }

  fps = 4 + ((score1 + score2)/10);
  moveTo(3, BOARD_WIDTH + 8); puts("SCORE");
  moveTo(4, BOARD_WIDTH + 7); printf("%2d : %d", score1, score2);
  moveTo(6, BOARD_WIDTH + 7); printf("FPS : %d", fps);
  moveTo(8, BOARD_WIDTH + 5); puts("FPS += 1 per 10 points");

  if(gameOver) return 1;

  return 0;
}

// wasd 1P, ����Ű 2P
Dir getInput(char x) {
  switch(x) {
    default : return NONE;

    case 'a' : return LEFT_1P;
    case 'd' : return RIGHT_1P;

    case ARROW_DETECT_1 : switch(getchar_()) {
      default : return NONE;

      case ARROW_DETECT_2 : switch(getchar_()) {
        default : return NONE;
        
        case LEFT  : return LEFT_2P;
        case RIGHT : return RIGHT_2P;
      } break;
    } break;
  }
  
  return NONE;
}

void moveBar(Dir d) {
  switch(d) {
    case LEFT_1P :
      p1bar = MAX(p1bar - BAR_MOVE, BAR_STRETCH);
      break;

    case LEFT_2P :
      p2bar = MAX(p2bar - BAR_MOVE, BAR_STRETCH);
      break;

    case RIGHT_1P :
      p1bar = MIN(p1bar + BAR_MOVE, BOARD_WIDTH - BAR_STRETCH - 1);
      break;

    case RIGHT_2P :
      p2bar = MIN(p2bar + BAR_MOVE, BOARD_WIDTH - BAR_STRETCH - 1);
      break;

    case NONE :
      return;
  }
  // ���� �ֻ��, ���ϴ� �� ���
  for(int x=1 ; x <= BOARD_WIDTH ; x++) {
    moveTo(2, x+1);
    putchar(BLANK);
    
    moveTo(BOARD_HEIGHT+1, x+1);
    putchar(BLANK);
  }
  
  puts(P1COLOR);
  for(int x = p1bar - BAR_STRETCH ; x <= p1bar + BAR_STRETCH; x++) {
    moveTo(2, x+2);
    if(x == p1bar + BAR_STRETCH)
      putchar(BAR_RIGHT);
    else if(x == p1bar - BAR_STRETCH)
      putchar(BAR_LEFT);
    else
      putchar(BAR);
  }
  puts(P2COLOR);
  for(int x = p2bar - BAR_STRETCH ; x <= p2bar + BAR_STRETCH; x++) {
    moveTo(BOARD_HEIGHT+1, x+2);
    if(x == p2bar + BAR_STRETCH)
      putchar(BAR_RIGHT);
    else if(x == p2bar - BAR_STRETCH)
      putchar(BAR_LEFT);
    else
      putchar(BAR);
  }
  puts(RESET);
  
  return;
}
