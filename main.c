#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024

void edit_line(char* buffer, int current_line) {
    for(int i=0; i < current_line; i++) {
        buffer = strchr(buffer, '\n') + 1;
    }

    char* line_end = strchr(buffer, '\n');
    char saved[1024] = {0};
    strcpy(saved, line_end);
    scanf("%s", buffer);
    strcpy(buffer + strlen(buffer), saved);
}

void read_file_content(const char* filename, char* buffer) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    fread(buffer, MAX_BUFFER_SIZE, 1, file);
    fclose(file);
}

void write_file_content(const char* filename, const char* buffer) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    fwrite(buffer, strlen(buffer), 1, file);
    fclose(file);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char buffer[MAX_BUFFER_SIZE] = {0};
    read_file_content(argv[1], buffer);

    printf("Contents:\n%s\n", buffer);

    int current_line = 0;
    printf("Enter line number to edit: ");
    scanf("%d", &current_line);

    edit_line(buffer, current_line);

    write_file_content(argv[1], buffer);

    return 0;
}