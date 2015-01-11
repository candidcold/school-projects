/******************************************************************************
Title :       calculator.h
Author :      David Morant
Created on :  November 15, 2014
Description : Evaluate infix expressions from either a file or the
              command line.
Purpose :     Practice using stacks and exception handling in order to make
              programs more robust and able to handle edge cases in a more
              efficient/standardized way.
Usage :       ./calc 2>errorfile
                    OR
              ./calc sometextfile.txt 2>errorfile
Build with :   g++ -o calc main.cpp calculator.cpp utility.cpp
Modifications: November 16, 2014
               Transcribed algorithm from textbook.
               November 19, 2014
               Created local stacks when needed instead of initialized in
               constructor.
               November 20, 2014
               Added functions better suited here than utility
               Commenting
******************************************************************************/
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "utility.h"

class Calculator {
private:
    double result,
           operand1,
           operand2;

    string expression;

public:
    // Default constructor.
    Calculator();

    // Returns an integer that corresponds to the precedence level of an operator.
    //
    // Precondition:  token is an operator. 
    // Postcondition: The precedence of the operator is found.
    //
    // @char token: the operator that needs its precedence found.
    int precedence(char token);

    // Calculates the partial infix expression.
    //
    // Precondition:  An expression has already been set.
    // Postcondition: The calculation of the two operands is done. 
    void calculate() throw(int);


    // Returns the result of the calculations.
    double getResult();

    // Evaluates partial expressions of the stacks.
    //
    // Precondition:  valStack and opStack are not empty. 
    // Postcondition: An expression is evaluated. 
    //
    // @stack<double>& valStack: Stack containing the values of operands in an expression.
    // @stack<char>& opStack:    Stack containing the operators in an expression.
    void execute(stack<double>& valStack, stack<char>& opStack) throw(int);

    // Formats an expression by removing whitespace.
    //
    // Precondition:  The expression given by the user.
    // Postcondition: Whitespace has been removed from expression.
    //
    // @string& expression: The expression given by the user.
    void formatExpression(string& expression); // throw(int)

    // Sets the expression given by the user
    //
    // Precondition:  The user supplies an expression.
    // Postcondition: The expression has been set
    //
    // @string expression: The expression the user wants to set.
    void setExpression(string expression);
};

#endif