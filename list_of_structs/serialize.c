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
    FILE *fp = fopen(FILE_USED, "w");
    if (fp == NULL) {
        fprintf(stderr, "[ERROR]: Opening file failed.\n");
    }

    Todo **data = calloc(N, sizeof(Todo));

    for (size_t i = 0; i < N; i++) {
        int tmp;
        size_t length;

        printf("[INFO]: Filling Todo[%ld]\n", i);

        data[i] = malloc(sizeof(Todo));
        data[i]->id = (int)malloc(sizeof(int));
        data[i]->done = malloc(sizeof(bool));
        data[i]->desc = malloc(INPUT_BUFFER * sizeof(char));
        printf("         ID (int): ");
        scanf("%d", &data[i]->id);
        printf("      Done (bool): ");
        scanf("%d", &tmp);
        if (tmp == 1) {
            data[i]->done = true;
        } else {
            data[i]->done = false;
        }

        getchar(); // Consume the newline (\n)
        printf("The task (char *): ");
        getline(&data[i]->desc, &length, stdin);
        int size = (int)strlen(data[i]->desc);
        data[i]->desc[size-1] = '\0';

        fprintf(fp, ";%d;%d;%s\n", data[i]->id, data[i]->done, data[i]->desc);
    }

    if (errno > 0) {
        printf(strerror(errno));
    }

    free(data);
    fclose(fp);
    return 0;
}
