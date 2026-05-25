#include "table.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

SymbolTable createSymbolTable(size_t capacity)
{
    SymbolTable result;
    result.capacity = 0;
    result.count = 0;

    result.symbols = (Symbol*) malloc(capacity * sizeof(Symbol));
    if (result.symbols == NULL)
    {
        return result;
    }
    result.capacity = capacity;

    return result;
}

int getLabelHash(const char *label, size_t capacity)
{
    int result = 0;
    for (int counter = 0; counter < strlen(label); ++counter)
    {
        result = result * 7 + label[counter];
    }
    return result % capacity;
}

int insertSymbol(SymbolTable *table, Symbol value)
{
    if (table == NULL)
    {
        return INSERT_FAILED;
    }
    int position = getLabelHash(value.label, table->capacity);
    while(table->symbols[position].isUsed == SYMBOL_USED)
    {
        if(!strncmp(table->symbols[position].label, value.label, LABEL_LENGTH))
        {
            return INSERT_FAILED;
        }
        position = (position + 1) % table->capacity;
    }
    value.isUsed = SYMBOL_USED;
    table->symbols[position] = value;
    table->count++;
    return position;
}

void destroySymbolTable(SymbolTable *table)
{
    if (table)
    {
        if (table->symbols != NULL)
        {
            free(table->symbols);
            table->symbols = NULL;
        }
        table->capacity = 0;
        table->count = 0;
    }
}

int findByLabel(SymbolTable *table, const char *label)
{
    if (table == NULL)
    {
        return NOT_FOUND;
    }
    int position = getLabelHash(label, table->capacity);
    while(table->symbols[position].isUsed == SYMBOL_USED)
    {
        if(!strncmp(table->symbols[position].label, label, LABEL_LENGTH))
        {
            return position;
        }
        position = (position + 1) % table->capacity;
    }
    return NOT_FOUND;
}