#include <string.h>
#include <stdlib.h>
#include "procedures.h"
#include "instruction.h"

int analyzeLabels(FILE *file, Symbol table[])
{
    int pc = 0;
    char buffer[BUFFER_MAX];
    while (fgets(buffer, BUFFER_MAX, file) != NULL)
    {
        InstructionInfo info = parseLine(buffer);
        if (info.function == UnknownInstruction && info.label[0] == '\0')
        {
            continue;
        }
        if (info.label[0] != '\0')
        {
            int position = findByLabel(table, info.label);
            if (position != NOT_FOUND)
            {
                return ANALYSIS_FAILED;
            }

            Symbol symbol = {0};
            symbol.pc = pc;
            symbol.isUsed = SYMBOL_USED;

            strncpy(symbol.label, info.label, LABEL_LENGTH - 1);
            symbol.label[LABEL_LENGTH - 1] = '\0';

            if (insertSymbol(table, symbol) < 0)
            {
                return ANALYSIS_FAILED;
            }
        }

        if (info.function == Space)
        {
            int count = atoi(info.arguments[0]);

            if (count < 0)
            {
                return ANALYSIS_FAILED;
            }
            pc += count;
        }
        else
        {
            pc++;
        }
    }
    return pc;
}