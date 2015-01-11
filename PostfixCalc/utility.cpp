/******************************************************************************
Title :       utility.cpp
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
******************************************************************************/
#include "utility.h"
#include "calculator.h"

// Checks if a given file is valid.
int fileStatus(ifstream& inputfile) {
    // If the file is false, that means it does not exist.
    if (inputfile) {

      // If the file isn't good, it's not able to be opened.
      if (inputfile.good()){
        return 0;
      } else {
        return 1;
      }

    } else {
      return 2;
    }
}

// Convenience to figure out if the token is not a digit.
int isNonDigit(char token) {
  if (token == '+' || token == '-' || token == '/' ||
      token == '*' || token == '^' || token == '(' || token == ')') {
    return 1;
  } else {
    return 0;
  }
}

// Checks if a token is an operator.
int isOperator(char token) {
    if (token == '+' || token == '-' || token == '/' ||
        token == '*' || token == '^') {
      return 1;
    } else {
      return 0;
    }
}

// Checks to see if there are multiple decimals in an operand
int decimals(string operand) {
    int decimalNum = 0;
    for (int i = 0; i < operand.length(); i++) {
        if (operand[i] == '.') {
            decimalNum++;
      }
    }

    // If the number of decimals is more than one, e.g. 1.23.45.6
    // the number isn't truly a double. 
    return decimalNum;
}