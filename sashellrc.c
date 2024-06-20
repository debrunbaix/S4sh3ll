#include <string.h>
#include <stdio.h>

FILE *sashellrc_file;
char sashellrc[50];
char *pathList[10];

//
// function to get the content of .sashellrc
//
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

//
// Function to parse sashellrc in list of path
//
void getPathList() {
  
  getSashellrcContent();
  
  int pathCount = 0;
  char *token = strtok(sashellrc, ":");
  
  while (token != NULL && pathCount < 10) {
    pathList[pathCount++] = token;
    token = strtok(NULL, ":");
  }
}
