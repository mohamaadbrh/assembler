#include "general.h"
#include <stdio.h>

InstructionInfo parseLine(const char *line)
{
    InstructionInfo result;
    int tokens = sscanf(line, "%s %s %d,%d,%d",
           result.label,
           result.function,
           result.arguments[0],
           result.arguments[1],
           result.arguments[2]
    );
    return result;
}