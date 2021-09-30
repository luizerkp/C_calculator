#include "main.h"
#include "macro_definitions.h"
#include "external_var.h"
#include "sanity_checks.h"

// provides a general error message for missing or unsuported math operation 
void error_message(int n)
{
    if ( n != 2)
       printf("Usage: ./calculator operation\n");
    else
        printf("Mathematical Opreation Ussuported\nAccepted Operations: sum, sub, divide, multiply, mod, logarithm, exponent, root, percent, factorial\n");
}

// provides error message for invalid number input
void invalid_number_error(void)
{
    printf("Error: Only 'start' or a valid number input accepted. Max length 12 digits plus 6 decimal places allowed\n");
    printf("For Operations that require two inputs like mod, root, logarithm, exponent, and percent only 2 numbers accepted\n");
}


// check that the operation is within supported list 
bool check_operation(char *n, char **ops)
{
    for (int i = 0; i < MAX_OPERATIONS; i++)
    {
        if (strcasecmp(n, ops[i]) == 0)
            return true;
    }
    return false;
}

// checks number polarity
bool is_positive_negative (char n)
{
    if (n == '-' || n == '+')
    {
        return true;
    }
    return false;
}
// checks for valid number input
bool check_number(char *n)
{
    bool floating_point_found = false;

    for (int i = 0, c = strlen(n); i < c; i++)
    {
        if ((is_positive_negative(n[i]) && i == 0) || isdigit(n[i]))
        {
            continue;
        }
        else if (n[i] == '.' && floating_point_found == false)
        {
            floating_point_found = true;
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

// checks if user inputs "start" to indicate start operation
bool check_end (char * n)
{
    if (strcasecmp(n, "start") == 0)
        return true;
    else
        return false;
}

// checks to see if the number input is a decimal or not
bool is_decimal(char *n)
{
    bool floating_point_found = false;
    for (int i = 0, c = strlen(n); i < c; i++)
    {
        if ((is_positive_negative(n[i]) && i == 0)|| isdigit(n[i]))
        {
            continue;
        }
        else if (n[i] == '.' && floating_point_found == false)
        {
            floating_point_found = true;
            continue;
        }
    }
    return floating_point_found;
}

// checks if decimal input is within max digits limit of 6 after the decimal point
bool max_decimal(char *n)
{
    bool floating_point_found = false;
    int decimal_places = 0;
    for (int i = 0, c = strlen(n); i < c; i++)
    {
        if (n[i] == '.' && floating_point_found == false)
        {
            floating_point_found = true;
            continue;
        }
        else if (floating_point_found == true)
        {
            decimal_places++;
        }
    }
    if (decimal_places <= MAX_DIGITS_DECIMAL)
    {
        return true;
    }
    return false;
}

// checks if no decimal input is within max digits limit of 12 before the decimal point
bool max_whole(char *n)
{
    int digits = 0;

    for (int i = 0, c = strlen(n); i < c; i++)
    {
        if ((is_positive_negative(n[i]) && i == 0))
        {
            continue;
        }
        else if (n[i] == '.')
        {
            break;
        }
        else if(isdigit(n[i]))
        {
            digits++;
        }
    }

    if (digits <= MAX_DIGITS_WHOLE)
    {
        printf("digits are : %d\n", digits);
        return true;
    }
    printf("digits are : %d\n", digits);
    return false;
}

// checks only two inputs are entered for math operations tha require two inputs i.e. modulos 
bool check_two(char *n)
{
    char *two_ops[5]= {"mod", "logarithm", "exponent", "root", "percent"};
    for (int i = 0; i < 5; i++)
    {
        if(strcasecmp(n, two_ops[i]) == 0)
        {
            return true;
        }
    }
    return false;
}
bool check_one(char *n)
{
    char *operation = "factorial";
    if (strcasecmp(n, operation) == 0)
    {
        return true;
    }
    return false; 
}

bool check_one_two(char *n, int numbers)
{
    bool start = false;
    if (check_two (n) && (numbers == 2))
    {
        start = true;
    }
    if (check_one(n) && (numbers == 1))
    {
        start = true;
    }
    return start;
}