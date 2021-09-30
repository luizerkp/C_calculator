#ifndef SANITY_CHECKS_H
#define SANITY_CHECKS_H

// provides a general error message for missing or unsuported math operation 
void error_message(int n);

// provides error message for invalid number input
void invalid_number_error(void);

// check that the operation is within supported list 
bool check_operation(char *n, char **ops);

// checks number polarity
bool is_positive_negative (char n);

// check that input is a valid number 
bool check_number(char * n);

// checks if the input is "start" which indicates the user wants to start calculation
bool check_end(char *n);

// checks to see if the number input is a decimal or not 
bool is_decimal(char *n);

// checks if decimal input is within max digits limit of 6 after the decimal point
bool max_decimal(char *n);

// checks if no decimal input is within max digits limit of 12 befoer the decimal point
bool max_whole(char *n);

// checks only two inputs are entered for math operations tha require two inputs i.e. modulos 
bool check_two(char *n);

// checks that only one input is entered for math operations that require one input i.e. factorial
bool check_one(char *n);

// checks that eihter one or two inputs required, this is used for starting opearations automatically after number of req. inputs
bool check_one_two(char *n, int numbers); 

#endif
