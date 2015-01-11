/******************************************************************************
Title: main.cpp
Author: David Morant
Created on: 2014-03-28
Description: Parses two input files, obtaining teams and a season's worth of games
 				to track and rank sports teams.
Build with: g++ main.cpp team.cpp -o dmorant_assignment2
Usage: ./dmorant_assignment2
Dependencies: Two input files in the same directory
			You MUST acknowledge my love of smiley faces :]
******************************************************************************/
#include "team.h"

int main(){
	string inputFile1, inputFile2, outputFile;
	ofstream outputStream;
	ifstream inputStream;
	int week = 1;
	Team teamsArray[50];

	// Obtain the input file names from the user
	cout << "Enter your 2 input files (List of teams first, including extensions):" << endl;
	cin >> inputFile1 >> inputFile2;


	// Makes sure the file exists before going on, if it does not the program will end
	// Also avoids having two different inputStreams when they can be checked by a single
	// function.
	if(validFile(inputFile1) && validFile(inputFile2)){
		createTeams(inputFile1, teamsArray);
		inputStream.open((inputFile2).c_str());

		// Ask the user for an output file, only if the first two files are valid.
		cout << "Enter the name of your output file" << endl;
		cin >> outputFile;

		outputStream.open((outputFile).c_str());

		// Loop through the entire file
		do{
			evaluateWeekScores(inputStream, teamsArray);
			outputStream << "Rankings after week #" << week << "\n";
			displayWeeklyRankings(outputStream, teamsArray);
			if(inputStream.eof()){
				break;
			}
	 		outputStream << "\n";
			week++;
		}while(!inputStream.eof());

	}else{
		cout << "You've provided invalid filenames, goodbye." << endl;
	}

	// Always shut the door on your way out. :]
	inputStream.close();
	outputStream.close();
	return 0;
}