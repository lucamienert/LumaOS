#ifndef LUMAOS_VM_H_
#define LUMAOS_VM_H_

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    PSH,
    POP,

    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    PRT,
    NOP,
    HLT
} instructions_t;

uint8_t fetch(int8_t program[]);
void eval(uint8_t instruction);
void run(int8_t program[]);

#endif