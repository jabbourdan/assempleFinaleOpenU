#include "machineDcode.h"


const char* funcBits(char op[]) /*Returns the opcode type in decimal base*/
{
    char *new = (char*)malloc(5 * sizeof(char));
    if (new == NULL) {
        return NULL;
    }
    memset(new, '\0', 5);
    if(!strcmp(op, "mov"))
        strcpy(new, "0000");
    else if(!strcmp(op, "cmp"))
        strcpy(new, "0001");
    else if(!strcmp(op, "add"))
        strcpy(new, "0010");
    else if(!strcmp(op, "sub"))
        strcpy(new, "0011");
    else if(!strcmp(op, "not"))
        strcpy(new, "0100");
    else if(!strcmp(op, "clr"))
        strcpy(new, "0101");
    else if(!strcmp(op, "lea"))
        strcpy(new, "0110");
    else if(!strcmp(op, "inc"))
        strcpy(new, "0111");
    else if(!strcmp(op, "dec"))
        strcpy(new, "1000");
    else if(!strcmp(op, "jmp"))
        strcpy(new, "1001");
    else if(!strcmp(op, "bne"))
        strcpy(new, "1010");
    else if(!strcmp(op, "red"))
        strcpy(new, "1011");
    else if(!strcmp(op, "prn"))
        strcpy(new, "1100");
    else if(!strcmp(op, "jsr"))
        strcpy(new, "1101");
    else if(!strcmp(op, "rst"))
        strcpy(new, "1110");
    else if(!strcmp(op, "stop"))
        strcpy(new, "1111");
    else
        strcpy(new, "-1");
    return new;
}
void machineCodeFunction(char* errorFileName,struct machineCode *head, char function[], char line[]) {
    const char *binaryFunction = funcBits(function);
    if(binaryFunction==NULL){

        printf_line_error(errorFileName,line,"Error: Memory allocation failed in funcBits \n");
        return;
    }
    if(strcmp(binaryFunction, "-1") == 0){
        printf_line_error(errorFileName,line,"The syntax of this line is not correct \n");
        return;
    }
    if(binaryFunction !=NULL || binaryFunction != 0){
        strcpy(head->opcode,"000000000000");
        strcpy(head->funct, function);
        strcpy(head->functAdress, binaryFunction);
    }
    strcpy(head->funct, function);
    strcpy(head->functAdress, binaryFunction);
}
char* changeBinary(int number, int bits) {
    /* Calculate the minimum buffer size needed for the binary representation */
    int bufferSize = bits + 1; /* bits + 1 for the null-terminator */
    int i;
    int bit;
    /* Allocate memory for the binary string dynamically */
    char *binaryString = (char *)malloc(bufferSize * sizeof(char));

    if (binaryString == NULL) {
        /* Memory allocation failed, handle the error here */
        return NULL;
    }
    if (number < 0) {
        number = (1 << bits) + number;
    }
    for (i = bits - 1; i >= 0; i--) {
        bit = (number >> i) & 1;
        binaryString[bits - 1 - i] = (char)(bit + '0');
    }
    binaryString[bits] = '\0';
    return binaryString;
}
int isNumeric(const char* str) {
    if (*str == '-') {
        str++;
    }
    if (*str== '\0') {
        return 0; /* Empty string is not numeric */
    }
    while (*str && *str != '\n') {
        if (*str < '0' || *str > '9') {
            return 0; /* At least one character is not a digit */
        }

        str++;
    }
    return 1;
}
void insertNode(char* errorFileName,struct machineCode* head, const char* symbol, int num) {
    char* binary;
    struct machineCode* current = head;
    struct machineCode* newNode = (struct machineCode*)malloc(sizeof(struct machineCode));
    if (newNode == NULL) {
        printf_line_error(errorFileName,NULL,"Error: Memory allocation failed in funcBits \n");
        return;
    }

    /* Convert the number to binary and store it in the new node */
    binary = changeBinary(num, 12);
    if (binary == NULL) {
        free(newNode); /* Free the newly allocated node before returning on error */
        return;
    }

    strcpy(newNode->symbol, symbol);
    strcpy(newNode->opcode, binary);
    newNode->next = NULL;

    free(binary);/* Free the binary representation string (since it was dynamically allocated)*/

    /* Find the last node in the linked list */
    while (current->next != NULL) {
        current = current->next;
    }

    /* Link the new node to the last node */
    current->next = newNode;

}

void insserTheNumbers(char *errorFileName,struct machineCode* head,char line[]){
    int num,firstTime=1;
    char *binary;
    char* symbol = head->symbol;
    char* token = strtok(line, " ,"); /* Split the line by spaces and commas*/
    while (token != NULL) {
        if (isNumeric(token)) {
            if (strtol(token, NULL, 10) != 0) { /* Convert the token to a long integer */
                num = strtol(token, NULL, 10);
                if (num != 0) {
                    binary = changeBinary((int)num, 12);
                    if (!head->next && firstTime) {
                        strcpy(head->opcode, binary);
                        strcpy(head->stringordata, ".data");
                        firstTime=0;
                    } else {
                        insertNode(errorFileName, head, symbol, num);
                        strcpy(head->stringordata, ".data");
                    }
                }
            }
        }
        token = strtok(NULL, " ,"); /* Move to the next token */
    }
}

void insertTheString(struct machineCode* head,char line[]){
    int theString=0;
    char* symbol = head->symbol;
    const char* token = strtok(line, " ,"); /* Split the line by spaces and commas */
    while (token != NULL) {
        if(!strcmp(token, ".string")) {
            theString=1;
        }
        if(theString && strcmp(token, ".string") != 0){
            printTheString(head,token,symbol);
        }
        token = strtok(NULL, " ,"); /* Move to the next token */
    }
}
char* convertBinaryString(char ch) {
    char *binaryStr = (char*)malloc(13);/* Fixed-size array to store the binary representation (12 bits + 1 null-terminator) */
    int i;
    if (binaryStr == NULL) {
        printf("Error: Memory allocation failed in funcBits \n");
        return NULL;
    }
    /* Build the binary representation in the character array */
    for (i = 11; i >= 0; i--) {
        binaryStr[11 - i] = (ch & (1 << i)) ? '1' : '0';
    }
    return binaryStr;
}
void insertnodeString(struct machineCode* head ,const char* symbol,char ch){
    struct machineCode* newNode = (struct machineCode*)malloc(sizeof(struct machineCode));
    struct machineCode* current;
    char* binary=NULL;
    if (newNode == NULL) {
        printf("Error: Memory allocation failed in funcBits \n");
        return;
    }
    if(ch == '\0'){
        binary = "000000000000";
    }else {
        binary = convertBinaryString(ch);
    }
    /* Convert the number to binary and store it in the new node */
    strcpy(newNode->symbol, symbol);
    strcpy(newNode->opcode, binary);
    strcpy(newNode->stringordata, ".string");
    newNode->next = NULL;

    /* Find the last node in the linked list */
    current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    /* Link the new node to the last node */
    current->next = newNode;
}

void printTheString(struct machineCode* head,const char* token,char* symbol){
    int index = 0,qua=0,firstTimeToInsert=0,firstTimeQue=0;
    char* binary;
    while(token[index] != '\0'){
        if(token[index] == '"'){
            if(!firstTimeQue) {
                qua = 1;
                firstTimeQue=1;
                index++;
                continue;
            }else{
                /*put an new line at the end */
                insertnodeString(head, symbol, '\0');
                break;
            }
        }
        if(!firstTimeToInsert) {
            binary = convertBinaryString(token[index]);
            strcpy(head->opcode,binary);
            strcpy(head->stringordata,".string");
            firstTimeToInsert=1;
        }else if (qua) {
            insertnodeString(head, symbol, token[index]);
            firstTimeToInsert=1;
        }
        index++;
    }
}

int checkBothRegOrNot(const char line[]){
    int thereIsTwoArgs = 0,index =0;/* 0 = no args 1 one arg ,2 two args*/
    while (line[index] != '\0'){
        if(line[index] == '@' && thereIsTwoArgs == 0){
            thereIsTwoArgs =1;
            index++;
            continue;
        }
        if(line[index] == '@' && thereIsTwoArgs == 1){
            thereIsTwoArgs =2;
        }
        index++;
    }

    return thereIsTwoArgs;
}

char* shiftBinary(char* binary, int positions, int direction) {/*0 left 1 for right */
    unsigned long length = strlen(binary);
    char* shiftedBinary = NULL;
    int i;
    if (direction == 0) {
        shiftedBinary = malloc(length + positions + 1); /* +1 for the null terminator */
        strcpy(shiftedBinary, binary);

        for (i = 0; i < positions; i++) {
            strcat(shiftedBinary, "0");
        }
    } else if (direction == 1) {
        shiftedBinary = malloc(length + positions + 1);
        for (i = 0; i < positions; i++) {
            shiftedBinary[i] = '0';
        }
        strcpy(shiftedBinary + positions, binary);
    }

    return shiftedBinary;
}
char* convertTheArgToBinary(char line[],char *errorFileName,struct dataTable* headTable,char* arg,int type,const char* secondArg){
    int lastValue;
    long number;
    long int value;
    unsigned long length = strlen(arg);
    char lastArg;
    char *endptr;
    char* binnary=NULL;
    if(type==1){
        number = strtol(arg, &endptr, 10);
        if(number <= -2048 || number >= 2047){
            printf_line_error(errorFileName,line,"The number ont this line is bigger that 2047 or lower that -2048");
            return 0;
        }
        value=strtol(arg, NULL, 10);
        binnary = changeBinary((int)value,10);
        binnary = shiftBinary(binnary, 2,0);
    }else if(type==3){
        binnary= extractTheAdressOfSymbol(headTable,arg);
    }else if(type==5&&secondArg==NULL){
        lastArg = arg[length-1];
        lastValue = lastArg - '0';
        binnary = changeBinary(lastValue , 4);
        binnary = shiftBinary(binnary, 2,0);
        binnary = shiftBinary(binnary, 6,1);

    }else if (type==5&&secondArg!=NULL){
        lastArg = arg[length-1];
        lastValue = lastArg - '0';
        binnary = changeBinary(lastValue , 5);
        binnary = shiftBinary(binnary, 7,0);
    }
    return binnary;
}

void updateTheOpCode(struct machineCode* head,int typeFirsArg ,int typeSecondArg){
    char* binaryFirstArg = changeBinary(typeFirsArg,3);
    char* binarySecondArg = changeBinary(typeSecondArg,3);
    char* binaryFunc = head->functAdress;
    size_t totalLength = strlen(binaryFirstArg) + strlen(binarySecondArg) + strlen(binaryFunc) + 1;
    char* concatenated = (char*)malloc(totalLength);
    if (concatenated) {
        if(strcmp(binarySecondArg,"000") ==0){

            strcpy(concatenated, binarySecondArg);
            strcat(concatenated, binaryFunc);
            strcat(concatenated, binaryFirstArg);


        }else {
            strcpy(concatenated, binaryFirstArg);
            strcat(concatenated, binaryFunc);
            strcat(concatenated, binarySecondArg);
        }
        concatenated = shiftBinary(concatenated,2,0);
    } else {
        printf("Memmory alocated error");
    }
    strcpy(head->opcode,concatenated);
    free(concatenated);
}
void updateMachineAtPosition(char line[],char *errorFileName,struct machineCode* head,struct dataTable* headData,char* firstArg,char* secondArg,char* funcName,int currentIC){
    struct machineCode* current = head;
    int typeFirsArg,typeSecondArg,count=1;
    char* binaryFirstArg;
    char* binarySecondArg;
    typeFirsArg=retrunTheNumberOfThetypeOfThearg(line,errorFileName,firstArg);
    typeSecondArg=retrunTheNumberOfThetypeOfThearg(line,errorFileName,secondArg);
    if (head == NULL) {
        return;
    }
    while (current != NULL) {
        if (!strcmp(current->funct,funcName) && count==currentIC) {
            updateTheOpCode(current,typeFirsArg,typeSecondArg);
            if(typeFirsArg==5 && typeSecondArg==5){
                strcpy(current->firstArg , firstArg);
                strcpy(current->secondArg , secondArg);
                strcpy(current->firstArgAddress,"000010010000");
            }else
            if(firstArg!=NULL){
                strcpy(current->firstArg , firstArg);
                binaryFirstArg = convertTheArgToBinary(line,errorFileName,headData,firstArg,typeFirsArg,secondArg);
                if(binaryFirstArg!=NULL){
                    strcpy(current->firstArgAddress , binaryFirstArg);
                }

                if(secondArg!=NULL){
                    strcpy(current->secondArg , secondArg);
                    binarySecondArg = convertTheArgToBinary(line,errorFileName,headData,secondArg,typeSecondArg,NULL);
                    if(binarySecondArg!=NULL){
                        strcpy(current->secondArgAddress , binarySecondArg);
                    }
                }
                return;
            }

        }
        count++;
        current = current->next;
    }

}
void updateTheMachineOfTheFunction(char* errorFileName,struct dataTable* headTable, struct machineCode* head, char line[], int isSymbol,int currentIC ) {
    char* funcNameSymbol = (char*)malloc(MAX_SYMBOL_LENGTH);
    char* funcName = (char*)malloc(MAX_LINE_LENGTH);
    int syIndex = 0, index = 0,symbol=0;
    char* firstArg = NULL, * secondArg = NULL;
    while (isspace(line[index])) {
        index++;
    }
    if (isSymbol) {
        /* Code for processing symbol */
        while(!isspace(line[index]))index++;
        while(isspace(line[index]))index++;
        while (!isspace(line[index])) {
            if (line[index] == ':') {
                funcName[syIndex] = '\0';
                index++;
                break;
            }
            funcName[syIndex] = line[index];
            index++;
            syIndex++;
            symbol=1;
        }
    }
    funcName[syIndex] = '\0';
    while (isspace(line[index])) {
        index++;
    }

    /* Code for processing function name */
    while (!isspace(line[index]) && !isSymbol) {
        if (line[index] == '\0') {
            syIndex++;
            break;
        }
        funcName[syIndex] = line[index];
        index++;
        syIndex++;
    }
    funcName[syIndex] =  '\0';
    if(!symbol){
        funcNameSymbol=NULL;
    }else
        strcpy(funcNameSymbol,funcName);
    /* Code for processing first and second arguments */
    firstArg = returnSource(line, index);
    secondArg = returnDest(line, index);
    if(funcNameSymbol!=NULL){
        if (validArgsFun(line,errorFileName,funcNameSymbol, firstArg, secondArg)) {
            updateMachineAtPosition(line,errorFileName,head, headTable, firstArg, secondArg, funcNameSymbol,currentIC);
        }
    }else if(validArgsFun(line,errorFileName,funcName, firstArg, secondArg)){
        updateMachineAtPosition(line,errorFileName,head, headTable, firstArg, secondArg,funcName,currentIC);
    }
    

    /* Free dynamically allocated memory */
    /*free(funcNameSymbol);*/
    /*free(funcName);*/
}

