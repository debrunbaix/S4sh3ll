#include <stdbool.h>
#include <stdio.h>

#include "extCmdManagement.c"
#include "parser.c"

bool UserEXIT = false;
char user_input[100];
char PROMPT[] = "s4sh3ll#";
char *internCommand[] = {"exit"};

//
// Function that verify if the cmd is not an external cmd.
//
bool isInternCmd(char *user_input){
  int intern_cmd_list_size = sizeof(internCommand) / sizeof(internCommand[0]);

  for (int i = 0; i < intern_cmd_list_size; i++) {
    if (strcmp(user_input, internCommand[i]) == 0) {
      return true;
    }
  }
  return false;
}

//
// Function to get the user input and deldte \n
//
void get_user_cmd(){
  fgets(user_input, 100, stdin);
  
  size_t len = strlen(user_input);
  
  if (len > 0 && user_input[len - 1] == '\n') {
    user_input[len - 1] = '\0';
  }
}

//
// Main function 
//
int main() { 
  
  while (!UserEXIT) {
    
    printf("%s", PROMPT);
    get_user_cmd();
    parseArgs(user_input);

    if (isInternCmd(user_input)) {

      if (strcmp(user_input, "exit") == 0) {
        UserEXIT = true;
        return 0;
      }
    } else {
      execExternalCommand(user_input);
    }
  }
  return 0;
}
