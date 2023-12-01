#include "../headers/records.h"

// records.txt�� main.c�� ���� ���丮�� �����Ƿ� ../ �� ������ �ȵȴ�

// game.c
extern player player1, player2;

void getPlayerNames() {
  printf("Enter player 1 name: ");
  scanf("%s", player1.name);
  printf("Enter player 2 name: ");
  scanf("%s", player2.name);
}

void saveRecords() {
  FILE* fp = fopen("records.txt", "a");
  if(!fp) exit(1);
  
  fprintf(fp, "%s %d %s %d\n",  player1.name, player1.score,
                                player2.name, player2.score);
  
  fclose(fp);
}

// �� ���� ����� �ִ��� Ȯ��
int recordsCount() {
  FILE* fp = fopen("records.txt", "r");
  if(!fp) exit(1);
  
  char buffer[256];
  int count = 0;
  while(fgets(buffer, 256, fp)) count++;

  fclose(fp);  
  return count;
}

// ��ϵ��� malloc �� �迭�� ���� �о��
void retrieveRecords(gameResult* list, int count) {
  FILE* fp = fopen("records.txt", "r");
  if(!fp) exit(1);
  
  for(int i = 0; i < count; i++)
    fscanf(fp, "%s %d %s %d\n", list[i].p1.name, &list[i].p1.score, list[i].p2.name, &list[i].p2.score);
  
  fclose(fp);
}

// ������� �ӽ� å��, ���� ���� ����
void showRecords(gameResult* list, int count) {
  for(int i = 0; i < count; i++)
    printf("%s : %d vs %d : %s\n",  list[i].p1.name,  list[i].p1.score,
                                    list[i].p2.score, list[i].p2.name);
}
