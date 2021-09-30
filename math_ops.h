#ifndef MATH_OPS_H
#define MATH_OPS_H
#include "main.h"
#include "macro_definitions.h"
#include "external_var.h"
#include "sanity_checks.h"

// *** Mathematical operations ***

// add the values stored in arr[]
long double sum(long double arr[], int numbers);

// subtract values in arr[]
long double sub(long double arr[], int numbers);

// multiplies the values stored in arr[]
long double multiply(long double arr[], int numbers);

// divides the values stored in arr[]
long double divide(long double arr[], int numbers);

// takes to input arr[0] = base, arr[1]= exponent
long double exponent(long double arr[], int numbers);

// takes two inputs arr[0] = number arr[1] = mod value
long double mod(long double arr[], int numbers);

// takes two inputs arr[0] = number arr[1] = log base
long double logarithm (long double arr[], int numbers);

// takes two inputs arr[0] = number arr[1] = root value
long double root(long double arr[], int numbers);

// takes two inputs arr[0] = number arr[1] = percent value
long double percent(long double arr[], int numbers);

// takes one inputs arr[0] = number 
long double factorial(long double arr[], int numbers);

#endif