#include "brainfuck.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bf_run(char *program, size_t stack_size, size_t memory_size) {
    size_t program_size = strlen(program);
    char *stack = (char *)calloc(stack_size, sizeof(char));
    char *memory = (char *)calloc(memory_size, sizeof(char));
    if (!(stack && memory)) {
        printf("memory allocation failed.\n");
        exit(-1);
    }
    size_t pc = 0, sp = 0, ptr = memory_size / 2;
    for (; pc < program_size; pc++) {
        if (!sp && program[pc] == ']') {
            printf("sp is zero.\n");
            break;
        }
        switch (program[pc]) {
            case '>':
                ptr++;
                break;
            case '<':
                ptr--;
                break;
            case '+':
                memory[ptr]++;
                break;
            case '-':
                memory[ptr]--;
                break;
            case ',':
                memory[ptr] = getchar();
                getchar();
                break;
            case '.':
                putchar(memory[ptr]);
                break;
            case '[':
                stack[sp] = pc;
                sp++;
                break;
            case ']':
                pc = memory[ptr] ? stack[sp - 1] : pc;
                sp -= !memory[ptr];
                break;
        }
        if (ptr < 0 || ptr >= memory_size) {
            printf("pointer out of range.\n");
            break;
        }
        if (sp >= program_size) {
            printf("sp out of range.\n");
            break;
        }
    }
    putchar('\n');
}
