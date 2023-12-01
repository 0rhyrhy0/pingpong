#include "../headers/game.h"

Point ball;
Vector ball_dir;
int p1bar, p2bar; // 바의 x좌표
int p1right, p1left, p2right, p2left; // 이동 방향
player player1, player2;
int fps;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
volatile int terminate = 0;

void ascii()
{ // ascii art title
  moveTo(1, 1);
  puts(" ____                               ____");
  puts("/\\  _`\\   __                       /\\  _`\\");
  puts("\\ \\ \\L\\ \\/\\_\\     ___       __     \\ \\ \\L\\ \\  ___     ___       __");
  puts(" \\ \\ ,__/\\/\\ \\   /'_ `\\   /'_ `\\    \\ \\ ,__/ / __`\\ /' _ `\\   /'_ `\\");
  puts("  \\ \\ \\/  \\ \\ \\ /\\ \\/\\ \\ /\\ \\/\\ \\    \\ \\ \\/ /\\ \\L\\ \\/\\ \\/\\ \\ /\\ \\/\\ \\");
  puts("   \\ \\_\\   \\ \\_\\\\ \\_\\ \\_\\\\ \\____ \\    \\ \\_\\ \\ \\____/\\ \\_\\ \\_\\\\ \\____ \\");
  puts("    \\/_/    \\/_/ \\/_/\\/_/ \\/___L\\ \\    \\/_/  \\/___/  \\/_/\\/_/ \\/___L\\ \\");
  puts("                            /\\____/                             /\\____/");
  puts("                            \\_/__/                              \\_/__/");
}

void initializeBoard() {
  ball.x = BALL_INIT_X, ball.y = BALL_INIT_Y;
  ball_dir.x = BALL_INIT_DIR_X, ball_dir.y = BALL_INIT_DIR_Y;
  p1bar = BOARD_WIDTH/2+1 - BAR_MOVE;
  p2bar = BOARD_WIDTH/2+1;
  p1right = 0, p1left = 0;
  p2right = 0, p2left = 0;
  player1.score  = 0, player2.score = 0;
  // fps : 매번 계산
  system("clear");
  puts("\033[38;2;100;200;200m");
  ascii();

  moveTo(GAMEBOARD_Y_OFFSET + 1, 1);                          putchar('+');
  moveTo(GAMEBOARD_Y_OFFSET + 1, BOARD_WIDTH+2);              putchar('+');
  moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT+2, 1);             putchar('+');
  moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT+2, BOARD_WIDTH+2); putchar('+');

  for(int i = 2; i < BOARD_WIDTH+2; i++) {
    moveTo(GAMEBOARD_Y_OFFSET + 1, i); putchar('-');
    moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT+2, i); putchar('-');
  }

  for(int i = 2; i < BOARD_HEIGHT+2; i++) {
    moveTo(GAMEBOARD_Y_OFFSET + i, 1); putchar('|');
    moveTo(GAMEBOARD_Y_OFFSET + i, BOARD_WIDTH+2); putchar('|');
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
    ball_dir.y *= -1, player1.score++;
  else if(ball.y == BOARD_HEIGHT-2 && (nextX >= p2bar - BAR_STRETCH && nextX <= p2bar + BAR_STRETCH))
    ball_dir.y *= -1, player2.score++;

  // 상태 계산
  ball.x += ball_dir.x;
  ball.y += ball_dir.y;

  // 게임오버 계산
  if (ball.y == 0 || ball.y == BOARD_HEIGHT-1) gameOver = 1;

  // 현상태 출력
  puts("\033[38;2;190;130;240m");
  for(int i = 1; i <= BOARD_HEIGHT-2; i++) { // 바 출력은 따로 처리
    for(int j = 0; j < BOARD_WIDTH; j++) {
      moveTo(GAMEBOARD_Y_OFFSET + i+2, j+2);
      if(i == ball.y && j == ball.x)
        putchar(BALL);
      else
        putchar(BLANK);
    }
  }
  puts(RESET);

  fps = 8 + ((player1.score + player2.score)/10);
  moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT + 3, 0); puts("SCORE");

  moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT + 3, 7); 
  printf("%s%2d%s : %s%d%s",  P1COLOR, player1.score, RESET,
                              P2COLOR, player2.score, RESET);

  moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT + 3, 35); printf("\033[1;33mFPS : %d\033[0m", fps);

  moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT + 3, 51); puts("\033[1;30mFPS += 1 per 10 points\033[0m");

  if(gameOver) return 1;

  return 0;
}

// wasd 1P, 방향키 2P
Dir getInput(char x) {
  switch(x) {
    default   : return NONE;
    case '\n' : return ENTER;

    case 'w' : return UP_1P;
    case 'a' : return LEFT_1P;
    case 's' : return DOWN_1P;
    case 'd' : return RIGHT_1P;

    case ARROW_DETECT_1 : switch(getchar_()) {
      default : return NONE;

      case ARROW_DETECT_2 : switch(getchar_()) {
        default : return NONE;
        
        case UP    : return UP_2P;
        case DOWN  : return DOWN_2P;
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

    case NONE : case ENTER : 
    case UP_1P : case DOWN_1P :
    case UP_2P : case DOWN_2P : return;
  }
  // 보드 최상단, 최하단 줄 출력
  for(int x=1 ; x <= BOARD_WIDTH ; x++) {
    moveTo(GAMEBOARD_Y_OFFSET + 2, x+1);
    putchar(BLANK);
    
    moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT+1, x+1);
    putchar(BLANK);
  }
  
  puts(P1COLOR);
  for(int x = p1bar - BAR_STRETCH ; x <= p1bar + BAR_STRETCH; x++) {
    moveTo(GAMEBOARD_Y_OFFSET + 2, x+2);
    if(x == p1bar + BAR_STRETCH)
      putchar(BAR_RIGHT);
    else if(x == p1bar - BAR_STRETCH)
      putchar(BAR_LEFT);
    else
      putchar(BAR);
  }
  puts(P2COLOR);
  for(int x = p2bar - BAR_STRETCH ; x <= p2bar + BAR_STRETCH; x++) {
    moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT+1, x+2);
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


void updateGame() {
  pthread_mutex_lock(&mutex);

  if(updateBoard()) {
    pthread_mutex_unlock(&mutex);
    game_over();
    return;
  }

  pthread_mutex_unlock(&mutex);
}

void *gameLoop(void*) {
  struct timespec startTime, endTime;
  long sleepTime;

  while (!terminate) {
    clock_gettime(CLOCK_MONOTONIC, &startTime);
    updateGame();
    if(terminate) break;
    clock_gettime(CLOCK_MONOTONIC, &endTime);

    sleepTime = NANOSECONDS_PER_SECOND / fps - 
                (endTime.tv_nsec - startTime.tv_nsec + 
                ( endTime.tv_sec - startTime.tv_sec) * NANOSECONDS_PER_SECOND);


    if (sleepTime > 0) {
      struct timespec ts;
      ts.tv_sec  = sleepTime / NANOSECONDS_PER_SECOND;
      ts.tv_nsec = sleepTime % NANOSECONDS_PER_SECOND;
      nanosleep(&ts, NULL);
    }
  }

  game_over();
  return NULL;
}

void *keyboardInputs(void*) {
  char x;
  
  while( !terminate && (x = getchar_() ) != 'q' ) {
    pthread_mutex_lock(&mutex);
    moveBar(getInput(x));
    pthread_mutex_unlock(&mutex);
  }

  game_over();
  return NULL;
}

void game_over() {
  pthread_mutex_lock(&mutex);
  terminate = 1;
  pthread_cond_broadcast(&cond);
  
  moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT/2 - 1, BOARD_WIDTH/2 - 2);
  puts("GAME OVER");
  
  moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT/2 + 1, BOARD_WIDTH/2 - 8);
  printf("Press " P1COLOR "'r'" RESET " to " P1COLOR "R" RESET "estart");
  
  moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT/2 + 2, BOARD_WIDTH/2 - 7);
  printf("Press " P2COLOR "'q'" RESET " to " P2COLOR "Q" RESET "uit");
  
  pthread_mutex_unlock(&mutex);
}


void gameStart()
{
  char input;
  pthread_t gameLoopThread, keyboardInputThread;
  
  while(1) {
    initializeBoard();
    moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT/2 + 3, BOARD_WIDTH/2 - 3); puts("PRESS @NY KEY");
    moveTo(GAMEBOARD_Y_OFFSET + BOARD_HEIGHT/2 + 4, BOARD_WIDTH/2);     puts("TO START");
    getchar_();

    pthread_create(&gameLoopThread,      NULL, keyboardInputs, NULL);
    pthread_create(&keyboardInputThread, NULL, gameLoop,       NULL);
    pthread_join(keyboardInputThread, NULL);
    pthread_join(gameLoopThread,      NULL);

    while( (input = getchar_()) != 'q' && input != 'r' ); // q, r 입력 대기
    terminate = 0;
    if(input == 'q') break;
  }
}
