/*
    Author: SyntaxSculptor
    Date: 4/27/26
    File: main.c
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./xdump <file_name>");
        return EXIT_SUCCESS;
    }

    char *file_name = argv[1];
    FILE *file_ptr = fopen(file_name, "rb");

    if (file_ptr == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    int file_char = fgetc(file_ptr);
    long offset = 0;

    while (file_char != EOF) {
        unsigned char byte = (unsigned char) file_char;
        
        printf("%08lx: %02x\n", offset, byte);
        file_char = fgetc(file_ptr);
        offset++;
    }

    fclose(file_ptr);

    return EXIT_SUCCESS;
}