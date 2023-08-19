#include "dataCode.h"

int notExistSymbol(char line[],char* errorFileName,struct dataTable *dataTable, char sname[]) /*Checks if the symbol already exists*/
{
    struct dataTable *tailf = NULL;
    tailf = dataTable;
    while (tailf != NULL)  /*Run on all the symbols we have already found*/
    {
        if (!strcmp(tailf->symbol, sname)) {
            if(strcmp(tailf->type, "entry") ==0){
                tailf = tailf->next;
                continue;
            }if(strcmp(tailf->type, "extern") ==0) {
                tailf = tailf->next;
                printf_line_error(errorFileName,line,"This Symbol is extern and is exist on the file as symbol");
                continue;
            }
            return 0;
        }
        tailf = tailf->next;
    }
    free(tailf);

    return 1;
}
int checkTheEntry(char* errorFileName,struct dataTable *head, char line[],int index){
    struct dataTable *current ;
    char* symbols = (char *) malloc(MAX_SYMBOL_LENGTH);
    int  syIndex ,apear=0;

    while (isspace(line[index])) {
        index++;
    }
    while(!isspace(line[index])) {
        index++;
    }
    while(line[index]!='\0') {
        memset(symbols,'\0',31);
        apear=0;
        syIndex=0;
        current=head;
        while(isspace(line[index]))index++;
        while (line[index]!='\0') {
            if (line[index] == ',' || isspace(line[index])) {
                index++;
                break;
            }
            symbols[syIndex] = line[index];
            index++;
            syIndex++;
        }
        while (current != NULL) {
            if (strcmp(current->symbol, symbols) == 0) {
                if (strcmp(current->type, "entry") != 0) {
                    apear=1;
                }
                /* Stop the loop once the symbol is found*/
            }
            current = current->next;
        }
        if(apear == 0){
            printf_line_error(errorFileName,line,"The entry symbole don't exist as a symbol in the file\n");
        }
    }
    free(symbols);
    return apear;
}

void checkTheExtern(char *errorFileName,struct dataTable *head, char line[],int index) {
    struct dataTable *current ;
    char* symbols = (char *) malloc(MAX_SYMBOL_LENGTH);
    int  syIndex ;

    while (isspace(line[index])) {
        index++;
    }
    while(!isspace(line[index])) {
        index++;
    }
    while(line[index]!='\0') {
        memset(symbols,'\0',31);
        syIndex=0;
        current=head;
        while(isspace(line[index]))index++;
        while (line[index]!='\0') {
            if (line[index] == ',' || isspace(line[index])) {
                index++;
                break;
            }
            symbols[syIndex] = line[index];
            index++;
            syIndex++;
        }
        while (current != NULL) {
            if (strcmp(current->symbol, symbols) == 0) {
                if (strcmp(current->type, "extern") != 0) {
                    printf_line_error(errorFileName,line,"This Symbol is extern and is exist on the file as symbol.\n");
                }
                /* Stop the loop once the symbol is found*/
            }
            current = current->next;
        }
    }
    free(symbols);
}

char* extractTheAdressOfSymbol(struct dataTable* head,char* symbol){
    char* adress=NULL;
    char* finalAddress=NULL;
    struct dataTable* current = head;
    while (current != NULL) {
        if (strcmp(current->symbol, symbol) == 0) {
            if(strcmp(current->type, "entry") == 0){
                current = current->next;
                continue;
            }else if(strcmp(current->type, "extern") == 0){
                finalAddress = "000000000001";
                return finalAddress;
            }
            finalAddress = (char*)malloc(12);
            if (finalAddress == NULL) {
                printf("Memory allocation failed");
                return 0;
            }
            adress=changeBinary(current->adress,10);
            strcpy(finalAddress, adress);
            strcat(finalAddress, "10");
            break; /* Stop the loop once the symbol is found */
        }
        current = current->next;
    }
    return finalAddress;
}
void putTheEntryOrExternIn(char *errorFileName,struct dataTable* dataHead, char line[],int flag,const char * type,int index) {
    unsigned long tokenLength;
    char *substring;
    char att[MAX_LINE_LENGTH];
    char *token;
    struct dataTable* temp1 = NULL; /* Point to the existing linked list */

    memset(att, '\0', MAX_LINE_LENGTH);

    while (isspace(line[index]))
        index++;

    while (!isspace(line[index]))
        index++;

    while (isspace(line[index]))
        index++;


    substring=&line[index];

    token = strtok(substring, " ,");
    while (token != NULL){
        if(!notExistSymbol(line,errorFileName,dataHead,token)){
            printf_line_error(errorFileName,line,"This symbol exist in the dataTable\n");
            token = strtok(NULL, " ,");
            continue;
        }
        temp1 = (struct dataTable *) malloc(sizeof(struct dataTable));
        temp1->next = NULL;
        tokenLength= strlen(token);
        if (tokenLength > 0 && token[tokenLength - 1] == '\n') {
            /* Remove the last character by setting it to \0 */
            token[tokenLength - 1] = '\0';
        }

        if(!strcmp(token,".extern") || !strcmp(token,".entry")){
            token = strtok(NULL, " ,");
            continue;
        }

        strcpy(temp1->symbol ,token);

        strcpy(temp1->type,type);
        if(flag){
            *dataHead = *temp1;
            dataHead->next = NULL;
            flag=0;
        }else {
            while (dataHead->next != NULL) {
                dataHead = dataHead->next;
            }
            dataHead->next = temp1;

        }
        token = strtok(NULL, " ,");
    }

}
