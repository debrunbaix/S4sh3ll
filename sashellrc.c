/**
 * \file           sashellrc.c
 * \brief          File where fonction to interact with a shellrc like file
 * \author         Debrunbaix
 */

#include <string.h>
#include <stdio.h>

FILE* sashellrc_file;                          /* File type to get the file director of sashellrc */
char* path_list[10];                           /* Variable to contain path list */
char sashellrc[50];                            /* Variable to contain sashellrc */

/**
 * \brief          get the content of .sashellrc file
 * \note           chancge the content of sashellrc_file locally
 */
void 
get_sashellrc_content() {

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

/**
 * \brief          Parse sashellrc file in a list of path
 */
void 
get_path_list() {
    get_sashellrc_content();

    int path_count = 0;
    char* token = strtok(sashellrc, ":");

    while (token != NULL && path_count < 10) {
        path_list[path_count++] = token;
        token = strtok(NULL, ":");
    }
}
