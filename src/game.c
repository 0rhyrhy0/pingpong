#include "../headers/game.h"

Point ball;
Vector ball_dir;
int p1bar, p2bar; // 바의 x좌표
int p1right, p1left, p2right, p2left; // 이동 방향
int score1, score2, fps;

void initializeBoard() {
  ball.x = BALL_INIT_X, ball.y = BALL_INIT_Y;
  ball_dir.x = BALL_INIT_DIR_X, ball_dir.y = BALL_INIT_DIR_Y;
  p1bar = BOARD_WIDTH/2+1 - BAR_MOVE;
  p2bar = BOARD_WIDTH/2+1;
  p1right = 0, p1left = 0;
  p2right = 0, p2left = 0;
  score1  = 0, score2 = 0;
  // fps : 매번 계산
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

// 게임 종료시 1 반환
int updateBoard() {
  int gameOver = 0;
  
  // 공이 벽에 튕기는 상황 계산
  if(ball.x == 0 || ball.x == BOARD_WIDTH-1)
    ball_dir.x *= -1;

  // 공이 바에 튕기는 상황 구현
  int nextX = ball.x + ball_dir.x;
  if(ball.y == 1 && (nextX >= p1bar - BAR_STRETCH && nextX <= p1bar + BAR_STRETCH))
    ball_dir.y *= -1, score1++;
  else if(ball.y == BOARD_HEIGHT-2 && (nextX >= p2bar - BAR_STRETCH && nextX <= p2bar + BAR_STRETCH))
    ball_dir.y *= -1, score2++;

  // 상태 계산
  ball.x += ball_dir.x;
  ball.y += ball_dir.y;

  // 게임오버 계산
  if (ball.y == 0 || ball.y == BOARD_HEIGHT-1) gameOver = 1;

  // 현상태 출력
  for(int i = 1; i <= BOARD_HEIGHT-2; i++) { // 바 출력은 따로 처리
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

// wasd 1P, 방향키 2P
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
  // 보드 최상단, 최하단 줄 출력
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
