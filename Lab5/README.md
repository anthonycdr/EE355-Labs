Name: Anthony Chandra


Program Summary
This code that I submitted describes the implementation of two programs (Q1 & Q2) that demonstrate pointer-based operations in C++. Both programs read input from a file (input.txt for Q1) or command-line arguments (Q2), apply transformations, and write the results to an output file.

Q1: Array Transformation and Computation
The program reads an array of integers from input.txt, modifies it and computes prefix sum, min, and max values, and writes the results to output_Q1.txt.

Transformations:
- Even numbers are doubled.
- Odd numbers are squared.
    + I used pointer arithmetics (ptr < arr + n) to traverse the array and checked whether number is odd or even using (%2) if (%2 == 0) then it's even otherwise it's odd and then modify based on that.

Computations:
- Computes prefix sum.
    + The first element of psum is the first element of arr and for everty other element the current prefix sum is the previous prefix sum + current element.
- Finds the minimum and maximum values in the transformed array.
    + I iterated over the arrays using a pointer then update min if a smaller value is found and max if a larger value is found.
- Writes results to output_Q1.txt.

Q2: Function Argument Passing Mechanisms
The program demonstrates different ways of passing arguments in C++ using command-line input. The results are written to output_Q2.txt.

- Pass-by-Value: Attempts to swap two numbers (no effect).
    + I just tried to swap a and b locally but it doesn't affect original variables as the vars are copied.
- Pass-by-Reference: Successfully swaps two numbers.
    + Same thing with the pass by value but instead of copying the var I used the address instead e.g. &a and &b
- Pass-by-Pointer: Doubles each value in an array.
    + I made a for loop through the array using pointer arithmetic which multiplies each element by 2
- Pointer-to-Pointer (char** argv) extracts and prints command-line arguments.
- Compute sum and product of all input numbers.
    + Made a for loop that traverses the array using a pointer and adds each element to sum and multiplies it to product.
- Reverses the array using pointer arithmetic.
    + Made a while loop that uses two pointers and swapped the values using the var temp (t) to move inward until they meet in the middle.
- Writes results to output_Q2.txt.

References Used:
I didn't use any external references other than the standard C++ libraries such as iostream, fstream, cstdlib.

Instructions to Compile and Run the Code

Compile both programs using:
g++ -o lab5p1 lab5_p1.cpp
g++ -o lab5p2 lab5_p2.cpp

Execution Commands:
Q1 Execution (Reads from input.txt):
./lab5p1
The program reads from input.txt, processes the array, and writes results to output_Q1.txt.

Q2 Execution (Command-line arguments):
./lab5p2 3 8 5 10 7 2
The program processes the numbers the user writes in the command line and produces results to output_Q2.txt.
