#include "main.h"
#include "macro_definitions.h"
#include "external_var.h"
#include "sanity_checks.h"
#include "math_ops.h"

// *** MAX_OPERATIONS, MAX_DIGITS_WHOLE, MAX_DIGITS_DECIMAL, and MAX_LENGTH are defined in macro_definitions.h ***
// determines which function to call based on user input
int determine_function(char * n, char **ops);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        error_message(argc);
        return 1;
    }

    // Stores all the allowed operations that can be entered at the cmd line
    // exported in external_var.h  
    char *operations_arr[MAX_OPERATIONS] = {"sum", "sub", "divide", "multiply", "mod", "logarithm", "exponent", "root", "percent", "factorial"};

    if (!check_operation(argv[1], operations_arr))
    {
        error_message(argc);
        return 1;
    }

    printf("***Intructions:\nEnter each number to be computed when prompted or enter 'start' if less than 11 numbers are needed.\n");
    printf("Max distinct numbers is 11 and Max number length is 12 digits plus 6 decimal places for floating point numbers\n");
    printf("For order dependant binary operations 1st input(*) and 2nd input(**) -->{*10 mod **1} {*10(base),**2(exp) ect...}\n");
    printf("Accepted Operations: sum, sub, divide, multiply, mod, logarithm, exponent, root, percent, collatz or factorial\n");
    printf("\n");


    // stores user input
    char string_numbers_input[MAX_LENGTH];

    // copies user input into an array of strings
    char string_numbers_bucket[MAX_OPERATIONS][MAX_LENGTH];

    // tracks the number of valid inputs by the user and is used to detmermine the size of the numbers-bucket array
    // exported in external_var.h 
    int numbers_counter = 0;

    // will store all the function pointers **Note that index oder must match operations_arr array**
    // exported in external_var.h 
    long double (*operration_functions_pointers[MAX_OPERATIONS])(long double arr[], int numbers) = {sum, sub, divide, multiply, mod, logarithm, exponent, root, percent, factorial};

    // Note to self: in the future I want to check for way to use malloc to accomplish this part and see how this affects performance.
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

        if (check_end(string_numbers_input))
        {
            break;
        }

        if (!check_number(string_numbers_input))
        {
            invalid_number_error();
            return 1;
        }

        if (!max_whole(string_numbers_input))
        {
            invalid_number_error();
            return 1;
        }

        bool decimal = is_decimal((string_numbers_input));

        if (decimal && !max_decimal(string_numbers_input))
        {
            invalid_number_error();
            return 1;
        }

        if (strcasecmp(string_numbers_input, "start") != 0)
        {
            strcpy(string_numbers_bucket[i], string_numbers_input);
            numbers_counter++;
        }
    }

    if (check_two (argv[1]) && (numbers_counter != 2))
    {
        invalid_number_error();
        return 1;
    }

    // will store the converted numbers, chose long double data type as that can store the largest number accepted
    long double numbers_bucket[numbers_counter];

    // ** This is used for testing correct ammount of numbers are recorded, remove for final
    // printf("%d\n", numbers_counter);

    // Will convert user string number input to long double data type so we can do math with it
    for (int i = 0; i < numbers_counter; i++)
    {
        numbers_bucket[i] = strtold(string_numbers_bucket[i], NULL);
        printf("Converted Number: %0.6LF\n", numbers_bucket[i]);
    }

    // determines which function index to pass to the 'operration_functions_pointers' array
    int operation = determine_function(argv[1], operations_arr);

    // error check in the event that determine_funtion fails for some reason
    if (operation == -1)
    {
        printf("Error unable to determine function\n");
        return 1;
    }

    // TODO: find out how to handle operations that require qualifies i.e 'number' mod 10 or percent of number first number is whole second is percent

    // calls the correct Math operation function from the function pointers array
    long double answer = (*operration_functions_pointers[operation])(numbers_bucket, numbers_counter);

    // ** used for testing user input remove for final
    printf("The operation index is: %d\n", operation);

    // prints final answer
    printf("Results: %.6LF\n", answer);
}
// funtion indentifier TODO: inplement way that the number returned is the index for operation_funtions_pointers
int determine_function(char * n, char **ops)
{
    for (int i = 0; i < MAX_OPERATIONS; i++)
    {
        if (strcasecmp(n, ops[i]) == 0)
            return i;
    }
    return -1;
}