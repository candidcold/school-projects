#include "team.h"

// Checks if the file name passed is a valid file (does it exist / is in directory).
bool validFile(const string& filename){
	ifstream inputfile((filename).c_str());

	if(inputfile.good()){
		return true;
	} else {
		return false;
	}
}

// Accepts the name of the file the user wants to implement.
// It must be the name of the teams and IDs, listed in the manner shown on the project page.
// Takes all teams and their IDs and puts them into an array of teams.
void createTeams(string teamIdentifiers, Team teamsArray[]){
	ifstream inputStream;
	string fileTeamName, fileTeamID;
	int counter = 0;

	// Opens the file of the name given
	inputStream.open((teamIdentifiers).c_str());

	// Goes through the file and grabs the team name and their ID.
	// Sets that Team in the array's values to the ones found in the file
	do{
		inputStream >> fileTeamName >> fileTeamID;

		// Just in case, y'know :]
		if(counter >= 50){
			break;
		}

		teamsArray[counter].setTeamName(fileTeamName);
		teamsArray[counter].setTeamID(fileTeamID);

		counter++;
	}while(!inputStream.eof());

	inputStream.close();
}

// Evaluates the outcomes of every game in a particular week for each team
void evaluateWeekScores(ifstream& inputStream, Team teamsArray[]){
	int convertedScore1 = 0, convertedScore2 = 0;
	int indexTeam1, indexTeam2;
	char team1[256], team2[256];
	string score1, score2;

	// Standard tests to see if end of file
	do{
		inputStream >> team1;

		// If you're at the end of a file after trying to take a value, or if the first char of input
		// value is not in the alphabet (meaning it's probably a '-'), break
		if(inputStream.eof() || !isalpha(team1[0])){
			break;
		}

		inputStream >> score1;

		// Check if the 2nd value of the line is actually a score (a number), if not, go to
		// next line of input. If it's not a number, it's a 'BYE'
		if(isdigit(score1.c_str()[0])){
			inputStream >> team2 >> score2;
			convertedScore2 = atoi(score2.c_str());
			convertedScore1 = atoi(score1.c_str());

		} else {
			continue;
		}

		// Find the two teams playing in this particular game
		// then checks their scores and updates their records of W-L-T
		indexTeam1 = findTeamInArray(team1, teamsArray);
		indexTeam2 = findTeamInArray(team2, teamsArray);

		// As long as the team is in the array, update their record
		if(indexTeam1 != -1 && indexTeam2 != -1){
			if(  score1 > score2 ){
				teamsArray[indexTeam1].updateRecord(1);
				teamsArray[indexTeam2].updateRecord(-1);
			} else if( score2 > score1 ){
				teamsArray[indexTeam2].updateRecord(1);
				teamsArray[indexTeam1].updateRecord(-1);
			} else if( score1 == score2 ){
				teamsArray[indexTeam1].updateRecord(0);
				teamsArray[indexTeam2].updateRecord(0);
			}
		}

	}while(!inputStream.eof());
}

// Searches the array for the team name passed by the user and returns its position in the array
int findTeamInArray(string name, Team teamsArray[]){
	for(int x = 0; x < 50; x++){
		if( name == teamsArray[x].getTeamID()){
			return x;
		}
	}

	// If that team is not in the array, return -1
	return -1;
}

// Accepts an ofstream from the user that will sort and display the rankings of the teams weekly.
void displayWeeklyRankings(ofstream& fileToWriteTo, Team teamsArray[]){
	int count = 1, ranking = 1, actualTeams = 0;
	int largestPosition = 0, positionToSwitch = 0;
	Team largestWinPercentage, temp_switch, highestAlphabetically;


	// Calculate the current winning percentage for each Team
	for(int x = 0; x < 50; x++){
		teamsArray[x].calculateWinningPercentage();
	}

	// Sorts teams by their win percentage
	for(int x = 0; x < 49; x++){
		largestWinPercentage = teamsArray[x];
		largestPosition = x;

		for(int i = x+1; i < 50; i++){
			if(largestWinPercentage.getWinPercentage() < teamsArray[i].getWinPercentage()){
				largestWinPercentage = teamsArray[i];
				largestPosition = i;
			}
		}

		temp_switch = teamsArray[x];
		teamsArray[x] = largestWinPercentage;
		teamsArray[largestPosition] = temp_switch;
	}

	// Sorts teams by their names, after already being sorted by their win percentages
	for(int k = 0; k < 49; k++){
		highestAlphabetically = teamsArray[k];
		positionToSwitch = k;

		for(int j = k+1; j < 50; j++){
			if(highestAlphabetically.getWinPercentage() == teamsArray[j].getWinPercentage()){
				if(teamsArray[j].getTeamID() < highestAlphabetically.getTeamID()){
					highestAlphabetically = teamsArray[j];
					positionToSwitch = j;
				}
			}

		}

		temp_switch = teamsArray[k];
		teamsArray[k] = highestAlphabetically;
		teamsArray[positionToSwitch] = temp_switch;
	}

	// Displays the rankings of all 'real' teams to an output file
	for(int p = 0; p < 50; p++){

		// If the team doesn't even have a name, that implies it's empty space in the array
		if(teamsArray[p].getTeamName().empty()){
			break;
		}
		fileToWriteTo << ranking << ": " << teamsArray[p].getTeamName() << " (" << teamsArray[p].getWins() << "-" <<  teamsArray[p].getLosses() << "-" << teamsArray[p].getTies() << ")\n";
		count++;
		if(teamsArray[p+1].getWinPercentage() != teamsArray[p].getWinPercentage()){
			ranking = count;
		}

	}
}

// ****************** Class Functions ***********************
Team::Team(){
	wins = 0;
	losses = 0;
	ties = 0;
}

int Team::getWins(){ return wins; }

int Team::getLosses(){ return losses; }

int Team::getTies(){ return ties; }

void Team::setTeamName(string name){ teamName = name; }

void Team::setTeamID(string ID){ teamID = ID; }

string Team::getTeamName(){ return teamName; }

string Team::getTeamID(){ return teamID; }

double Team::getWinPercentage(){ return winningPercentage; }

void Team::calculateWinningPercentage(){

	winningPercentage = ((wins) + (0.5 * ties)) / (wins+ties+losses);

	// Makes sure that if a valid team has a BYE the first week (or is yet to have played a game), their % is 0
	if((wins+ties+losses) == 0.0 && !teamID.empty()){
		winningPercentage = 0.0;
	}
}

void Team::updateRecord(int outcome){
	if(outcome == 1){
		wins++;
	}else if(outcome == -1){
		losses++;
	}else if(outcome == 0){
		ties++;
	}
}