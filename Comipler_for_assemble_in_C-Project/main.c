#include "main.h"

int check_length_lines(char *filename);
void printAllMachineCodes(struct machineCode* head) {
    struct machineCode* current = head;
    int i;
    while (current != NULL) {
        printf("The Opcode: ");
        for (i = 0; i < 12; i++) {
            printf("%c", current->opcode[i]);
        }
        printf("\nThe First code: ");
        for (i = 0; i < 12; i++) {
            printf("%c", current->firstArgAddress[i]);
        }
        printf("\nThe second code: ");
        for (i = 0; i < 12; i++) {
            printf("%c", current->secondArgAddress[i]);
        }
        printf("\n");
        printf("\n");
        current = current->next;
    }
}
int main(int argc, char *argv[]) {
    int i,IC, DC,numMcro;
    const char *extension_as = ".as";
    int max_length;
    int valid ;
    struct  machineCode* machineHead;
    struct  dataTable* dataHead;
    char errorFile[30];
    char *fileEnd;
    char *file;
    struct Macro* head;
    const char* baseFilename = "errorFile"; /* Base filename */
    const char* extension_txt = ".txt";   /* File extension */
    size_t filenameLength;
    size_t extensionLength;
    if (argc == 1) {
        return 1;
    }
    for (i = 1; i < argc; i++) {
 
        filenameLength = strlen(argv[i]);
        extensionLength = strlen(extension_as);
        fileEnd=NULL;
        dataHead = NULL;
        machineHead = NULL;
        dataHead = (struct dataTable*)malloc(sizeof(struct dataTable));
        dataHead->next = NULL;
        machineHead = (struct machineCode*)malloc(sizeof(struct machineCode));
        machineHead->next = NULL;
        file = (char *)malloc((filenameLength + extensionLength + 1) * sizeof(char));
        fileEnd = file;
        strcpy(file, argv[i]);
        strcat(file, extension_as);
        
        sprintf(errorFile, "%s%d%s", baseFilename, i, extension_txt);
	
        max_length = check_length_lines(file);
        if (max_length <= 0) {
            printf("This file %s has line bigger than 80\n",file);
            continue;
        }
        numMcro = isThereMcro(file);
        if(numMcro > 0){
            valid = checkMacro(file);
		
            if(valid){
                fileEnd = makeAmFile(file);
                head = NULL;
                insertTheMacro(errorFile,&head, file);
                reWriteAmFile(&head, file,fileEnd);
                freeList(head);

            }
        }

        firstcheck(fileEnd,errorFile,dataHead,machineHead,&IC,&DC);
        secondCheck(fileEnd,errorFile,dataHead,machineHead,&IC,&DC);
        /*printAllMachineCodes(machineHead); (You can remove the comment to see the machineCode here !)*/ 
        
        if(returnIfThereIsNoErrors(errorFile)){
            printTheObFile(machineHead,fileEnd,&IC,&DC);
            if(checkIfTheEntryOrExtern(dataHead,"entry")){
                makeTheEntryAndExtern(dataHead,machineHead,fileEnd,"entry","ent");
            }
            if(checkIfTheEntryOrExtern(dataHead,"extern")){
                makeTheEntryAndExtern(dataHead,machineHead,fileEnd,"extern","ext");
            }
        }
        free(file);
    }
    return 0;
}

int check_length_lines(char* filename) {

    FILE* file;
    
    char line[MAX_LINE_LENGTH+1];
    unsigned long maxLineLength = 0,lineLength,length_line;
    /* Open the file in read mode */
    file = open_file(filename, "r");


    /* Read each line of the file */
    while (fgets(line, sizeof(line), file)) {
        lineLength = strlen(line);

        /* Remove the newline character at the end of the line */
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
            lineLength--;
        }

        /* Update the maximum line length if necessary */
        if (lineLength > maxLineLength) {
            maxLineLength = lineLength;
        }
    }
    fclose(file);

    length_line = maxLineLength +1;
    if(length_line <=80){
        return 1;
    }
    else
        return 0;
}
