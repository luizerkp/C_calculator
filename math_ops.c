#include "main.h"
#include "macro_definitions.h"
#include "external_var.h"
#include "sanity_checks.h"
#include "math_ops.h"

// Mathematical Operation funtions
long double sum(long double arr[], int numbers)
{
    long double results = 0;
    for (int i = 0; i < numbers_counter; i++)
    {
        results += arr[i];
    }
    return results;
}
long double sub(long double arr[], int numbers)
{
    long double results = arr[0];
    for (int i = 1; i < numbers_counter; i++) 
    {
        results -= arr[i];
    }
    return results;
}
long double multiply(long double arr[], int numbers)
{
    long double results = arr[0];
    for (int i = 1; i < numbers_counter; i++)
    {
        results *= arr[i];
    }
    return results;
}
long double divide(long double arr[], int numbers)
{
    long double results = arr[0];
    for (int i = 1; i < numbers_counter; i++)
    {
        results /= arr[i];
    }
    return results;
}
long double exponent(long double arr[], int numbers)
{
    return 1;
}
long double mod(long double arr[], int numbers)
{
    return 1;
}
long double logarithm(long double arr[], int numbers)
{
    return 1;
}
long double root(long double arr[], int numbers)
{
    return 1;
}
long double percent(long double arr[], int numbers)
{
    return 1;
}
long double factorial(long double arr[], int numbers)
{
    return 1;
}