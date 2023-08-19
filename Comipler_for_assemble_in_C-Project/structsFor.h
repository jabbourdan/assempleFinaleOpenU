#ifndef MSTRUCTSFOR_H
#define MSTRUCTSFOR_H
#include "main.h"
struct dataTable  {
    char symbol [MAX_SYMBOL_LENGTH];
    int numberOfValues;
    int adress;
    int appear;
    char type[8];/*if its external or what like step 9 */
    struct dataTable* next;
};

struct machineCode {
    char symbol[31];
    char opcode [MAX_BITES];
    char funct [5];
    char functAdress [5];
    char firstArg [MAX_LINE_LENGTH];
    char firstArgAddress[MAX_BITES];
    char secondArg [MAX_LINE_LENGTH];
    char secondArgAddress [MAX_BITES];
    char stringordata[MAX_LINE_LENGTH];
    struct machineCode* next;
};

#endif
