/******************************************************************************
Title :       utility.h
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
Build with :  g++ -o calc main.cpp calculator.cpp utility.cpp
Modifications: November 20, 2014
               Separated isOperator from isNonDigit for convenience in
               calculator implementation.
               Removed functions better suited for calculator object. 
******************************************************************************/
#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cmath>
#include <stdlib.h>
#include <vector>
using namespace std;

// Checks if a given file is valid.
//
// Precondition:  An input file has already been opened. 
// Postcondition: The file's validity has been determined.
//
// @string filename: the name of a file to be checked.
int fileStatus(ifstream& inputfile);

// Convenience to figure out if the token is an operator.
//
// Precondition:  None.
// Postcondition: None.
//
// @char token: The token to be checked.
int isNonDigit(char token);

// Checks if a token is an operator.
//
// Precondition:  None. 
// Postcondition: None.
//
// @char token: The token to be checked.
int isOperator(char token);

// Checks how many decimals are in an operator.
//
// Precondition:  An operand has been supplied and created. 
// Postcondition: None.
//
// @string operand: The operand to be checked for decimals.
int decimals(string operand);


#endif