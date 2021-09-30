#ifndef EXTERNAL_VAR_H
#define EXTERNAL_VAR_H

// Stores all the allowed operations to check a cmd line
// declared in calcualtor.c 
extern char *operations_arr[];

// tracks the number of valid inputs by the user and is used to detmermine the size of the numbers-bucket array declared in calcualtor.c
// declared in calcualtor.c
extern int numbers_counter;

// Stores function pointers in an array
// delared in calculator.c
extern long double (*operration_functions_pointers[])(long double arr[], int numbers);

#endif
