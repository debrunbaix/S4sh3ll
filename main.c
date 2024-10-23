/**
 * \file		   main.c
 * \brief		   Main file that start all the program.
 * \author		   Debrunbaix
 */

#include <stdbool.h>
#include <stdio.h>

#include "extCmdManagement.c"
#include "parser.c"

bool user_exit = false;                        /* Var to stop the program if input is the xommand exit */
char user_input[100];                          /* Variable containing user_input */
char user_prompt[] = "s4sh3ll#";               /* Const that contain the prompt string */
char* intern_cmd[] = {"exit"};                 /* List of intern command */

/**
 * \brief          Function that verify if user's input is an intern command or not
 * \param[in]      user_input = Pointer to the user's input
 * \return         Boolean True if it is intern command
 */
bool 
is_intern_cmd(char* user_input){
	int intern_cmd_list_size = sizeof(intern_cmd) / sizeof(intern_cmd[0]);

  	for (int i = 0; i < intern_cmd_list_size; i++) {
    	if (strcmp(user_input, intern_cmd[i]) == 0) {
      		return true;
    	}
  	}
  	return false;
}

/**
 * \brief		   Function to get the user input and delete the "\n" char
 * \note		   It return nothing because it change the local var directly
 */
void 
get_user_cmd(){
  	fgets(user_input, 100, stdin);
  	size_t len = strlen(user_input);		   /* lenght of the user's input */
  
  	if (len > 0 && user_input[len - 1] == '\n') {
    	user_input[len - 1] = '\0';
  	}
}

int 
main() { 
  
  	while (!user_exit) {
    
    	printf("%s", user_prompt);
    	get_user_cmd();
    	parse_args_cmd(user_input);

    	if (is_intern_cmd(user_input)) {

      		if (strcmp(user_input, "exit") == 0) {
        		user_exit = true;			   /* Changing the exit to quit the program */
        		return 0;
      		}
    	} else {
      		exec_ext_cmd(user_input);
    	}
  	}
  	return 0;
}