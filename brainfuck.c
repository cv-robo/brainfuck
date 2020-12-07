#include "brainfuck.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bf_run(char *program, size_t memory_size) {
    size_t program_size = strlen(program);
    size_t *stack = (char *)malloc(program_size * sizeof(size_t));
    size_t *jmp_table = (char *)malloc(program_size * sizeof(size_t));
    char *memory = (char *)calloc(memory_size, sizeof(char));
    if (!(stack && jmp_table && memory)) {
        printf("memory allocation failed.\n");
        exit(-1);
    }
    size_t pc = 0, sp = 0, ptr = memory_size / 2;
    for (pc = 0; pc < program_size; pc++) {
        if (!sp && program[pc] == ']') {
            printf("sp is zero.\n");
            break;
        }
        switch (program[pc]) {
            case '[':
                stack[sp] = pc;
                sp++;
                break;
            case ']':
                sp--;
                jmp_table[pc] = stack[sp];
                jmp_table[stack[sp]] = pc;
                break;
        }
    }
    for (pc = 0; pc < program_size; pc++) {
        if (ptr < 0 || ptr >= memory_size) {
            printf("pointer out of range.\n");
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
                break;
            case '.':
                putchar(memory[ptr]);
                break;
            case '[':
                pc = memory[ptr] ? pc : jmp_table[pc];
                break;
            case ']':
                pc = memory[ptr] ? jmp_table[pc] : pc;
                break;
        }
    }
    free(stack);
    free(jmp_table);
    free(memory);
}
