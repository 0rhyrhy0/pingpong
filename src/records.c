#include "../headers/records.h"

// records.txt는 main.c와 같은 디렉토리에 있으므로 ../ 가 있으면 안된다

// game.c
extern player player1, player2;

void getPlayerNames() {
  printf(P1COLOR "Enter player 1 name: ");
  scanf("%s", player1.name);
  printf(P2COLOR "Enter player 2 name: ");
  scanf("%s", player2.name);
  printf(RESET);
}

void saveRecords() {
  time_t now;
  time(&now);

  struct tm *timeinfo;
  timeinfo = localtime(&now);

  FILE* fp = fopen("records.txt", "a");
  if(!fp) exit(1);
  
  fprintf(fp, "%d %d %d %d %d %s %d %s %d\n",
              timeinfo->tm_year + 1900,  // 년
              timeinfo->tm_mon + 1,      // 월 (0-11이므로 1을 더함)
              timeinfo->tm_mday,         // 일
              timeinfo->tm_hour,         // 시
              timeinfo->tm_min,          // 분
              player1.name, player1.score,
              player2.name, player2.score);
  
  fclose(fp);
}

// 몇 개의 기록이 있는지 확인
int recordsCount() {
  FILE* fp = fopen("records.txt", "r");
  if(!fp) exit(1);
  
  char buffer[256];
  int count = 0;
  while(fgets(buffer, 256, fp)) count++;

  fclose(fp);  
  return count;
}

// 기록들을 malloc 한 배열을 통해 읽어옴
void retrieveRecords(gameResult* list, int count) {
  FILE* fp = fopen("records.txt", "r");
  if(!fp) exit(1);
  
  for(int i = 0; i < count; i++)
    fscanf(fp,
      "%d %d %d %d %d %s %d %s %d\n",
      &list[i].timeinfo[0], &list[i].timeinfo[1], &list[i].timeinfo[2],
      &list[i].timeinfo[3], &list[i].timeinfo[4], 
      list[i].p1.name, &list[i].p1.score, list[i].p2.name, &list[i].p2.score
    );
  
  fclose(fp);
}

// 사이즈는 임시 책정, 추후 변경 가능
void showRecords(gameResult* list, int count) {
  for(int i = 0; i < count; i++)
    printf("[%04d%02d%02d %02d:%02d] %s : %d vs %d : %s\n",
            list[i].timeinfo[0], list[i].timeinfo[1], list[i].timeinfo[2],
            list[i].timeinfo[3], list[i].timeinfo[4], 
            list[i].p1.name,  list[i].p1.score,
            list[i].p2.score, list[i].p2.name);
}
