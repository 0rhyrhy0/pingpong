#include "../headers/titlescreen.h"

void displayMenu(int option, int color) // color : 0 ~ 3 (red , green, yellow, blue)
{
  printf("\033[%dm", 31 + color);
  system("clear");
  char* arrows[] = {"  ", "->"};
  char* options[] = {"1. Game Start", "2. View Records", "3. Exit Game"};
  
  ascii();
  
  moveTo(12, 3); puts(arrows[option == 0]);
  moveTo(13, 3); puts(arrows[option == 1]);
  moveTo(14, 3); puts(arrows[option == 2]);
  
  moveTo(12, 10 + 4 * (option == 0)); printf("\033[%dm%s", 33, options[0]);
  moveTo(13, 10 + 4 * (option == 1)); printf("\033[%dm%s", 34, options[1]);
  moveTo(14, 10 + 4 * (option == 2)); printf("\033[%dm%s", 31, options[2]);
  
  moveTo(18, 0);
  
  // 방향키 입력에 따른 처리(재귀)
  while(1) switch(getInput(getchar_())) {
    case NONE : break;
    
    case UP_1P : case UP_2P :
      displayMenu(MAX(option - 1, 0), color);
      return;
    
    case DOWN_1P : case DOWN_2P :
      displayMenu(MIN(option + 1, 2), color);
      return;
      
    case RIGHT_1P : case RIGHT_2P :
      displayMenu(option, (color + 1) % 4);
      return;
      
    case LEFT_1P : case LEFT_2P :
      displayMenu(option, (color + 3) % 4);
      return;
      
    case ENTER :
      printf("\033[0m");
      switch(option) {
        case 0 :
          system("clear");
          puts(TITLECOLOR);
          ascii();
          showcursor(); getPlayerNames(); hidecursor(); getchar_();
          gameStart();
          saveRecords();


          displayMenu(option, color);
          return;
        case 1 :
          int count = recordsCount();
          if(count) {
            gameResult *results = malloc(sizeof(gameResult) * count);
            retrieveRecords(results, count);
            
            system("clear");
            showRecords(results, count); // 수정 필요
            getchar_();
          }

          displayMenu(option, color);
          return;
        // case 2 : exitGame(); break;
      }
      return;
  }
}
