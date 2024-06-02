#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUT_FILE "./tasks"
#define READ_BUFFER 256
#define INPUT_BUFFER 128
#define N 3

typedef struct {
    int id;
    bool done;
    char *desc;
} Todo;

int main(void) {
    FILE *fp = fopen(OUT_FILE, "r");
    if (fp == NULL) {
        fprintf(stderr, "[ERROR]: Opening file failed.\n");
    }

    char *line = malloc(INPUT_BUFFER * sizeof(char));
    if (line == NULL) {
        return 1;
    }
    size_t line_len;

    Todo **data = calloc(N, sizeof(Todo));
    if (!data) {
        return 1;
    }

    for (size_t i = 0; i < N; i++) {
        int id;
        int tmp;
        char desc[INPUT_BUFFER];

        data[i] = malloc(sizeof(Todo));
        if (!data[i]) {
            return 1;
        }
        
        data[i]->id = (int)malloc(sizeof(int));
        if (!data[i]->id) {
            return 1;
        }
        data[i]->done = malloc(sizeof(bool));
        if (!data[i]->done) {
            return 1;
        }

        data[i]->desc = malloc(INPUT_BUFFER * sizeof(char));
        if (!data[i]->desc) {
            return 1;
        }

        int j = 0;
        while (getline(&line, &line_len, fp) != EOF) {
            printf("[INFO]: Deserializing Todo data[%d]\n", j);
            sscanf(line, ";%d;%d;%[^\n]", &id, &tmp, desc);
            data[i]->id = id;
            data[i]->done = tmp == 1 ? true : false;
            data[i]->desc = desc;

            printf("  ID: %d\nDone: %d\nDesc: %s\n\n",
                    data[i]->id, data[i]->done, data[i]->desc);
            j++;
        }
    }
    
    if (errno > 0) {
        printf(strerror(errno));
    }

    if (feof(fp)) {
        fprintf(stderr, "[INFO] Output file \"%s\" end reached.\n", OUT_FILE);
    }

    free(data);
    fclose(fp);
    return 0;
}
