#ifndef CODER_H
#define CODER_H

#include <inttypes.h>
#include <stdio.h>

typedef uint8_t byte;

enum {
    MaxCodeLength = 4,
};

typedef struct {
    byte code[MaxCodeLength];
    size_t length;
} CodeUnit;

int encode(uint32_t code_point, CodeUnit *code_units);
uint32_t decode(const CodeUnit *code_unit);
int read_next_code_unit(FILE *in, CodeUnit *code_units);
int write_code_unit(FILE *out, const CodeUnit *code_unit);

void print_code_unit(const CodeUnit *unit);

#endif