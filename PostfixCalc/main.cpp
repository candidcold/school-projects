/******************************************************************************
Title :       main.cpp
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
               November 19, 2014
               Added a vector to group input expressions found
               November 20, 2014
               Fixed command line input parsing. 
               Commenting
******************************************************************************/
#include "utility.h"
#include "calculator.h"

int main(int argc, char *argv[]) {
    ifstream inputFile;             // Stream of the file provided.
    int temp;                       // Temporary int to record the status of the file.
    string userInput;               // One instance of userInput from the command line.
    string expressionLine;          // One instance of a line from the file.
    Calculator calculator;          // A calculator.
    vector<string> expressions;     // A vector of expressions regardless of where the input comes from.

    // The "Magic Formula", used to set the number of positions after the decimal to 3.
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(3);

	// Discern the file if one is provided on the command line, and find out its status.
    if (argv[1]) {
        inputFile.open(argv[1]);
        temp = fileStatus(inputFile);

        switch(temp){
            // 0: The file is accessible.
            case 0:
                while (getline(inputFile, expressionLine)) {
                    expressions.push_back(expressionLine);
                }

                inputFile.close();
                break;

            // 1: The file may have been found, but we cannot access it.
            case 1:
                cout << "The file you provided cannot be opened." << endl;
                inputFile.close();
                exit(0);
                break;

            // 2: The file is not "true", meaning it doesn't exist.
            case 2:
                cout << "The file you provided could not be found." << endl;
                inputFile.close();
                exit(0);
                break;
        }
    } else {
        cout << "Enter expressions (1 per line). When done, press Ctrl-D" << endl;
        while (!cin.eof() &&  getline(cin, userInput)) {
            expressions.push_back(userInput);
        }
    }

    // Regardless of how we obtained the inputs, try each output to see if it works.
    for (int i = 0; i < expressions.size(); i++) {
        try {
            calculator.setExpression(expressions[i]);
            calculator.calculate();
            cout << calculator.getResult() << " = " << expressions[i] << endl;

            // The file was not formatted correctly
            } catch (int x) {
                cerr << expressions[i] << endl;
                continue;
            }
    }

	return 0;
}