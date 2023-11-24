#include "headers.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
volatile int terminate = 0;

// game.c
extern int fps;

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
  
  moveTo(BOARD_HEIGHT/2 - 1, BOARD_WIDTH/2 - 2);
  puts("GAME OVER");
  
  moveTo(BOARD_HEIGHT/2 + 1, BOARD_WIDTH/2 - 8);
  printf("Press " P1COLOR "'r'" RESET " to " P1COLOR "R" RESET "estart");
  
  moveTo(BOARD_HEIGHT/2 + 2, BOARD_WIDTH/2 - 7);
  printf("Press " P2COLOR "'q'" RESET " to " P2COLOR "Q" RESET "uit");
  
  pthread_mutex_unlock(&mutex);
}

int main() {
  hidecursor();
  char input;
  pthread_t gameLoopThread, keyboardInputThread;

  while(1) {
    initializeBoard();
    moveTo(BOARD_HEIGHT/2 + 3, BOARD_WIDTH/2 - 3); puts("PRESS @NY KEY");
    moveTo(BOARD_HEIGHT/2 + 4, BOARD_WIDTH/2);     puts("TO START");
    getchar_();

    pthread_create(&gameLoopThread,      NULL, keyboardInputs, NULL);
    pthread_create(&keyboardInputThread, NULL, gameLoop,       NULL);
    pthread_join(keyboardInputThread, NULL);
    pthread_join(gameLoopThread,      NULL);

    while( (input = getchar_()) != 'q' && input != 'r' ); // q, r 입력 대기
    terminate = 0;
    if(input == 'q') break;
  }
  
  /* 이 밑으로 엔드카드 */
  
  // 기록을 저장할지 물어봄
  system("clear");
  showcursor();
  printf("Submit your scores? [y/n] ");
  char x;
  while((x = getchar_()) != 'y' && x != 'n');
  puts("");
  if(x == 'y') {
    getPlayerNames();
    printf("%s %d %s %d\n", player1.name, player1.score, player2.name, player2.score);
    
      // 기록를 저장
    saveRecords();

  }
  // 이후 recordsCount를 통해 기록 개수 파악 후 출력
  printf("There are %d records.\n\n", recordsCount());
  retrieveRecords();



  moveTo(BOARD_HEIGHT+3, 1); // echo 출력 조정용
  showcursor();
  return 0;
}
