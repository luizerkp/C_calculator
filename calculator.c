#include <stdio.h>
#include <float.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>


// defines how many numbers can be computed
#define MAX_OPERATIONS 10

// defines the maximum number digits before decimal point
#define MAX_DIGITS_WHOLE 32

// defines maximum number of digits after decimal point
#define MAX_DIGITS_DECIMAL 32

// defines maximum total lenght MAX_DIGITS_WHOLE + MAX_DIGITS_DECIMAL + 2 for '+/-' and/or '.' + 1 for null terminator '\0'
#define MAX_LENGTH 35

// used to determine whether to use scientific notation or not i.e fortmat specifiers %e vs %LF
const long double DISPLAY_LIMIT_MAX = 9999999999.999999;
const long double DISPLAY_LIMIT_MIN = 0.000001;

// Sanity checks
void error_message(int n);
void invalid_number_error(void);
void invalid_input_error(char *n);
bool is_decimal(char *n);
bool max_decimal(char *n);
void overflow_error_message(void);
bool max_whole(char *n);
bool check_operation(char *n, char **ops);
bool check_number(char * n);
bool check_end(char *n);
bool check_two(char *n);
bool check_one(char *n);
bool check_one_two(char *n, int numbers);
bool valid_entry_for_operation(int index, long double arr[]);
bool check_root(long double arr[]);
bool check_log(long double arr[]);
bool check_factorial(long double arr[]);
bool overflow_limits (long double n);

// checks number polarity
bool is_positive_negative (char n);

// Funtion declations for Mathematical operations
long double sum(long double arr[], int numbers);
long double sub(long double arr[], int numbers);
long double multiply(long double arr[], int numbers);
long double divide(long double arr[], int numbers);
long double exponent(long double arr[], int numbers);
long double mod(long double arr[], int numbers);
long double logarithm (long double arr[], int numbers);
long double root(long double arr[], int numbers);
long double percent(long double arr[], int numbers);
long double factorial(long double arr[], int numbers);

// helper function
long double recursive_fact(long double n);

// determines which funcition to call based on user inpuut
int determine_function(char *n, char **ops);

int main(int argc, char* argv[])
{
     if (argc != 2)
    {
        error_message(argc);
        return 1;
    }

    // Stores all the allowed operations that can be entered at the cmd line
    char *operations_arr[MAX_OPERATIONS] = {"sum", "sub", "divide", "multiply", "mod", "log", "exponent", "root", "percent", "factorial"};

    if (!check_operation(argv[1], operations_arr))
    {
        error_message(argc);
        return 1;
    }

    printf("***Intructions:\nEnter each number to be computed when prompted or enter 'start' if less than 10 numbers are needed.\n");
    printf("Max lenght is 32 digits including digits before/after decimal point\n");
    printf("For order dependant binary operations 1st input(*) and 2nd input(**) -->{*10 mod **1} ect...}\n");
    printf("Accepted Operations: sum, sub, divide, multiply, mod, log, exponent, root, percent, collatz or factorial\n");
    printf("\n");


    // stores user input
    char string_numbers_input[MAX_LENGTH];

    // copies user input into an array of strings
    char string_numbers_bucket[MAX_OPERATIONS][MAX_LENGTH];

    // tracks the number of valid inputs by the user and is used to detmermine the size of the numbers-bucket array
    int numbers_counter = 0;

    // will store all the function pointers **Note that index oder must match operations_arr array**
    long double (*operration_functions_pointers[MAX_OPERATIONS])(long double arr[], int numbers) = {sum, sub, divide, multiply, mod, logarithm, exponent, root, percent, factorial};

    for (int i = 0; i < MAX_OPERATIONS; i++)
    {
        // starts calculation after two inputs if mathematical operation requires only two inputs or one input
        // for those that require one.
        if (check_one_two(argv[1], numbers_counter))
        {
            break;
        }

        printf("Enter Number: ");
        fgets(string_numbers_input, sizeof(string_numbers_input), stdin);

        // remove trailing \n due to fgets
        string_numbers_input[strcspn(string_numbers_input, "\n")] = 0;

        int len = strlen(string_numbers_input);

        if (len == 0)
        {
            invalid_number_error();
            return 1;
        }

        // checks if "start" command was inputed
        if (check_end(string_numbers_input))
        {
            break;
        }

        // check if input is a valid number
        if (!check_number(string_numbers_input))
        {
            invalid_number_error();
            return 1;
        }

        // check if number is within max digit limit
        if (!max_whole(string_numbers_input))
        {
            invalid_number_error();
            return 1;
        }

        // checks if inout is decimal and if it is within digit limit
        bool decimal = is_decimal((string_numbers_input));
        bool within_max_decimal_places = max_decimal(string_numbers_input);

        if (decimal && !within_max_decimal_places)
        {
            invalid_number_error();
            return 1;
        }

        // loads input into array
        if (strcasecmp(string_numbers_input, "start") != 0)
        {
            strcpy(string_numbers_bucket[i], string_numbers_input);
            numbers_counter++;
        }
    }

    // will store the converted numbers, chose long double data type as that can store the largest number accepted
    long double numbers_bucket[MAX_OPERATIONS];

    // Will convert user string number input to long double data type so we can do math with it
    for (int i = 0; i < numbers_counter; i++)
    {
        numbers_bucket[i] = strtold(string_numbers_bucket[i], NULL);
    }

    // checks for valid input requirements for root, log, and factorial
    char *ops_with_requirements[3] = {"root", "log", "factorial"};
    bool check_valid = true;

    for (int i = 0; i < 3; i++)
    {
        if (strcasecmp(ops_with_requirements[i], argv[1]) == 0)
        {
            check_valid = valid_entry_for_operation(i , numbers_bucket);
        }
    }

    // if input is not valid for root, log, or factorial returns error message
    if (!check_valid)
    {
        invalid_input_error(argv[1]);
        return 1;
    }

    // determines which function index to pass to the 'operration_functions_pointers' array
    int operation = determine_function(argv[1], operations_arr);

    // error check in the event that determine_funtion fails for some reason
    if (operation == -1)
    {
        printf("Error unable to determine function\n");
        return 1;
    }

    // calls the correct Math operation function from the function pointers array
    long double answer = (*operration_functions_pointers[operation])(numbers_bucket, numbers_counter);

    // checks if answer is beyond MAX MIN long double value
    bool check_ldbl_limits = overflow_limits(answer);

    if (check_ldbl_limits)
    {
        overflow_error_message();
        return 1;
    }

    // prints final answer; if answer is greater than 10 digits will use scientific notation instead.
    if (fabsl(answer) > DISPLAY_LIMIT_MAX || (fabsl(answer) > 0 && fabsl(answer) < DISPLAY_LIMIT_MIN))
    {
        printf("Results: %Le\n", answer);
    }
    else
    {
       printf("Results: %.7Lf\n", answer);
    }

}

// provides a general error message for missing or unsuported math operation
void error_message(int n)
{
    if ( n != 2)
       printf("Usage: ./calculator operation\n");
    else
        printf("Mathematical Opreation Ussuported\nAccepted Operations: sum, sub, divide, multiply, mod, log, exponent, root, percent, factorial\n");
}

// provides error message for invalid number input
void invalid_number_error(void)
{
    printf("Error: Only 'start' or a valid number input accepted. Max length 32 digits including digits before/after decimal point\n");
    printf("For Operations that require two inputs like mod, root, log, exponent, and percent only 2 numbers accepted\n");
}

// provide error when negative number is entered
void invalid_input_error(char *n)
{
    if (strcasecmp(n, "log") == 0)
    {
        printf("Only positive, non-zero values accepted for log operation\n");
    }
    else
    {
        printf("Only positive values accepted for root and factorial operations\n");
    }

}

// displays error message when answer is beyond long double limits.
void overflow_error_message(void)
{
    printf("Results are beyond the max/min possible value for this Calculator\n");
}

// check that the operation is within supported list
bool check_operation(char *n, char **ops)
{
    bool suported = false;
    for (int i = 0; i < MAX_OPERATIONS; i++)
    {
        if (strcasecmp(n, ops[i]) == 0)
            suported = true;
    }
    return suported;
}

// checks number polarity
bool is_positive_negative (char n)
{
    bool found = false;

    if (n == '-' || n == '+')
    {
        found = true;
    }
    return found;
}

// checks for valid number input
bool check_number(char *n)
{
    bool floating_point_found = false;
    bool valid_number = true;
    bool polarity = is_positive_negative(n[0]);

    for (int i = 0, c = strlen(n); i < c; i++)
    {
        if ((polarity == true && i == 0) || (isdigit(n[i]) && valid_number == true))
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
            valid_number = false;
        }
    }
    return valid_number;
}

// checks if user inputs "start" to indicate start operation
bool check_end (char * n)
{
    bool found = false;

    if (strcasecmp(n, "start") == 0)
        found = true;

    return found;
}

// checks if number inout is decimal
bool is_decimal(char *n)
{
    bool floating_point_found = false;

    for (int i = 0, c = strlen(n); i < c; i++)
    {
        if (n[i] == '.' && floating_point_found == false)
        {
            floating_point_found = true;
            continue;
        }
        else if (n[i] == '.' && floating_point_found == true)
        {
            floating_point_found = false;
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

    bool within_max = false;

    if (decimal_places <= MAX_DIGITS_DECIMAL)
    {
        within_max = true;
    }
    return within_max;
}

// checks if input is within max digits limit of 12 before the decimal point
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

    bool within_limits = false;

    if (digits <= MAX_DIGITS_WHOLE)
    {
        within_limits = true;
    }

    return within_limits;
}

// checks if only two inputs are entered for math operations tha require two inputs i.e. modulos
bool check_two(char *n)
{
    char *two_ops[4]= {"mod", "exponent", "root", "percent"};
    bool found = false;

    for (int i = 0; i < 4; i++)
    {
        if(strcasecmp(n, two_ops[i]) == 0)
        {
            found = true;
        }
    }
    return found;
}

// function indentifier
int determine_function(char *n, char **ops)
{
    int operation = -1;

    for (int i = 0; i < MAX_OPERATIONS; i++)
    {
        if (strcasecmp(n, ops[i]) == 0)
        {
            operation = i;
        }
    }
    return operation;
}

// checks if only one input is required for math operation
bool check_one(char *n)
{
    char *operation[2] = {"factorial", "log"};
    bool found = false;

    for (int i = 0; i < 2; i++)
    {
        if (strcasecmp(n, operation[i]) == 0)
        {
            found = true;
        }
    }

    return found;
}

// triggers start of operation after one or two inputs when required
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

// checks if operations has non-negative numbers or non-zero requirements i.e. log
bool valid_entry_for_operation(int index, long double arr[])
{
    bool valid = true;
    bool (*check_operation_requirements[3])(long double arr[]) = {check_root, check_log, check_factorial};

    valid = check_operation_requirements[index](arr);

    return valid;
}

// check for required inputs for root operations
bool check_root(long double arr[])
{
    bool valid = true;

    if (arr[0] < 0 || arr[1] <= 0)
    {
        valid = false;
    }
    return valid;
}

// check for required inputs for log operations
bool check_log(long double arr[])
{
    bool valid = true;

    if (arr[0] <= 0)
    {
        valid = false;
    }
    return valid;
}

// check for required inputs for factorial operations
bool check_factorial(long double arr[])
{
    bool valid = true;

    if (arr[0] < 0)
    {
        valid = false;
    }
    return valid;
}

// Mathematical Operation funtions
long double sum(long double arr[], int numbers)
{
    long double results = 0;
    for (int i = 0; i < numbers; i++)
    {
        results += arr[i];
    }
    return results;
}

long double sub(long double arr[], int numbers)
{
    long double results = arr[0];
    for (int i = 1; i < numbers; i++)
    {
        results -= arr[i];
    }
    return results;
}

long double multiply(long double arr[], int numbers)
{
    long double results = arr[0];
    for (int i = 1; i < numbers; i++)
    {
        results *= arr[i];
    }
    return results;
}

long double divide(long double arr[], int numbers)
{
    long double results = arr[0];
    for (int i = 1; i < numbers; i++)
    {
        results /= arr[i];
    }
    return results;
}

long double exponent(long double arr[], __attribute__((unused)) int numbers)
{
    return pow(arr[0], arr[1]);
}

long double mod(long double arr[], __attribute__((unused)) int numbers)
{
    return fmod(arr[0], arr[1]);
}

long double root(long double arr[], __attribute__((unused)) int numbers)
{
    return pow(arr[0], 1.0 / arr[1]);
}

long double percent(long double arr[], __attribute__((unused)) int numbers)
{
    long double total = arr[0];
    long double part = arr[1];
    long double results = (part / total) * 100.0;
    return results;
}

long double logarithm(long double arr[], __attribute__((unused)) int numbers)
{
    return log10(arr[0]);
}

long double factorial(long double arr[], __attribute__((unused)) int numbers)
{
    // returns double the max number a long double can store to prevent too many recursions
    // n! of any number higher than 1754 produces a number that is larger than __LDBL_MAX__
    long double answer;
    if (arr[0] > 1800)
    {
        answer = __LDBL_MAX__ * 2;
    }
    else
    {
        answer = recursive_fact(arr[0]);
    }

    return answer;
}

// source CS50 week 3 youtube video with Doug Lloyd
long double recursive_fact(long double n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * recursive_fact(n - 1);
    }
}

// check if value is greater than long double min/max limits
bool overflow_limits (long double n)
{
    bool beyond_max_min = false;

    if (fabsl(n) > __LDBL_MAX__)
    {
        beyond_max_min = true;
    }

    return beyond_max_min;
}