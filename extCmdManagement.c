#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sashellrc.c"

int execExternalCommand(char *user_choice) {

  getPathList();

  char fullPath[150];

  for (int i = 0; i < 10 && pathList[i] != NULL; i++) {
    DIR *dr = opendir(pathList[i]);
    if (dr == NULL) {
      perror("Failed to open directory");
      continue;
    }

    struct dirent *de;
    while ((de = readdir(dr)) != NULL) {
      if (strcmp(user_choice, de->d_name) == 0) {
        snprintf(fullPath, sizeof(fullPath), "%s/%s", pathList[i], user_choice);
        printf("Found: %s\n", fullPath);

        pid_t pid = fork();
        if (pid == 0) {
          char *args[] = {user_choice, NULL};
          execve(fullPath, args, NULL);
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
