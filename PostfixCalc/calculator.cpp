/******************************************************************************
Title :       calculator.cpp
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
Modifications: November 16, 2014
               Transcribed algorithm from textbook.
               November 17 - 18, 2014
               Improved error handling.
               November 20, 2014
               Fixed balanced bracket algorithm.
               Commenting
******************************************************************************/
#include "utility.h"
#include "calculator.h"

// Default Constructor, intentionally empty.
Calculator::Calculator() {}

// Returns an integer that corresponds to
// the precedence level of an operator.
int Calculator::precedence(char token) {
	if (token == '-' || token == '+') {
		return 1;
	}

	if (token == '*' || token == '/') {
		return 2;
	}

    if (token == '^') {
        return 3;
    }

    if (token == ')') {
        return -1;
    }

	return 0;
}

// Sets the expression given by the user.
void Calculator::setExpression(string theirExpression) {
    expression = theirExpression;
}

// Takes out unnecessary spaces from the input for convenience.
void Calculator::formatExpression(string& expr) {
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == ' ') {
            expr.erase(i, 1);
            i--;
        }
    }
}

// Calculates an entire infix expression.
void Calculator::calculate() throw(int){
    char ch;                    // Character to be checked in an expression.
    int i = 0,                  // Simple counter.
        brackets = 0;           // Keeps track of the number of brackets.
    string unit = "";           // Holds a string to recognize what TYPE the previous item was.
    string singleOperand = "";  // A single operand in an expression.
    stack<double> valStack;     // Stack holding values to be used for expressions.
    stack<char> opStack;        // Stack holding operators to be used for expressions.


    // Used for convenience; takes out spaces from the expression.
    formatExpression(expression);

    // If the expression starts or ends with an operator, it's malformatted.
    if (isOperator(expression.back()) || isOperator(expression.front())) {
        throw(0);
    }

    while (i < expression.length()){
        ch = expression[i];

        // We're not doing algebra, so there won't be any letters.
        if (isalpha(ch)) {
            throw(0);
        }

        switch (ch) {
            case '(':
                opStack.push(ch);
                brackets++;
                break;

            // Finish all executions within a set of parenthesis
            case ')':
                brackets = brackets - 1;
                if (brackets < 0) {
                    // End bracket before opening bracket.
                    throw(0);
                }

                // Evaluate all expressions within a set of parenthesis.
                while (opStack.top() != '(') {
                    execute(valStack, opStack);
                }

                opStack.pop();
                break;

            // In the case of any operator:
            case '+': case '-': case '/': case '*': case '^':
                if (unit == "operator") {
                // The unit before this was also an operator.
                    throw(0);
                } else {
                    unit = "operator";
                }

                if (opStack.empty())
                    opStack.push(ch);
                else if (precedence(ch) > precedence(opStack.top()))
                    opStack.push(ch);
                else {
                    // When you have a lower precedence, the item with higher precedence
                    // needs to happen first, then add this operation to the stack.
                    while (!opStack.empty() && precedence(ch) <= precedence(opStack.top()))
                        execute(valStack, opStack);
                    opStack.push(ch);
                }
                break;

            // It's not a special type of character
            // Add all non operator characters to the value stack
            default:
                while (isNonDigit(expression[i]) == 0 && i < expression.length()) {
                    singleOperand = singleOperand + expression[i];
                    i++;
                }
                // If the string has multiple decimals, it's not a real double.
                if (decimals(singleOperand) > 1) {
                    throw(1);
                }

                // The value before this was an operand.
                if (unit == "operand") {
                    throw(0);
                } else {
                    unit = "operand";
                }

                // Have to get back to the position before the operator.
                valStack.push(atof(singleOperand.c_str()));
                singleOperand = "";
                i--;
                break;
        }
        i++;
    }

    // If there are remaining brackets that means the brackets are not balanced.
    if (brackets > 0) {
        throw(0);
    }

    // Do the final calculations of what's left in the stacks
    while (!opStack.empty() && !valStack.empty()) {
        execute(valStack, opStack);
    }

    result = valStack.top();
}

// Returns the value of result.
double Calculator::getResult() {
    return result;
}

// Algorithm given:
// Performs remaining operations on remaining operands.
void Calculator::execute(stack<double>& valStack, stack<char>& opStack) throw(int){
    // Take what's on top of the stacks and then pop them.
    char operatorToken;
    operand2 = valStack.top();
    valStack.pop();
    operand1 = valStack.top();
    valStack.pop();
    operatorToken = opStack.top();
    opStack.pop();

    // Compute the values of each partial expression.
    switch (operatorToken) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
        case '^':
            result = pow(operand1, operand2);
            break;
    }

    valStack.push(result);
}