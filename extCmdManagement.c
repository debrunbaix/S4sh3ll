/**
 * \file		   extCmdManagement.c
 * \brief		   To manage the execution of external command.
 * \author		 Debrunbaix
 */

#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sashellrc.c"

int 
exec_ext_cmd(char* user_choice) {
  /*
    Function to execute command that are in the PATH variable.
  */
  get_path_list();

  char full_path[150];

  for (int i = 0; i < 10 && path_list[i] != NULL; i++) {
    DIR* dr = opendir(path_list[i]);
    if (dr == NULL) {
      perror("Failed to open directory");
      continue;
    }

    struct dirent* de;
    while ((de = readdir(dr)) != NULL) {
      if (strcmp(user_choice, de->d_name) == 0) {
        snprintf(full_path, sizeof(full_path), "%s/%s", path_list[i], user_choice);
        printf("Found: %s\n", full_path);

        pid_t pid = fork();
        if (pid == 0) {
          char *args[] = {user_choice, NULL};
          execve(full_path, args, NULL);
          perror("execve failed");
          exit(EXIT_FAILURE);
        } else if (pid > 0) {
          int status;
          waitpid(pid, &status, 0);
        } else {
          perror("fork failed");
          return -1;
        }

        closedir(dr);
        return 0;
      }
    }

    closedir(dr);
  }
  return -1;
}
