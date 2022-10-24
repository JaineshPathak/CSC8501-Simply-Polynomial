Project: 		Simply Polynomial (CSC8501 Coursework)
Student: 		Jainesh Pathak
Student Email: 		J.P.Pathak2@newcastle.ac.uk
Student ID:		220639466

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

OutputSet.txt file contains the following A-F sets:
0, 3, 24, 81, 192, 375, 648, 1029, 1536, 2187, 3000, 3993, 5184, 6591, 8232, 10125, 12288, 14739, 17496, 20577, 24000
-9, -4, 71, 396, 1271, 3116, 6471, 11996, 20471, 32796, 49991, 73196, 103671, 142796,, 192071, 253116, 327671, 417596, 524871, 651596, 799991
0, 14, 96, 300, 680, 1290, 2184, 3416, 5040, 7110, 9680, 12804, 16536, 20930, 26040, 31920, 38624, 46206, 54720, 64220, 74760
7, 13, 17, 13, -5, -43, -107, -203, -337, -515, -743, -1027, -1373, -1787, -2275, -2843, -3497, -4243, -5087, -6035, -7093
114, 110, 100, 78, 38, -26, -120, -250, -422, -642, -916, -1250, -1650, -2122, -2672, -3306, -4030, -4850, -5772, -6802, -7946
715, 625, 523, 409, 283, 145, -5, -167, -341, -527, -725, -935, -1157

Expression.txt file contains the following expression:
3x^3
5x^4-9
9x^3+7x^2-2x
-x^3+2x^2+5x+7
-x^3-3x+114
-6x^2-84x+715

//----------------------------------------------------------------------------------------------------------------------------

Important Notes:
- Zip file contains the visual studio solution file along with all the programs and the OutputSet.txt and Expression.txt
- The program expects only integer numbers in the expressions and output sets. Floating points support is not added

Thank you.