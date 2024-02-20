#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_USED "./tasks"
#define INPUT_BUFFER 128
#define N 3

typedef struct {
    int id;
    bool done;
    char *desc;
} Todo;

int main(void) {
    FILE *fp = fopen(FILE_USED, "r");
    if (fp == NULL) {
        fprintf(stderr, "[ERROR]: Opening file failed.\n");
    }

    char *line = malloc(INPUT_BUFFER * sizeof(char));
    size_t line_len;

    Todo **data = calloc(N, sizeof(Todo));

    for (size_t i = 0; i < N; i++) {
        int j = 0;
        int id;
        int done_tmp;
        char desc[INPUT_BUFFER];

        data[i] = malloc(sizeof(Todo));
        data[i]->id = (int)malloc(sizeof(int));
        data[i]->done = malloc(sizeof(bool));
        data[i]->desc = malloc(INPUT_BUFFER * sizeof(char));

        while (getline(&line, &line_len, fp) != EOF) {
            printf("[INFO]: Reading Todo[%d]\n", j);
            sscanf(line, ";%d;%d;%[^\n]", &id, &done_tmp, desc);
            data[i]->id = id;
            if (done_tmp == 1) {
                data[i]->done = true;
            } else {
                data[i]->done = false;
            }
            data[i]->desc = desc;
            printf("%d;%d;%s\n", data[i]->id, data[i]->done, data[i]->desc);
            j++;
        }
    }
    
    if (errno > 0) {
        printf(strerror(errno));
    }
    if (feof(fp)) {
        fprintf(stderr, "[INFO] Todo data file end reached.\n");
    }

    free(data);
    fclose(fp);
    return 0;
}
