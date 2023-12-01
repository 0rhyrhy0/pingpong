#include "headers.h"

int notmain() {
  hidecursor();

  gameStart();
  
  /* 이 밑으로 엔드카드 */
  
  // 기록을 저장할지 물어봄
  system("clear");
  showcursor();
  printf("Submit your scores? [y/n] ");
  char x;
  while((x = getchar_()) != 'y' && x != 'n');
  if(x == 'y') {
    puts("");
    getPlayerNames();
    saveRecords();
  }
  
  // 이후 recordsCount를 통해 기록 개수 파악 후 출력
  int count = recordsCount();
  gameResult *results = malloc(sizeof(gameResult) * count);
  if(count) {
    puts("");
    retrieveRecords(results, count);
    
    // system("clear");
    showRecords(results, count);
  }
  return 0;
}

int main()
{
  hidecursor();
  displayMenu(0, 2);
  
  puts("\033[0m");
  system("clear");
  showcursor();
  return 0;
}
