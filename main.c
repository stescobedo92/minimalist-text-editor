#include <stdio.h>

void main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "r");
    char buffer[1024] = {0};
    fread(buffer, 1024, 1, file);
    fclose(file);
}