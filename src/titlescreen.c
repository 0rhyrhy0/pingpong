#include "../headers/titlescreen.h"

void displayMenu(int option, int color) // color : 0 ~ 3 (red , green, yellow, blue)
{
  printf("\033[%dm", 31 + color);
  system("clear");
  char* arrows[] = {"  ", "->"};
  char* options[] = {"1. Game Start", "2. View Records", "3. Exit Game"};
  
  moveTo(1, 1);
  { // ascii art title
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
  
  moveTo(12, 3); puts(arrows[option == 0]);
  moveTo(13, 3); puts(arrows[option == 1]);
  moveTo(14, 3); puts(arrows[option == 2]);
  
  moveTo(12, 10); printf("\033[%dm%s", 33, options[0]);
  moveTo(13, 10); printf("\033[%dm%s", 34, options[1]);
  moveTo(14, 10); printf("\033[%dm%s", 31, options[2]);
  
  moveTo(18, 0);
  
  // ����Ű �Է¿� ���� ó��(��� ������?)
  switch(getInput(getchar_())) {
    case NONE : return;
    
    case UP_1P : case UP_2P :
      displayMenu(MAX(option - 1, 0), color);
      break;
    
    case DOWN_1P : case DOWN_2P :
      displayMenu(MIN(option + 1, 2), color);
      break;
      
    case RIGHT_1P : case RIGHT_2P :
      displayMenu(option, (color + 1) % 4);
      break;
      
    case LEFT_1P : case LEFT_2P :
      displayMenu(option, (color + 3) % 4);
      break;
      
    case ENTER :
      printf("\033[0m");
      switch(option) {
        case 0 :
          gameStart();
          displayMenu(option, color);
          break;
        // case 1 : viewRecords(); break;
        // case 2 : exitGame(); break;
      }
      break;
  }
  printf("\033[0m");
}

