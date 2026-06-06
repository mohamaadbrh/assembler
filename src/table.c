#include "table.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int getLabelHash(const char *label, size_t capacity)
{
    int result = 0;
    for (int counter = 0; counter < strlen(label); ++counter)
    {
        result = result * 7 + label[counter];
    }
    return result % capacity;
}

int insertSymbol(Symbol table[], Symbol value)
{
    int position = getLabelHash(value.label, TOTAL_CAPACITY);
    while(table[position].isUsed == SYMBOL_USED)
    {
        if(!strncmp(table[position].label, value.label, LABEL_LENGTH))
        {
            return INSERT_FAILED;
        }
        position = (position + 1) % TOTAL_CAPACITY;
    }
    value.isUsed = SYMBOL_USED;
    table[position] = value;
    return position;
}

int findByLabel(Symbol table[], const char *label)
{
    int position = getLabelHash(label, TOTAL_CAPACITY);
    while(table[position].isUsed == SYMBOL_USED)
    {
        if(!strncmp(table[position].label, label, LABEL_LENGTH))
        {
            return position;
        }
        position = (position + 1) % TOTAL_CAPACITY;
    }
    return NOT_FOUND;
}