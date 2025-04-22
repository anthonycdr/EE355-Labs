Name: Anthony Chandra  
Email:ac68801@usc.edu

This program demonstrates inheritance and polymorphism in C++ with three tasks:

1. Q1: Public vs. Private Inheritance
   - Student class (public inheritance) allows access to displayPersonInfo().
   - StudentPrivate class (private inheritance) restricts access to displayPersonInfo() outside the class.

2. Q2: Abstract Class and Virtual Functions
   - The Person class is made abstract by including a pure virtual function displayInfo().
   - Derived classes Student and Teacher override displayInfo() to provide specific implementations.

3. **Q3: Polymorphism via Virtual Functions
   - The function introduce() is declared as virtual in Person and overridden in Student and Teacher.
   - Demonstrates dynamic dispatch when calling introduce() on Person* pointers.

 References
- [C++ Reference](https://en.cppreference.com/)

How to Compile

First make an input.txt file then execute the code using
g++ -std=c++11 -o lab4 Lab4.cpp
./lab4

