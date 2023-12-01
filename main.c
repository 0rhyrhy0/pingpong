#include "headers.h"

int notmain() {
  hidecursor();

  gameStart();
  
  /* �� ������ ����ī�� */
  
  // ����� �������� ���
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
  
  // ���� recordsCount�� ���� ��� ���� �ľ� �� ���
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
