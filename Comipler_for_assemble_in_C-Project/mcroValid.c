#include "mcroValid.h"

funNotAllowed macroNames[24] = {
        {"mov"},
        {"cmp"},
        {"add"},
        {"sub"},
        {"not"},
        {"clr"},
        {"lea"},
        {"inc"},
        {"dec"},
        {"jmp"},
        {"bne"},
        {"red"},
        {"prn"},
        {"jsr"},
        {"rts"},
        {"stop"},
        {"@r1"},
        {"@r2"},
        {"@r3"},
        {"@r4"},
        {"@r5"},
        {"@r6"},
        {"@r7"},
        {"@r0"}
};

FILE* open_file(const char* file, char* operator) {
    FILE* inputFile = fopen(file, operator);
    if (inputFile == NULL) {
        printf("Unable to open the file\n");
    }
    return inputFile;
}
int isValidRestrictedWord(const char* word) {
    int i;
    for (i = 0; i < 24; i++) {
        if (strcmp(word, macroNames[i].name) == 0) {
            return 0;
        }
    }
    return 1;
}


int validMacro(char* file) {
    char line[MAX_LINE_LENGTH];
    const char* word = "mcro";
    const char* endWord = "endmcro";
    int found = 0,validEndMacro,tokenIndex;
    int endfound = 0;
    int i;
    char* nextWord;
    char* additionalWord;
    FILE* inputFile = open_file(file,"r");

    /* Read each line of the file */
    while (fgets(line, sizeof(line), inputFile)) {
        /* Tokenize the line into words */
        char* token = strtok(line, " \t\n\r");

        /* Check each word */
        while (token != NULL) {
            /* Compare the word with the target word */
            if (strcmp(token, word) == 0) {
                /* Check if there are only spaces or no spaces before the keyword */
                int tokenIndex = token - line;
                int validMacro = 1;

                /* Check before the keyword */
                for (i = 0; i < tokenIndex; i++) {
                    if (line[i] != ' ') {
                        validMacro = 0;
                        break;
                    }
                }

                /* Check if the next word exists */
                nextWord = strtok(NULL, " \t\n\r");


                if (nextWord == NULL || !isValidRestrictedWord(nextWord)) {
                    validMacro = 0;
                    return 0;
                } else {
                    /* Check if there are additional words after the next word */
                    additionalWord = strtok(NULL, " \t\n\r");
                    if (additionalWord != NULL) {
                        validMacro = 0;
                    }
                }
                if (validMacro) {
                    found = 1;
                    break;
                }else
                    found = 0;
                break;

            }

            if (strcmp(token, endWord) == 0) {
                /* Check if there are only spaces or no spaces before the keyword */
                tokenIndex = token - line;
                validEndMacro = 1;

                /* Check before the keyword */
                for (i = 0; i < tokenIndex; i++) {
                    if (line[i] != ' ') {
                        validEndMacro = 0;
                        break;
                    }
                }

                /* Check if there are additional words after the keyword */
                nextWord = strtok(NULL, " \t\n\r");
                if (nextWord != NULL) {
                    validEndMacro = 0;
                }

                if (validEndMacro) {
                    endfound = 1;
                    break;
                } else {
                    endfound = 0;
                    break;
                }
            }

            token = strtok(NULL, " \t\n\r");
        }




    }

    fclose(inputFile);

    if (found&endfound) {
        return 1;
    } else {
        return 0;
    }
}

int isThereMcro(char* file){
    const char* targetWord = "mcro";
    FILE* inputFile = open_file(file,"r");
    int index = 0;
    char* token;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), inputFile)) {
        token = strtok(line, " \t\n\r");
        while (token != NULL) {
            if (strcmp(token, targetWord) == 0) {
                index++;
            }
            token = strtok(NULL, " \t\n\r");
        }
    }
    fclose(inputFile);
    return index;
}

int checkMacro(char* file){
    if(isThereMcro(file)) {
        if (validMacro(file))

            return 1;
    }
    return 0;
}

