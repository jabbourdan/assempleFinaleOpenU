#ifndef MACHINEDCODE_H
#define MACHINEDCODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "dataCode.h"
#include "structsFor.h"

/**
*import the function int the Machine code
*@param errorFileName,@param head machineCode, @param function funcNameand and @param line the text line.
*/
void machineCodeFunction(char* errorFileName,struct machineCode *head, char function[], char line[]);
/**
* conver the function to the bits (mov == "0000")
*@param op the funcion
*/
const char* funcBits(char op[]);
/**
*import the the numebrs in the machine code in data for example
*@param errorFileName,@param head machineCode and @param line the text line.
*/
void insserTheNumbers(char *errorFileName,struct machineCode* head,char line[]);
/**
*return the the number in the binary
*@param number the number to conver in base of 10 and @param bits the bits to conver 4 or 6 or 8 bits for example
*/
char* changeBinary(int number,int bits);
/**
*check if the str is numeric
*/
int isNumeric(const char* str);
/**
*import the chars to the machhine code
*@param head the machineCode and @param line the text line.
*/
void insertTheString(struct machineCode* head,char line[]);
/**
*check if the line has 2 registers or not
*@param line the text line.
*/
int checkBothRegOrNot(const char line[]);
/**
*update the machineCode in the sencond step
*@param errorFileName,@param data dataTable, @param dataTable machineCode ,@param line the text line, @param is Symbol check flag for symbole and @param tempID.
*/
void updateTheMachineOfTheFunction(char* errorFileName,struct dataTable* data,struct machineCode* head,char line[],int isSymbol,int tempID);
/**
*Print the string in the machineCode
*/
void printTheString(struct machineCode* head,const char* token,char* symbol);
#endif
