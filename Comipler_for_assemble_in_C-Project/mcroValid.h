#ifndef MCROVALID_H
#define MCROVALID_H

#include <stdio.h>
#include <string.h>
#include "makeAm.h"
#include "main.h"

/*Typedef of the struct to function that not allowed*/
typedef struct {
    char name[MAX_LINE_LENGTH];
} funNotAllowed;

/*Open the file */
FILE* open_file(const char* file, char* operator);
/**
*check if mcro name exsit ,@param word the name of the mcro
*/
int isValidRestrictedWord(const char* word);
/*
*check if the mcro is valid, @param file thhe file name
*/
int validMacro(char* file);
/*
*check if there is mcro , @param file the file name
*/
int isThereMcro(char* file);
/**
*check the mcro,@param file thhe file name
*/
int checkMacro(char* file);

#endif
