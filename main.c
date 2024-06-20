#include <stdbool.h>
#include <stdio.h>

#include "extCmdManagement.c"

bool UserEXIT = false;
char user_choice[100];
char PROMPT[] = "s4sh3ll#";
char *internCommand[] = {"exit", "help"};

//
// Function that verify if the cmd is not an external cmd.
//
bool isInternCmd(char *user_choice){
  int intern_cmd_list_size = sizeof(internCommand) / sizeof(internCommand[0]);

  for (int i = 0; i < intern_cmd_list_size; i++) {
    if (strcmp(user_choice, internCommand[i]) == 0) {
      return true;
    }
  }
  return false;
}

//
// Main function 
//
int main() { 
  
  while (!UserEXIT) {
    
    printf("%s", PROMPT);

    scanf("%99s", user_choice);
   
    if (isInternCmd(user_choice)) {
      
      if (strcmp(user_choice, "exit") == 0) {
        UserEXIT = true;
        return 0;
      }
    } else {
      execExternalCommand(user_choice);
    }
  }
  return 0;
}
