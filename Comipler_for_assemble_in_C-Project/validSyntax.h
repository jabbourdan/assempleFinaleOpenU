#ifndef VALIDSYNTAX_H
#define VALIDSYNTAX_H
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "structsFor.h"

/**
*all the function here for the same porpose like to validate the syntax and the function in the data and return true or fale zero or 1
*/
int validSymbol(char line[], int indexOfTheDots);
int validString(char line[],char *errorFileName,int index);
int returnIndexTheData(char line[],int index);
int validTakesArgs(char functionName[],char line[],int index);
int validateDataSyntax(char *errorFileName,char line[],int index);
int validEntryAndExtern(char line[],char *errorFileName,int index);
char* returnDest(char line[],int index);
char* returnSource(char line[],int index);
int validArgsFun(char line[],char *errorFileName,char functionName[],char* firsArg,char* secondArg);
int retrunTheNumberOfThetypeOfThearg(char line[],char *errorFileName,char* arg);
void printf_line_error(char* errorFileName, char* line, char* message);
#endif /* VALIDSYNTAX_H */
