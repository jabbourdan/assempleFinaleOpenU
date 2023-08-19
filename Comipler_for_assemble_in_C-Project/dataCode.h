#ifndef DATATABLE_H
#define DATATABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "structsFor.h"

/**
*put the entry and the extern in the dataHead
*@param errorFileName,@param temp dataTable,@param line the line text,@param flag for flag index ,@param type what the type (entry or extern) and @param index
*/
void putTheEntryOrExternIn(char *errorFileName,struct dataTable * temp,char line[],int flag,const char * type,int index);
/**
*check if the symbol exsist in the dataTable
*@param errorFileName,@param dataTable dataTable and @param sname the symbol name.
*/
int notExistSymbol(char line[],char* errorFileName,struct dataTable *dataTable, char sname[]);
/**
*extract the adress of the symbol
*@param head dataTable and @param symbol the symbol name.
*/
char* extractTheAdressOfSymbol(struct dataTable* head,char* symbol);
/**
*check the extern 
*@param errorFileName,@param head dataTable and @param line the text line,@param index to check .
*/
void checkTheExtern(char* errorFileName,struct dataTable* head,char line[],int index);
/**
*check the entry 
*@param errorFileName,@param head dataTable and @param line the text line,@param index to check .
*/
int checkTheEntry(char *errorFileName,struct dataTable *head, char line[],int index);
#endif
