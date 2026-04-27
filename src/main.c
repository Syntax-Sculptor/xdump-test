/*
    Author: SyntaxSculptor
    Date: 4/27/26
    File: main.c
*/

#include <stdlib.h>
#include <stdio.h>

const int BYTES_PER_LINE = 16;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./xdump <file_name>");
        return EXIT_FAILURE;
    }

    char *file_name = argv[1];
    FILE *file_ptr = fopen(file_name, "rb");

    if (file_ptr == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    int file_char = fgetc(file_ptr);
    long offset = 0;
    int bytes_printed = 0;

    while (file_char != EOF) {
        unsigned char byte = (unsigned char) file_char;

        if (bytes_printed % BYTES_PER_LINE == 0) {
            printf("%08lx: ", offset);
        }

        printf("%02x ", byte);
        bytes_printed++;

        if (bytes_printed % BYTES_PER_LINE == 0) {
            printf("\n");
        }

        file_char = fgetc(file_ptr);
        offset++;
    }

    if (bytes_printed % BYTES_PER_LINE > 0) {
        printf("\n");
    }

    fclose(file_ptr);

    return EXIT_SUCCESS;
}