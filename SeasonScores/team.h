#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
using namespace std;

// Must implement a class named Team!
class Team{
	private:
		int wins;
		int losses;
		int ties;
		double winningPercentage;
		string teamName;
		string teamID;

	public:
		Team();
		int getWins(); //  Returns the amount of wins this team has had
		int getLosses(); //  Returns the amount of losses this team has had
		int getTies(); // Returns the amount of ties this team has had
		double getWinPercentage(); // Returns the win percentage of that team
		void calculateWinningPercentage(); // Calculates the win percentage of the team
		void updateRecord(int outcome); // Updates the record of this team
		void setTeamName(string name); // Sets the Team's name
		void setTeamID(string ID); // Sets the Team's ID
		string getTeamName(); // Returns the team's name
		string getTeamID(); // Returns the team's ID
};

// Function Prototypes
bool validFile(const string& filename);
// This function will handle checking if a file exists, for clarity in the main file.
// returns true if the file exists, false if not

void createTeams(string teamIdentifiers, Team teamsArray[]);
// Accepts the file containing team names, and creates a Team for each in the file.

void evaluateWeekScores(ifstream& inputStream, Team teamsArray[]);
// This function will handle the evaluation of the weekly scores
// It is given the file containing the weekly scores.

void displayWeeklyRankings(ofstream& fileToWriteTo, Team teamsArray[]);
// Will display the rankings weekly

int findTeamInArray(string name, Team teamsArray[]);
// Accepts a string, and searches for that team within the array of Teams
// returns the place in the array where that team is located

#endif