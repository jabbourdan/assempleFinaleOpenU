#ifndef SECONDSTEP_H
#define SECONDSTEP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"
#include "dataCode.h"
#include "machineDcode.h"
#include "structsFor.h"

/**
*The second step make the machine code and check the entry and all the stuf that realted to the data table
*@param fileName the file name ,@param errorFileName, @param stail thhe data table, @param dtail the machineCode ,@param IC the count of the machine code and @param DC the data count
*/
void secondCheck(char* fileName,char* errorFileName,struct  dataTable* stail, struct  machineCode* dtail,int *IC,int *DC);
#endif
