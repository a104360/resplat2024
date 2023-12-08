#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/testes.h"

#define MAX_LINE_LENGTH 1024

int areFilesEqual(const char *file1Path, const char *file2Path) {
    FILE *file1 = fopen(file1Path, "r");
    FILE *file2 = fopen(file2Path, "r");

    if (file1 == NULL || file2 == NULL) {
        perror("Error opening files");
        return 0;  // Return false if there was an error opening files
    }

    char line1[MAX_LINE_LENGTH], line2[MAX_LINE_LENGTH];
    int lineNum = 1;

    while (1) {
        if (fgets(line1, MAX_LINE_LENGTH, file1) == NULL || fgets(line2, MAX_LINE_LENGTH, file2) == NULL) {
            break;  // End of file reached for either file
        }

        if (strcmp(line1, line2) != 0) {
            printf("Difference in line %d:\n", lineNum);
            printf("%s: %s", file1Path, line1);
            printf("%s: %s", file2Path, line2);
            fclose(file1);
            fclose(file2);
            return 0;  // Return false if lines differ
        }

        lineNum++;
    }

    if (fgets(line1, MAX_LINE_LENGTH, file1) != NULL || fgets(line2, MAX_LINE_LENGTH, file2) != NULL) {
        printf("Files have different lengths.\n");
        fclose(file1);
        fclose(file2);
        return 0;  // Return false if files have different lengths
    }

    fclose(file1);
    fclose(file2);

    return 1;  // Return true if all lines match
}

int confirmar(int argc, char ** argv) {
    
    int num = atoi(argv[1]);

    for(int i = 1;i <= num;i++){
        char comp[100];
        memset(comp,'\0',100);
        snprintf(comp, 99, "./Resultados/command%d_output.txt",i);
        char correct[100];
        memset(correct,'\0',100);
        snprintf(correct,99,"../../li3_fr/dataset/outputs/command%d_output.txt",i);
        if(areFilesEqual((const char *) correct,(const char *) comp)){
            printf("Command %d is correct!\n",i);
        }else break;
    }
    return 0;

}

