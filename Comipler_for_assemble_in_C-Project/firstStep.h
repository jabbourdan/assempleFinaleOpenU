#ifndef FIRSTSTEP_H
#define FIRSTSTEP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "dataCode.h"
#include "machineDcode.h"
#include "structsFor.h"

/**
*check if its symbol or not 
*@param line the text line,@param errorFileName,@param temp dataTable ,@dataTable dataTable and @param step the first or second step
*/
int isSymbol(char line[],char *errorFileName, struct  dataTable* temp,struct  dataTable* dataTable,int step);
/**
*the first check (firs step on the) the read lines and put the data in the data table and some of the machine code.
*@param fileName the file that we read from,@param errorFileName, @param shead the dataTable,@param dhead the machine table,@param IC for count the machinecode and @param DC for dataCount .
*/
int firstcheck(char* fileName, char* errorFileName,struct  dataTable* shead, struct  machineCode* dhead, int *IC, int *DC);
/**
*check if the line is string or data
*@param line the line text and @param index to check.
*/
int stringOrData(char line[] , int index);
/**
*return the number of chars and +1 for NULL for the string
*@param line the line text and @param index to check.
*/
int stringArg(char line[] , int index);
/**
*return the number of numbers for data
*@param line the line text and @param index to check.
*/
int dataArg(const char line[] , int index);
/**
*build basic machine code for the lines
*@param line the line text ,@param errorFileName, @param index to check and @param machineCode for the machineCode
*/
int opCode(char line[],char *errorFileName, int ind ,struct  machineCode* machineCode);
/**
*check if the line has entry or extern or not
*@param line the line text and @param index to check.
*/
int entryOrExtery(char line[],int index);
/**
*return the number of args if I have a function
*@param machineCode for the machineCodeand @param line the line text.
*/
int numOfArg(struct  machineCode* machineCode,char line[]);

/** just skip the like that has new line and spaces ,@param line the text line.*/
int is_newline_or_spaces(const char *line);
#endif
