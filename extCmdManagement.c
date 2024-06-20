#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *pathList[10];
FILE *sashellrc_file;
char sashellrc[50];

void getSashellrcContent() {
  
  sashellrc_file = fopen(".sashellrc", "r");
  
  if (sashellrc_file == NULL) {
    perror("Failed to open .sashellrc");
    exit(EXIT_FAILURE);
  }
  if (fgets(sashellrc, sizeof(sashellrc), sashellrc_file) == NULL) {
    perror("Failed to read from .sashellrc");
    fclose(sashellrc_file);
    exit(EXIT_FAILURE);
  }
  fclose(sashellrc_file);

  size_t len = strlen(sashellrc);
  if (len > 0 && sashellrc[len - 1] == '\n') {
    sashellrc[len - 1] = '\0';
  }
}

void getPathList() {
  
  getSashellrcContent();
  
  int pathCount = 0;
  char *token = strtok(sashellrc, ":");
  
  while (token != NULL && pathCount < 10) {
    pathList[pathCount++] = token;
    token = strtok(NULL, ":");
  }
}

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