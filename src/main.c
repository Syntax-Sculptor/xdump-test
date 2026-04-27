/*
    Author: SyntaxSculptor
    Date: 4/27/26
    File: main.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "xdump.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./xdump <file_name>");
        return EXIT_FAILURE;
    }

    char *file_name = argv[1];
    dumpFile(file_name);

    return EXIT_SUCCESS;
}