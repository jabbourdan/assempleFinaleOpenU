#ifndef PRINTTHEOUTPUTS_H
#define PRINTTHEOUTPUTS_H
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "machineDcode.h"
#include "dataCode.h"
#include "structsFor.h"
/**
*rturn if there is and error with the file to not make the ob and all the entry and extern files ,@param file the file name
*/
int returnIfThereIsNoErrors(char *filename);
/**
*print the error of the file 
*@param machineHead the machhineCode, and @param the file name, @param IC the count of the machoneCode and @param Dc the count of the data
*/
void printTheObFile(struct machineCode* machineHead,char *filename,const int *IC,const int *DC);
/*
*check if the entery or extern
*@param dataHead datatabel and @param typeToCheck 
*/
int checkIfTheEntryOrExtern(struct dataTable* dataHead,char* typeToCheck);
/*
*make thefile of the entry and the extern
*@param dataHead datatabel ,@param machineCode machineCode ,@param fileName the file name, @param type the tpye extern or entry and the extension (ent and ext) 
*/
void makeTheEntryAndExtern(struct dataTable* dataHead,struct machineCode* machineCode,char *fileName,char *tpye,char* extenstion);
#endif
