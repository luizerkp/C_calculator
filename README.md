#  C Calculator
#### Video Demo:  <https://youtu.be/rPMxPo5jqxc>
#### Description:
This is a command line calculator implemented entirely in C, it can perform  addition, subtraction, division, multiplication, modulo, logarithm,
exponent, root, percent, & factorial. For addition, subtraction, division and multiplication it can take up to ten inputs, for the others it is either twor one. It takes as input the program plus one of the operations listed and returns the as output the calculated results in either scientific notation for
results that are either too big or too small  or just a number with 7 decimal places. I debated on just outputting the answer in raw format with 7 decimal
places but the factorial of 999 for example just outputted a wall of numbers that had very little meaning to the user. I originally wanted to use **%g**
format specifier but decided to use my own logic to decide whether to output in scientific notation **%e** or just a long double with 7 decimal
places **%.7Lf**. Any number that falls out the range *0.000001 - 9999999999.999999* will be displayed in scientific notation.

The input is taken in as a string, then verified for validity through various checks and stored in an array of strings. This array in later
converted into an array of long doubles. The decision to use long doubles was made to allow a wider set of inputs. I originally had many global
variables but midway I realized this not a good design, therefore I reworked my code to accept those values as function parameters instead. I also
decided to use a MAKEFILE to compile multiple source files into one program, however after learning about MAKEFILES and making my own simple one in
VS studio, I dropped this a idea because it was time consuming to get it working correctly due to my lack of familiarity compiling multiple source
files as well as building MAKE files. For the scope of this program I did not think that it would have any added advantage by using multiple source
files.

This project has been a learning opportunity and while it is not as impressive as some of the other final projects I had in mind, it did
challenge my knowledge of the basics. For example the limits of the different data types, as well as the limits of the different library
functions. For Example I originally intended to use **fscanf()** but I ran into problems with validation so that I would force the user to
input a number in the correct format, as result I ended using **fgets()**.
