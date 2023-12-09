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

int validation(const char ** filePath){
    FILE *file1 = fopen(filePath[0], "r");
    char file2Path[50];
    memset(file2Path,'\0',60);
    snprintf(file2Path,59,"../../li3_fr/dataset/data/users_errors.csv");
    FILE *file2 = fopen(file2Path, "r");

    if (file1 == NULL || file2 == NULL) {
        perror("Validation file does not exist");
        return 0;  // Return false if there was an error opening files
    }

    char line1[MAX_LINE_LENGTH], line2[MAX_LINE_LENGTH];
    int lineNum = 1;

    while (1) {
        if (fgets(line1, MAX_LINE_LENGTH, file1) == NULL || fgets(line2, MAX_LINE_LENGTH, file2) == NULL) {
            break;  // End of file reached for either file
        }

        if (strcmp(line1, line2) != 0) {
            printf("Difference in line %d:\n of users", lineNum);
            printf("%s: %s", filePath[0], line1);
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

    file1 = fopen(filePath[1], "r");
    memset(file2Path,'\0',60);
    snprintf(file2Path,59,"../../li3_fr/dataset/data/reservations_errors.csv");
    file2 = fopen(file2Path, "r");

    if (file1 == NULL || file2 == NULL) {
        perror("Validation file does not exist");
        return 0;  // Return false if there was an error opening files
    }

    lineNum = 1;

    while (1) {
        if (fgets(line1, MAX_LINE_LENGTH, file1) == NULL || fgets(line2, MAX_LINE_LENGTH, file2) == NULL) {
            break;  // End of file reached for either file
        }

        if (strcmp(line1, line2) != 0) {
            printf("Difference in line %d:\n of reservations", lineNum);
            printf("%s: %s", filePath[1], line1);
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


    file1 = fopen(filePath[2], "r");
    memset(file2Path,'\0',60);
    snprintf(file2Path,59,"../../li3_fr/dataset/data/flights_errors.csv");
    file2 = fopen(file2Path, "r");

    if (file1 == NULL || file2 == NULL) {
        perror("Validation file does not exist");
        return 0;  // Return false if there was an error opening files
    }

    lineNum = 1;

    while (1) {
        if (fgets(line1, MAX_LINE_LENGTH, file1) == NULL || fgets(line2, MAX_LINE_LENGTH, file2) == NULL) {
            break;  // End of file reached for either file
        }

        if (strcmp(line1, line2) != 0) {
            printf("Difference in line %d:\n of flights", lineNum);
            printf("%s: %s", filePath[2], line1);
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


    file1 = fopen(filePath[3], "r");
    memset(file2Path,'\0',60);
    snprintf(file2Path,59,"../../li3_fr/dataset/data/passengers_errors.csv");
    file2 = fopen(file2Path, "r");

    if (file1 == NULL || file2 == NULL) {
        perror("Validation file does not exist");
        return 0;  // Return false if there was an error opening files
    }

    lineNum = 1;

    while (1) {
        if (fgets(line1, MAX_LINE_LENGTH, file1) == NULL || fgets(line2, MAX_LINE_LENGTH, file2) == NULL) {
            break;  // End of file reached for either file
        }

        if (strcmp(line1, line2) != 0) {
            printf("Difference in line %d:\n of passangers", lineNum);
            printf("%s: %s", filePath[3], line1);
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

    printf("\nAll errors matched with the dataset errors!\n\n");
    return 1;  // Return true if all lines match
}

int confirmar(int argc, char ** argv) {

    char users[60];
    memset(users,'\0',60);
    snprintf(users,59,"./Resultados/users_errors.csv");
    
    char reservations[60];
    memset(reservations,'\0',60);
    snprintf(reservations,59,"./Resultados/reservations_errors.csv");

    char flights[60];
    memset(flights,'\0',60);
    snprintf(flights,59,"./Resultados/flights_errors.csv");

    char passangers[60];
    memset(passangers,'\0',60);
    snprintf(passangers,59,"./Resultados/passengers_errors.csv");

    char ** files = malloc(sizeof(char *) * 4);

    files[0] = users;
    files[1] = reservations;
    files[2] = flights;
    files[3] = passangers;

    validation((const char **) files);

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
    
    free(files);

    return 0;

}

