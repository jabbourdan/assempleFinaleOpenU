#include "validSyntax.h"

void printf_line_error(char* errorFileName,char* line, char* message){
    FILE *err_output_file = fopen(errorFileName, "a");

    fprintf(err_output_file,"Error In %s", line);
    fprintf(err_output_file,"The error is : %s",message);
    fprintf(err_output_file, "\n");
    fflush(err_output_file);

    fclose(err_output_file);

}

int validSymbol(char line[],int indexOfTheDots) {
    int j=0;

    if(indexOfTheDots == 0 ){
        return -1;
    }
    while(isspace(line[j]))
        j++;
    if(isdigit(line[j])){
        return 0;}
    if(indexOfTheDots-j>=MAX_SYMBOL_LENGTH-1){
        return -1;
    }
    if(!isspace(line[indexOfTheDots+1]) || isspace((line[indexOfTheDots-1]))){

        return -1;
    }
    return 1;
}
int returnIndexTheData(char line[],int index){
    int aindex = 0;
    char att[MAX_LINE_LENGTH];
    memset(att, '\0' , MAX_LINE_LENGTH);
    while(isspace(line[index]))
        index ++;
    while (!isspace(line[index]) && line[index] != '\n')
    {
        att[aindex] = line[index];
        aindex++;
        index++;
    }
    return index;
}
int validateDataSyntax(char line[],char *errorFileName,int index) {
    int index1 = returnIndexTheData(line,index);
    int num_flag = 0,comma=0;
    int last_non_space_idx = 0,num=0;
    int i = 0,isNumeric=1;
    int index2=returnIndexTheData(line,index);
    char mainLine[MAX_LINE_LENGTH];
    char *line1=line;
    char *line2=line;
    char line3[MAX_LINE_LENGTH];
    char *token;
    long number;
    int last_comma = -2;
    char *endptr;
    strcpy(line3,line);
    strcpy(mainLine,line);
    while (line[index1] != '\0') {
        if (isspace(line[index1])) {
            index1++;
            continue;
        }
        if (num_flag &&  isdigit(line[index1])){
            printf_line_error(errorFileName,mainLine,"This line has wrong format\n");
            return 0;}
        while (isdigit(line[index1])) {
            num_flag = 1;
            index1++;
        }
        if (line[index1] == ',') {

            num_flag = 0;
        }
        index1++;
    }
    /* second run adjacent comma check*/
    while (line1[index2] != '\0') {
        if (isdigit(line1[index2]) || isalpha(line1[index2])) {
            last_non_space_idx = i;
            comma=0;
        } else {
            if (line[index2] == ',') {
                if (last_comma > last_non_space_idx) {
                    printf_line_error(errorFileName,mainLine,"This line has wrong format\n");
                    return 0;
                }
                last_comma = i;
                comma=1;
            }
        }
        index2++;
        i++;
    }
    i= returnIndexTheData(line,index);
    while(line2[i]!='\0'){
        if(isspace(line2[i]))i++;
        if(line2[i] == ','&& !num){
            printf_line_error(errorFileName,mainLine,"This line has wrong format with the comma\n");
            return 0;
        }
        if(!isspace(line[i])&&line[i] != ','){
            num=1;
        }
        i++;
    }
    if(comma){
        printf_line_error(errorFileName,mainLine,"This line has wrong format\n");
        return 0;
    }
    token = strtok(line3 + index, " ,");
    while (token != NULL) {
        /* If the token starts with a digit or a minus sign followed by a digit */
	if(strcmp(token,".data") ==0){
            token = strtok(NULL, " ,");
            continue;
        }
        for (i = 0; token[i] != '\0'; i++) {
            if(token[0] == '-')i++;
            if(token[i] == '\n')break;
            if (!isdigit(token[i])) {
                isNumeric = 0; /* The token contains non-numeric characters */
                break;
            }
        }
        if (!isNumeric) {
            printf_line_error(errorFileName, mainLine, "This line has non-numeric characters\n");
            return 0;
        }
        number = strtoul(token, &endptr, 10);
        if (number <= -2048 || number >= 2047) {
            printf_line_error(errorFileName,mainLine,"error: this line has wrong number\n");
            return 0;
        }
        /* Find the next token */
        token = strtok(NULL, " ,");
    }
    return 1;
}

int validString(char line[],char *errorFileName,int index){
    int quat=0;
    index = returnIndexTheData(line,index);
    while(isspace(line[index])){
        index++;
    }
    while(line[index] != '\0') {

        if (line[index] == '"') {
            if (quat == 0) {
                quat = 1;
            } else if (quat==1){
                quat=2;
            }
        }
        index++;
    }
    if(quat==1){
        printf_line_error(errorFileName,line,"This line has wrong syntax\n");
        return 0;
    }
    return 1;
}
char* returnSource(char line[],int index) {
    char *sourceArg = (char *) malloc(MAX_LINE_LENGTH * sizeof(char));
    int sourceIndex = 0;
    if(line[index] == '\n'){
        return NULL;
    }
    while (isspace(line[index])) {
        index++;
    }
    while (line[index] != '\0'&&!isspace(line[index])) {
        if(line[index] == ','){
            break;
        }
        sourceArg[sourceIndex] = line[index];
        sourceIndex++;
        index++;
    }
    if(sourceIndex==0){
        return NULL;
    }
    sourceArg[sourceIndex] = '\0';
    return sourceArg;
}

char* returnDest(char line[],int index) {
    char *desArg = (char *) malloc(MAX_LINE_LENGTH * sizeof(char));
    int desIndex = 0,comma=0;
    if(line[index] == '\n'){
        return NULL;
    }
    while(isspace(line[index]))index++;
    while(!isspace(line[index])){
        if(line[index] == ','){
            index++;
            comma =1;
            break;
        }
        index++;
    }

    while (isspace(line[index]) || line[index] ==',') {
        if(line[index] ==','){
            comma=1;
        }
        index++;
    }
    if(!comma)return NULL;

    while (line[index] != '\0'&&!isspace(line[index]) && line[index] !='\n') {
        desArg[desIndex] = line[index];
        desIndex++;
        index++;
    }
    if(desIndex==0){
        return NULL;
    }
    desArg[desIndex] = '\0';
    return desArg;
}

int validTakesArgs(char functionName[],char line[],int index){
    char* firstArg= returnSource(line,index);
    char* secondArg= returnDest(line,index);
    if(strcmp(functionName, "mov") == 0 || strcmp(functionName, "cmp") == 0 || strcmp(functionName, "add") == 0 || strcmp(functionName, "sub") == 0 || strcmp(functionName, "lea") == 0){
        if(firstArg == NULL || secondArg ==NULL){
            return 0;
        }
    }else if (strcmp(functionName, "not") == 0 || strcmp(functionName, "clr") == 0 || strcmp(functionName, "inc") == 0 || strcmp(functionName, "dec") == 0 || strcmp(functionName, "jmp") == 0 || strcmp(functionName, "bne") == 0 || strcmp(functionName, "red") == 0 || strcmp(functionName, "prn") == 0 || strcmp(functionName, "jsr") == 0){
        if(firstArg==NULL){
            return 0;
        }else if(secondArg != NULL){
            return 0;
        }
    }else if(strcmp(functionName, "rts") == 0 || strcmp(functionName, "stop") == 0){
        if(firstArg!=NULL || secondArg!=NULL){
            return 0;
        }
    }
    free(firstArg);
    free(secondArg);
    return 1;
}
int retrunTheNumberOfThetypeOfThearg(char line[],char *errorFileName,char* arg){
    int index = 0;
    if(arg==NULL)return 0;
    while(isspace(arg[index]) || arg[index] == ',')index++;
    if(!strcmp(arg,"@r0") || !strcmp(arg,"@r1") || !strcmp(arg,"@r2") || !strcmp(arg,"@r3") || !strcmp(arg,"@r4") ||!strcmp(arg,"@r5") || !strcmp(arg,"@r6") || !strcmp(arg,"@r7")){
        return 5;
    }else if(arg[index] == '-' || isdigit(arg[index])){
        if(arg[index] == '-')index++;
        while(arg[index] != '\0'){
            if(!isdigit(arg[index])){
                printf_line_error(errorFileName,line,"The symbol is take wrong type arg\n");
                return 0;
            }
            index++;
        }
        return 1;
    }else if(isalpha(arg[index])){
        return 3;
    }else
        return 0;
}

int validArgsFun(char line[],char *errorFileName,char funcNameSymbol[],char* firstArg,char* secondArg){
    int firstTpye=retrunTheNumberOfThetypeOfThearg(line,errorFileName,firstArg);
    int secondTpye=retrunTheNumberOfThetypeOfThearg(line,errorFileName,secondArg);
    if(!strcmp(funcNameSymbol, "mov") || !strcmp(funcNameSymbol, "sub") || !strcmp(funcNameSymbol, "add")){
        if(secondTpye==1){
            printf_line_error(errorFileName,line,"The symbol is take wrong type arg\n");
            return 0;
        }
    }else if(!strcmp(funcNameSymbol, "lea")){
        if(firstTpye==1 || firstTpye==5 || secondTpye ==1){
            printf_line_error(errorFileName,line,"The symbol is take wrong type arg\n");
            return 0;
        }
    }else if(!strcmp(funcNameSymbol, "not") || !strcmp(funcNameSymbol, "clr") || !strcmp(funcNameSymbol, "inc") || !strcmp(funcNameSymbol, "dec") ||
            !strcmp(funcNameSymbol, "jmp") || !strcmp(funcNameSymbol, "bne") || !strcmp(funcNameSymbol, "red") || !strcmp(funcNameSymbol, "jsr")){
        if(firstTpye==1){
            printf_line_error(errorFileName,line,"The symbol is take wrong type arg\n");
            return 0;
        }
    }
    return 1;

}

int validEntryAndExtern(char line[],char *errorFileName,int index) {
    /*valid entry no first number, betwen every 2 word should be comma */
    int index1 = returnIndexTheData(line,index);
    int num_flag = 0,comma=0;
    int last_non_space_idx = 0,num=0;
    int i = 0;
    int index2=returnIndexTheData(line,index);
    char *line1=line;
    char *line2=line;
    int last_comma = -2;
    while (line[index1] != '\0') {
        if (isspace(line[index1])) {
            index1++;
            continue;
        }
        if(isdigit(line[index1])){
            printf_line_error(errorFileName,line,"The line has wrong format\n");
            return 0;
        }
        if (num_flag &&  !isspace(line[index1]) && line[index1] != ','){
            printf_line_error(errorFileName,line,"The line has wrong format\n");
            return 0;}

        while (!isspace(line[index1]) && line[index1] != ',') {
            num_flag = 1;
            index1++;
        }
        if (line[index1] == ',') {
            num_flag = 0;
        };
        index1++;
    }

    while (line1[index2] != '\0') {
        if (isdigit(line1[index2]) || isalpha(line1[index2])) {
            last_non_space_idx = i;
            comma=0;
        } else {
            if (line[index2] == ',') {
                if (last_comma > last_non_space_idx) {
                    printf_line_error(errorFileName,line,"The line has wrong format with comma\n");
                    return 0;
                }
                last_comma = i;
                comma=1;
            }
        }
        index2++;
        i++;
    }
    i= returnIndexTheData(line,index);
    while(line2[i]!='\0'){
        if(isspace(line2[i]))i++;
        if(line2[i] == ','&& !num){
            printf_line_error(errorFileName,line,"The line has wrong format with first comma\n");
            return 0;
        }
        if(!isspace(line[i])&&line[i] != ','){
            num=1;
        }
        i++;
    }
    if(comma){
        printf_line_error(errorFileName,line,"The line has wrong format\n");
        return 0;
    }
    return 1;
}
