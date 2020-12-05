#include <stdio.h>

#include "brainfuck.h"

int main(void) {
    char program[1024];
    scanf("%s", program);
    getchar();
    bf_run(program, 1024);
    return 0;
}
