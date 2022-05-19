#include <ds/vm.h>

uint8_t instruction_pointer = 0;
int8_t stack_pointer = -1;
uint8_t stack[STACK_SIZE];
bool running = false;

uint8_t fetch(int8_t program[])
{
    return program[instruction_pointer];
}

void eval(uint8_t instruction)
{
    switch(instruction)
    {
        case HLT: 
        {
            running = false;
            break;
        }
        case PSH: 
        {
            stack_pointer++;
            stack[stack_pointer] = program[++instruction_pointer];
            break;
        }
        case POP: 
        {
            stack[stack_pointer--];
            break;
        }
        case PRT: 
        {
            int16_t stack_value = stack[stack_pointer];
            printf("VM > %d\n", stack_value);
            break;
        }
        case ADD: 
        {
            int16_t a = stack[stack_pointer--];
            int16_t b = stack[stack_pointer--];

            int16_t result = b + a;

            stack_pointer++;
            stack[stack_pointer] = result;
            break;
        }
        case SUB: 
        {
            int16_t a = stack[stack_pointer--];
            int16_t b = stack[stack_pointer--];

            int16_t result = b - a;

            stack_pointer++;
            stack[stack_pointer] = result;
            break;
        }
        case MUL: 
        {
            int16_t a = stack[stack_pointer--];
            int16_t b = stack[stack_pointer--];

            int16_t result = a * b;

            stack_pointer++;
            stack[stack_pointer] = result;
            break;
        }
        case DIV: 
        {
            int16_t a = stack[stack_pointer--];
            int16_t b = stack[stack_pointer--];

            int16_t result = b / a;

            stack_pointer++;
            stack[stack_pointer] = result;
            break;
        }
        case MOD: 
        {
            int16_t a = stack[stack_pointer--];
            int16_t b = stack[stack_pointer--];

            int16_t result = b % a;

            stack_pointer++;
            stack[stack_pointer] = result;
            break;
        }
        case NOP: break;
        default: {
            printf("An error occured: Unknown instruction (%d)", instruction);
            break;
        }
    }
}

void run(int8_t program[])
{
    running = true;
    while(running)
    {
        eval(fetch(program));
        ++instruction_pointer;
    }
}