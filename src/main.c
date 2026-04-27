/*
    Author: SyntaxSculptor
    Date: 4/27/26
    File: main.c
*/

#include <stdlib.h>
#include <stdio.h>

#define BYTES_PER_LINE 16

int isPrintableChar(char c) {
    return c >= 32 && c <= 126;
}

void printAsciiBuffer(char buff[], int n) {
    printf("| ");
    for (int i = 0; i < n; i++) {
        if (isPrintableChar(buff[i])) {
            putc(buff[i], stdout);
        }
        else {
            printf(".");
        }
    }
    
    printf(" |\n");
}

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
    char ascii_buffer[BYTES_PER_LINE];

    while (file_char != EOF) {
        unsigned char byte = (unsigned char) file_char;
        int ascii_buffer_idx = bytes_printed % BYTES_PER_LINE;

        if (bytes_printed % BYTES_PER_LINE == 0) {
            printf("%08lx: ", offset);
        }

        printf("%02x ", byte);
        bytes_printed++;

        ascii_buffer[ascii_buffer_idx] = byte;

        if (bytes_printed % BYTES_PER_LINE == 0) {
            printAsciiBuffer(ascii_buffer, BYTES_PER_LINE);
        }

        file_char = fgetc(file_ptr);
        offset++;
    }

    if (bytes_printed % BYTES_PER_LINE > 0) {
        printAsciiBuffer(ascii_buffer, bytes_printed % BYTES_PER_LINE);
    }

    fclose(file_ptr);

    return EXIT_SUCCESS;
}