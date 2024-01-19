#ifndef CONTROLLER_H
#define CONTROLLER_H

/**
 * @brief Executes the program in batch mode
 * @param argv Paths to the CSVs and the input
*/
void run(char **);

/**
 * @brief Executes the batch mode and performs 
 * tests for time,memory and correction
 * @param argv Paths to the CSVs, input and correct outputs
*/
void test(char **);

#endif