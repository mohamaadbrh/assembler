#ifndef TABLE_H
#define TABLE_H

#include "general.h"

typedef struct Symbol
{
    char label[LABEL_LENGTH];
    int32_t isUsed;
    int32_t pc;
}
Symbol;

int insertSymbol(Symbol table[], Symbol value);
int findByLabel(Symbol table[], const char *label);

#endif