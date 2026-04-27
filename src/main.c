/*
    Author: SyntaxSculptor
    Date: 4/27/26
    File: main.c
*/

#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 100

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./xdump <file_name>");
        return EXIT_SUCCESS;
    }

    char buffer[BUFFER_SIZE];

    char *file_name = argv[1];
    FILE *file_ptr = fopen(file_name, "r");

    while (fgets(buffer, BUFFER_SIZE, file_ptr)) {
        printf("%s", buffer);
    }

    fclose(file_ptr);

    return EXIT_SUCCESS;
}