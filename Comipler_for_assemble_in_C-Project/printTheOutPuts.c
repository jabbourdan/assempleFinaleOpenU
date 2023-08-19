#include "printTheOutPuts.h"

int returnIfThereIsNoErrors(char* filename) {
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("File %s is empty.\n",filename);
        return 1;
    }
	
    fseek(file, 0, SEEK_END); /* Move to the end of the file */
    if (ftell(file) == 0 || file==NULL) {
        printf("File %s is empty.\n",filename);
        fclose(file);
        return 1; /* Return code for empty file */
    }else
        printf("File %s is not empty.\n",filename);

    fclose(file);

    return 0; /* Return code for non-empty file */
}
int binaryToDecimal(const char *binary) {
    int decimal = 0,i;
    for (i = 0; i < 6; i++) {
        decimal <<= 1;
        decimal |= binary[i] - '0';
    }
    return decimal;
}
void printTheBase64(struct machineCode* head,FILE* fileOb){
    struct machineCode* current = head;
    int decimal1 ,decimal2 ;
    const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char base64_char1,base64_char2;
    char first_6_bits[7]; /* Including null terminator */
    char second_6_bits[7]; /* Including null terminator */
    while(current != NULL){
        if(current->opcode[0] != '\0'){
            strncpy(first_6_bits, current->opcode, 6);
            first_6_bits[6] = '\0';
            /* Extract the second 6-bit portion and pad with zeros if needed */
            strncpy(second_6_bits, current->opcode + 6, 6);
            second_6_bits[6] = '\0';
            decimal1 = binaryToDecimal(first_6_bits);
            decimal2 = binaryToDecimal(second_6_bits);

            base64_char1 = base64_table[decimal1];
            base64_char2 = base64_table[decimal2];
            fprintf(fileOb, "%c%c\n", base64_char1, base64_char2);
        }
        if(current->firstArgAddress[0] != '\0'){
            strncpy(first_6_bits, current->firstArgAddress, 6);
            first_6_bits[6] = '\0';
            /* Extract the second 6-bit portion and pad with zeros if needed */
            strncpy(second_6_bits, current->firstArgAddress + 6, 6);
            second_6_bits[6] = '\0';
            decimal1 = binaryToDecimal(first_6_bits);
            decimal2 = binaryToDecimal(second_6_bits);

            base64_char1 = base64_table[decimal1];
            base64_char2 = base64_table[decimal2];
            fprintf(fileOb, "%c%c\n", base64_char1, base64_char2);
        }
        if(current->secondArgAddress[0] != '\0'){
            strncpy(first_6_bits, current->secondArgAddress, 6);
            first_6_bits[6] = '\0';
            /* Extract the second 6-bit portion and pad with zeros if needed */
            strncpy(second_6_bits, current->secondArgAddress + 6, 6);
            second_6_bits[6] = '\0';
            decimal1 = binaryToDecimal(first_6_bits);
            decimal2 = binaryToDecimal(second_6_bits);

            base64_char1 = base64_table[decimal1];
            base64_char2 = base64_table[decimal2];
            fprintf(fileOb, "%c%c\n", base64_char1, base64_char2);
        }
        current = current->next;
    }

}

void printTheObFile(struct machineCode* machineHead,char *fileName,const int *IC,const int *DC){
    char fileNameOb[MAX_LINE_LENGTH];
    FILE *fileOb;
    size_t fileNameLength ;
	
    char* copiedString = (char*)malloc(strlen(fileName) + 1);
    strcpy(copiedString, fileName);

    fileNameLength = strlen(copiedString);
    if (fileNameLength >= 3) {
        copiedString[fileNameLength - 3] = '\0';
    }
    sprintf(fileNameOb,"%s.ob", copiedString);
    fileOb = fopen(fileNameOb,"w");
    fprintf(fileOb , "   %d  %d \n",*IC-*DC-100 , *DC);
    printTheBase64(machineHead,fileOb);
    fclose(fileOb);
}
int checkIfTheEntryOrExtern(struct dataTable* dataHead,char* typeToCheck){
    struct dataTable* current = dataHead;

    while (current != NULL) {
        if (strcmp(current->type, typeToCheck) == 0) {
            return 1; /* Found the specified type, return 1 */
        }
        current = current->next;
    }
    return 0;
}

void printTheEntry(char* fileName,struct dataTable* dataHead,char* type){
    struct dataTable* current = dataHead;
    struct dataTable* temp;
    char fileNameEnt[MAX_LINE_LENGTH];
    FILE *fileEnt;
    size_t fileNameLength;
    char* copiedString = (char*)malloc(strlen(fileName) + 1);
    
    strcpy(copiedString, fileName);
    fileNameLength = strlen(copiedString);
    if (fileNameLength >= 3) {
        copiedString[fileNameLength - 3] = '\0';
    }
    sprintf(fileNameEnt, "%s.ent", copiedString);
    fileEnt = fopen(fileNameEnt,"w");
    while (current != NULL) {
        temp =dataHead;
        if (strcmp(current->type, type) == 0) {
            while(temp!= NULL){
                if(strcmp(temp->symbol, current->symbol) == 0 && strcmp(temp->type,type) != 0){
                    fprintf(fileEnt,"The symbol is : %s and the adress is %d\n",temp->symbol,temp->adress);
                }
                temp = temp->next;
            }
        }
        current = current->next;
    }
}
void printExtern(char* fileName,struct machineCode* machineHead,struct dataTable* dataHead,char *type){
    int count;
    struct dataTable* currentData = dataHead;
    struct machineCode* tempMachine;
    char fileNameExt[MAX_LINE_LENGTH];
    FILE *fileExt;
    size_t fileNameLength;
    char* copiedString = (char*)malloc(strlen(fileName) + 1);
    strcpy(copiedString, fileName);

    fileNameLength = strlen(copiedString);
    if (fileNameLength >= 3) {
        copiedString[fileNameLength - 3] = '\0';
    }
    sprintf(fileNameExt, "%s.ext", copiedString);
    fileExt = fopen(fileNameExt,"w");
    while(currentData != NULL){
        count = 100;
        tempMachine =machineHead;

        if(strcmp(currentData->type,type)==0){
            while(tempMachine != NULL){
                if(strcmp(currentData->symbol,tempMachine->firstArg)==0 || strcmp(currentData->symbol,tempMachine->secondArg)==0){
                    fprintf(fileExt,"The symbol is : %s and the value is %d\n",currentData->symbol,count+1);
                }
                if(tempMachine->opcode[0] != '\0'){
                    count++;
                }
                if(tempMachine->firstArgAddress[0] != '\0'){
                    count++;
                }
                if(tempMachine->secondArgAddress[0] != '\0'){
                    count++;
                }
                tempMachine = tempMachine->next;

            }

        }

        currentData = currentData ->next;
    }
}

void makeTheEntryAndExtern(struct dataTable* dataHead,struct machineCode* machineHead,char *fileName,char *type,char* extenstion){
    char fileNameOb[MAX_LINE_LENGTH];
    FILE *file;
    char *fileNameCopy = malloc(strlen(fileName) + 1);
    size_t fileNameLength;
    strcpy(fileNameCopy, fileName);
    fileNameLength = strlen(fileName);
    if (fileNameLength >= 3) {
        fileNameCopy[fileNameLength - 3] = '\0';
    }
    sprintf(fileNameOb, "%s.%s", fileNameCopy,extenstion);
    file = fopen(fileNameOb,"w");
    if(strcmp(type,"extern") == 0){
        printExtern(fileName,machineHead,dataHead,type);
    }else
        printTheEntry(fileName,dataHead,type);

    fclose(file);
}
