# Simply Polynomial
The task was to write a computer program in C++ that creates a sequence of numbers from an algebraic expression. In addition, the program may also derive an algebraic expression used to create a sequence of numbers. Program will focus
on algebraic expressions of one, two, three, and four terms (Monomial, Binomial, Trinomial, Quadrinomial), commonly termed polynomials. 
Each algebraic expression is limited to the existence of a single variable (which can appear in multiple terms), a highest degree of 4, a highest coefficient of 9, highest constant is 1000, and restricted to the operators of + or - only between terms.

Description:
The project provides an interface with commands for performing different types:

1. Enter Expression and get Output Set
2. Read file and view Output Sets
3. Read Output Set and derive Expression
4. Read All Output Sets and derive Expression (Batch Style)
5. Exit

//----------------------------------------------------------------------------------------------------------------------------

1. Enter Expression and get Output Set:
This option will ask for an algebraic expression from the user in the format example: 5x^3 + 2x^2 - x + 3
After inputting the expression, it ask for the start and end range for generating sequence of numbers based on expression
Once done, it will show the output set and ask for saving the currently generated set to the OutputSet.txt file.
After telling yes or no, the program will return to the main menu screen.

However, while inputting the expression there are few constraints like:
Max Degree/Exponent: 4
Max Coefficient: 9
Max Constant: 1000

2. Read file and view Output Sets:
This will simply read the OutputSet.txt file and print all the output sets on the screen for the user.

3. Read Output Set and derive Expression:
This will print the output sets from the OutputSet.txt file with indexes and ask the user for the index.
After getting the index from the user, it will take the output set at index and start the process for deriving the expression.

4. Read All Output Sets and derive Expression (Batch Style):
Same like above with only difference that it will read all the output sets from file OutputSet.txt and save all the expressions in a separate Expression.txt file.

//----------------------------------------------------------------------------------------------------------------------------

OutputSet.txt file contains few sets:
0, 3, 24, 81, 192, 375, 648, 1029, 1536, 2187, 3000, 3993, 5184, 6591, 8232, 10125, 12288, 14739, 17496, 20577, 24000

-9, -4, 71, 396, 1271, 3116, 6471, 11996, 20471, 32796, 49991, 73196, 103671, 142796,, 192071, 253116, 327671, 417596, 524871, 651596, 799991,

Expression.txt file contains the expression which are generated from output sets:
3x^3,
5x^4-9,
9x^3+7x^2-2x,
-x^3+2x^2+5x+7,
-x^3-3x+114,
-6x^2-84x+715,

//----------------------------------------------------------------------------------------------------------------------------

Important Notes:
- Zip file contains the visual studio solution file along with all the programs and the OutputSet.txt and Expression.txt
- The program expects only integer numbers in the expressions and output sets. Floating points support is not added

Thank you.
