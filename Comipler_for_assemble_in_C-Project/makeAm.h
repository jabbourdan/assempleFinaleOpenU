#ifndef MAKEAM_H
#define MAKEAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validSyntax.h"
#include "main.h"

/*Define the structure for the Macro*/
struct Macro {
    char name[MAX_LINE_LENGTH];
    char* content; 
    struct Macro* next;
};

/**
* make the AM file ,@ param fileSource the file.
*/
char* makeAmFile(char* fileSource);
/**
*check if the line has macro or end of mcro or not.
*@param line the line text
*/
int isMacroOrEndm(char line[]);
/**
*reWrite the file of the Am 
*@param head the mcro struct,@file the file,@param fileAm the new file 
*/
void reWriteAmFile(struct Macro** head, const char* file, const char* fileAm);
/**
*create new node for mcro 
*@param the name of the mcro and @param content the content of the mcro
*/
struct Macro* createNode(const char* name, const char* content);
/**
*free the lists ,@param head the mcro struc
*/
void freeList(struct Macro* head);
/**
*remove the last line
*/
void removeTrailingNewline(struct Macro* head);
/**
*inser the mcro in the macro head
*@param errorFileName,@param head the mcro head and @param file the file name 
*/
int insertTheMacro(char *errorFileName,struct Macro** head, const char* file);
/**
*check if the mcro name exsit or not
*@param head the mcro head and @param name the name of the mcro
*/
int isMacroNameExists(struct Macro* head, const char* name);

#endif /* MAKE_AM */
