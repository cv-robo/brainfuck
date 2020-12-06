#include <stdio.h>

#include "brainfuck.h"

int main(void) {
    char program[1024];
    fgets(program, 1024, stdin);
    bf_run(program, 1024, 1024);
    return 0;
}
