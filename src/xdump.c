/*
    Author: SyntaxSculptor
    Date: 4/27/26
    File: xdump.c
*/

#include "xdump.h"
#include <stdio.h>
#include <stdlib.h>


#define BYTES_PER_LINE 16

int isPrintableChar(char c) {
    return c >= 32 && c <= 126;
}

void printByteBuffer(unsigned char buff[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%02x ", buff[i]);
    }
}

void printAsciiBuffer(unsigned char buff[], int n) {
    printf("|");
    for (int i = 0; i < n; i++) {
        if (isPrintableChar(buff[i])) {
            putc(buff[i], stdout);
        }
        else {
            printf(".");
        }
    }
    
    printf("|\n");
}

void dumpFile(const char* file_name) {
    FILE *file_ptr = fopen(file_name, "rb");

    if (file_ptr == NULL) {
        perror("Failed to open file");
        return;
    }

    int file_char = fgetc(file_ptr);
    long offset = 0;
    int current_line_byte = 0;
    unsigned char ascii_buffer[BYTES_PER_LINE];

    while (file_char != EOF) {
        unsigned char byte = (unsigned char) file_char;
        int ascii_buffer_idx = current_line_byte % BYTES_PER_LINE;

        if (current_line_byte == 0) {
            printf("%08lx: ", offset);
        }
        
        current_line_byte++;

        ascii_buffer[ascii_buffer_idx] = byte;

        if (current_line_byte == BYTES_PER_LINE) {
            current_line_byte = 0;
            printByteBuffer(ascii_buffer, BYTES_PER_LINE);
            printAsciiBuffer(ascii_buffer, BYTES_PER_LINE);
        }

        file_char = fgetc(file_ptr);
        offset++;
    }

    // Print remaining bytes and pad them.
    if (current_line_byte > 0) {
        printByteBuffer(ascii_buffer, current_line_byte);

        for (int i = 0; i < BYTES_PER_LINE - current_line_byte; i++) {
            printf("   ");
        }

        printAsciiBuffer(ascii_buffer, current_line_byte);
    }

    fclose(file_ptr);
}