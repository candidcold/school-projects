/*******************************************************************************
Title:         songs.cpp
Author:        David Morant
Created on:    October 22, 2014
Description:   Allow the user to create and manage playlists of songs featured 
			   in a song database.
Purpose:       Experience creating a menu based user interface, and using
			   linked lists and larger classes.
Usage:         ./jukebox songslist.txt OR
			   ./jukebox
Build with:    g++ -o jukebox jukebox.cpp songs.cpp
Modifications: October 24: Added generic functions for convenience,
			   i.e. findPlaylist, uniqueName, etc.
			   October 27: Refined insertSong to handle edge cases. Bug fixes.
			   October 28: Refined validLine algorithm to be able to include tabs
			   and spaces within a given field.
			   October 29: Added extra commenting for clarity. 
********************************************************************************/
#include "songs.h"

//////////////////////////// Song Class Definition //////////////////////////////

// Creates a song.
// Requires a songId, a name, and an artist.
// Other information is allowed.
Song::Song(string userSongId, string songName, string songArtist,
		   string songAlbum, string songGenre, int songSize,
		   int songTime, string songYear, string songComments) {

	id = atoi(userSongId.c_str());
	name = songName;
	artist = songArtist;
	album = songAlbum;
	genre = songGenre;
	size = songSize;
	timeInSeconds = songTime;
	year = songYear;
	comments = songComments;
}

// Getters for private members. Return the name on the tin
string Song::getName() { return name; }
string Song::getArtist() { return artist; }
string Song::getAlbum() { return album; }
string Song::getGenre() { return genre; }
string Song::getComments() { return comments; }
string Song::getYear() { return year; }
int Song::getSize() { return size; }
int Song::getSongId() { return id; }

// Converts the time in seconds to MM:SS form (string). 
string Song::getTime() const {
	string timeAsString = "",
		   minutesAsString = "",
		   secondsAsString = "";
	int seconds = 0,
		minutes = 0;

	// Splice the timeInSeconds into minutes and seconds. 
	minutes = timeInSeconds / 60;
	seconds = timeInSeconds % 60; 

	// Convert each to strings.
	minutesAsString = to_string(minutes);
	secondsAsString = to_string(seconds);

	// Formatting, always has 2 fields.
	if (minutes < 10)
		minutesAsString = "0" + to_string(minutes);
	if (seconds < 10)
		secondsAsString = "0" + to_string(seconds);

	timeAsString = minutesAsString + ":" + secondsAsString;
	return timeAsString;
}

// Formats the field to be used for display. Used for compartmentalization.
string Song::formatString(bool leftJustified, string text, int size) const {
	string builtString = text;
	string spaces = "";

	// If the length of the text they want is larger than the allotted space
	// truncate the text up to the size needed.
	if (text.length() > size) {
		builtString = text.substr(0, size);
		return builtString;
	}

	// Get the correct amount of spaces needed to reach size.
	for (int i = 0; i < size - text.length(); i++) {
		spaces = spaces + " ";
	}

	// Figure out where you need to place those spaces.
	if (leftJustified) {
		builtString = builtString + spaces;
	} else {
		builtString = spaces + builtString;

	}

	return builtString;
}

// Formats an entire line to be used for display.
string Song::formatLine() const {
	string builtString = "";

	// Build a string that represents an entire formatted line.
	builtString = this->formatString(false, to_string(id), 5) + " "
				+ this->formatString(true, artist, 20) 		  + " "
				+ this->formatString(true, name, 30)		  + " "
				+ this->formatString(true, album, 10)		  + " "
				+ this->formatString(true, this->getTime(), 5)+ " "
				+ this->formatString(true, year, 4);

	return builtString;
}

/////////////////////////////////////// Playlist Class Definition ///////////////////////////////

// Initializes an empty playlist.
Playlist::Playlist() { /* Intentionally left blank */ }
Playlist::Playlist(string playlistName) { name = playlistName; }

// Getters and setters for private members.
int Playlist::getPlaylistSize() { return songList.size(); }
string Playlist::getPlayListName() { return name; }

void Playlist::setPlayListName(string playlistName) { name = playlistName; }


// Returns an output string of songs in the playlist
string Playlist::listSongs() {
	string stringBuilder = "";

	// Iterate through the songList and format each song for output.
	for (list<Song>::iterator it = songList.begin(); it != songList.end(); ++it) {
		stringBuilder = stringBuilder + it->formatLine() + "\n";
	}

	return stringBuilder;
}

// Returns an output string of songs in the playlist in a given range
string Playlist::listSongs(int first, int last){
	string stringBuilder = "";
	int counter = 1;

	// If the count of songs is within the range given by the user, build.
	for (list<Song>::iterator it = songList.begin(); it != songList.end(); it++) {
		if (counter >= first && counter <= last) {
			stringBuilder = stringBuilder + it->formatLine() + "\n";
		}
		if (counter > last) {
			// No use in checking after our range is up.
			break;
		}
		counter++;
	}

	return stringBuilder;
}

// Finds all songs by artist.
// Iterate through the list, if the single element's field is equal to the query
// format the line, and add it to a string builder and add a new line.
string Playlist::listSongsByArtist(string artist){
	list<Song> songsByArtist = fieldSearch(3, artist);
	string outputBuilder = "";

	// Iterate through the song list and format each song for output.
	for (list<Song>::iterator it = songsByArtist.begin(); it != songsByArtist.end(); ++it) {
		outputBuilder = outputBuilder + it->formatLine() + "\n";
	}

	return outputBuilder;
}

// Finds all songs with a matching title.
// Iterate through the list, if the single element's field is equal to the query
// format the line, and add it to a string builder and add a new line.
string Playlist::listSongsWithTitle(string title){
	list<Song> songsWithTitle = fieldSearch(2, title);
	string outputBuilder = "";

	// Iterate through the song list and format each song for output.
	for (list<Song>::iterator it = songsWithTitle.begin(); it != songsWithTitle.end(); ++it) {
		outputBuilder = outputBuilder + it->formatLine() + "\n";
	}
	return outputBuilder;
}

// Searches a field for all that match with a given query.	
// Returns a list of songs that meet that criteria.
list<Song> Playlist::fieldSearch(int field, string query) {
	list<Song> mylist;

	// Case 1 is searching for songId
	// Case 2 is searching for title
	// Case 3 is searching for artist
	switch (field) {
		case 1:
			for (list<Song>::iterator it = songList.begin(); it != songList.end(); ++it) {
				if (it->getSongId() == atoi(query.c_str())) {
					mylist.push_back(*it);
				}
			}
			break;
		case 2:
			for (list<Song>::iterator it = songList.begin(); it != songList.end(); ++it) {
				if (it->getName().find(query) != -1) {
					mylist.push_back(*it);
				}
			}
			break;
		case 3:
			for (list<Song>::iterator it = songList.begin(); it != songList.end(); ++it) {
				if (it->getArtist().find(query) != -1) {
					mylist.push_back(*it);
				}
			}
			break;
	}

	return mylist;
}

// Delete a song with the given id.
void Playlist::deleteSong(int id) {
	// Iterate through the list and if you find a song with a matching ID, erase it.
	for (list<Song>::iterator it = songList.begin(); it != songList.end(); ++it) {
		if (it->getSongId() == id) {
			songList.erase(it);
		}
	}
}

// Inserts song with songId id into position pos if possible.
void Playlist::insertSong(int id, int position, list<Song> songDatabase) {
	int counter = 1;

	// Search the song database to see if the song even exists.
	for (list<Song>::iterator it = songDatabase.begin(); it != songDatabase.end(); ++it) {
		if (it->getSongId() == id) {

			// Sadly you can only pass constant values when using insert.
			const Song songFromDatabase = *it;

			// The first item in the list must just be pushed there
			// Also, if the position they want is just outside of the size of the list
			// put it at the end.
			if (position == songList.size() + 1) {
				songList.push_back(songFromDatabase);
				break;
			}

			// Otherwise, insert the song at the position asked for.
			for (list<Song>::iterator sit = songList.begin(); sit != songList.end(); ++sit) {

				// If we're at the position we want to insert the song, insert it.
				if (counter == position) {
					songList.insert(sit, songFromDatabase);
					break;
				}
				counter++;
			}
			break;
		}	
	}	
}

// Returns a string that represents a playlist.
string Playlist::printPlaylist() {
	string outputString = "",
		   playlistPrefix = this->getPlayListName() + "\t" + to_string(songList.size()) + ": ";
	int count = 1;

	// Iterate through the song list
	for (list<Song>::iterator it = songList.begin(); it != songList.end(); ++it) {

		// If you're at the end of the playlist, do not add a comma, else, add a comma.
		if (count == this->getPlaylistSize()) {
			outputString = outputString + to_string(it->getSongId());
		} else {
			outputString = outputString + to_string(it->getSongId())  + ", ";
		}
		count++;
	}

	outputString = playlistPrefix + outputString;
	return outputString;
}


////////////////////////////////// Generic Function Definitions ///////////////////////////////////

// Checks if a given file is valid.
bool validFile(ifstream& inputfile) {
  // If the file is false, that means it does not exist.
  if (inputfile) {

    // If the file isn't good, it's not able to be opened.
    if (inputfile.good()){
      return true;
    } else {
      return false;
    }

  } else {
    return false;
  }
}

// Echoes back the command the user input to let them know something has happened.
string commandExecuted(string command) {
	string output = "Command " + command + " has been executed";
	return output;
}

// Checks if the heading of the file of songs is in the correct format.
bool isProperHeading(string heading) {
	string properHeading = "\"Name\"	\"Artist\"	\"Album\"	\"Genre\"	\"Size\"	\"Time\"	\"Year\"	\"Comments\"";
	return heading == properHeading;
}

// Checks if the name given to create a playlist is unique.
bool uniqueName(string playlistName, vector<Playlist>& playlistList){
	for (int i = 0; i < playlistList.size(); i++) {

		// If a playlist's name is the same as playlistName, return false.
		if (playlistName == playlistList[i].getPlayListName()) {
			return false;
		} 
	}

	// If we get through without returning false, the name is unique.
	return true;
}

// Accepts an entire line and creates a song from it.
Song createSong(string fileLine, int songId) {
	int foundQuote = 0,  // Position of the first outer quote.
	    foundQuote2 = 0, // Position of the second outer quote.
	    fieldLength = 0; // Length of the field.
	string songField[8]; // An array holding all necessary song arguments.

	// Every time you find a quote take the substring between quotes.
	// You then set the start point to where the last quote was found.
	for (int i = 0; i < 8; i++) {

		foundQuote = fileLine.find("\"", foundQuote);
		foundQuote2 = fileLine.find("\"\t\"", foundQuote+1);

		fieldLength = foundQuote2 - foundQuote; 

		// Just in case there are quotation marks within fields. 
		// If you're on the last element of the song, find the last "
		if (i == 7) {
			foundQuote2 = fileLine.find_last_of("\"", foundQuote+1);
			fieldLength = fileLine.substr(foundQuote+1).size();
		}

		// Get the substring from between the quotes
		songField[i] = fileLine.substr(foundQuote+1, fieldLength-1);

		// Move the chains. You need to make the new starting point equal to the last + 1
		// to start searching at the point after it.
		foundQuote = foundQuote2+1;
	}

	// Create a song. 
	Song singleSong(to_string(songId), songField[0], songField[1], songField[2], songField[3],
	 				atoi(songField[4].c_str()), atoi(songField[5].c_str()), songField[6], songField[7]);

	return singleSong;
}

// Check if a single line is valid:
// 		It has an artist and name
//		7 tabs separating items
//		8 total items
bool validLine(string fileLine) {
	bool argumentFilled = false; // Used to denote whether or not a field is filled.
	int tabPoint = 0,			 // The position of a tab.
		foundPoint1 = -1,		 // The position of the first outer quote.
		foundPoint2 = 0,		 // The position of the second outer quote.
		counter = 1,			 // A counter to keep track of how many fields supplied
		quoteCount = 0,			 // The number of outer quotes.
		tabCount = 0;			 // The number of separating tabs.

	do {
		// Find the positions of the quotes
		foundPoint1 = fileLine.find("\"", foundPoint1+1);

		// Fields are quote enclosed AND tab separated, therefore
		// quotes and tabs can be within a field (for whatever reason).
		// However, if they were to have a tab separating them,
		// it would be counted as a new field.
		//
		// Aside:
		// However, if there are tabs inside the fields, they will be
		// misaligned when formatted. However, the amount of characters
		// on the line are the same. So, if one tab is included, it'd
		// be best if tabs were included in all use cases.
		if (foundPoint1 >= 0 && counter < 8) { 
			quoteCount++;
			foundPoint2 = fileLine.find("\"\t\"", foundPoint1+1);
		} else if (foundPoint1 >= 0 && counter == 8) {
			foundPoint2 = fileLine.find("\"", foundPoint1+1);
			quoteCount++;
		} else {
			break;
		}


		// If there is no quote found, return false.
		// If you have more than 8 fields then the line isn't formatted right.
		if (foundPoint2 < 0) {
			break;
		} else {
			quoteCount++;
		}

		// If it is one of the first two fields, find out if the string within the
		// quotes is actually filled.
		if (counter == 1 || counter == 2) {
			argumentFilled = fileLine.substr(foundPoint1, foundPoint2 - foundPoint1).length() > 0;

			// If the argument isn't filled, return false, because the first two fields aren't filled
			if (!argumentFilled) {
				return false;
			}
		}

		// Add to the amount of tabs if there is a tab found after the quote.
		tabPoint = fileLine.find("\t", foundPoint2);
		if (tabPoint >= 0) {
			tabCount++;
		}

		foundPoint1 = foundPoint2;
		counter++;

	// Count to 10 just to make sure you check if there is anything extra on the line
	} while (counter < 10); 


	// If the tabs and quotes equal up, then it is a valid line.
	// Quotes mean outer quotes, the ones that denote a field.
	// Tabs mean separating tabs, those separating fields.
	if (tabCount == 7 && quoteCount == 16)
		return true;
	else
		return false;
}

// Stores all songs made by the file.
bool storeSongs(list<Song>& songDatabase, ifstream& inputFile){
	string singleLine;	 // A single line from the inputFile.
	int currentLine = 1, // The number line currently being used.
		count = 1;		 // The number song we're up to.

	while(!inputFile.eof()) {

		getline(inputFile, singleLine);

		// If we're at the end of the life after trying to obtain that last line, we're done.
		if (inputFile.eof()) {
			return true;
		}

		if (currentLine == 1) {

			// If it's a proper heading, move on to the next line.
			if (isProperHeading(singleLine)) {
				currentLine++;
				continue;
			} else {
				// The heading isn't proper, therefore we break out.
				return false;
			}
		}

		if (validLine(singleLine)) {
			Song singleSong = createSong(singleLine, count);

			// Add that song back to the songDatabase
			songDatabase.push_back(singleSong);
			count++;
			currentLine++;
		} else {
			// A line isn't valid, therefore we break out. 
			return false;
		}
		
	}

	// If you can get through the entire file without having a hiccup, return true
	return true;
}

// Turns commands into int values to be easily checked for ease of access.
int commandAsInt(string command) {
	if (command == "L" || command == "l") { return 1; }
	if (command == "V" || command == "v") { return 2; }
	if (command == "C" || command == "c") { return 3; }
	if (command == "M" || command == "m") { return 4; }
	if (command == "D" || command == "d") { return 5; }
	if (command == "S" || command == "s") { return 6; }
	if (command == "H" || command == "h") { return 7; }
	if (command == "Q" || command == "q") { return 8; }
	if (command == "A" || command == "a") { return 9; }
	if (command == "T" || command == "t") { return 10; }
	if (command == "B" || command == "b") { return 11; }
	if (command == "Insert") { return 12; }
	if (command == "Delete") { return 13; }
	if (command == "Show") { return 14; }

	return -1;		
}

// Parses the command line arguments for ease of access.
void parseCLA(string& command, string& arg1, string& arg2, string entireLine) {
	int positionOfSpace,				// The position of a space on the CL.
		startPoint = 0,					// The start point of an argument.
		numberOfArgs = 0;				// The number of arguments on the CL.
	string arguments[] = {"", "", ""};  // An array of arguments.

	// There are at most 3 arguments possible to be given.
	for (int i = 0; i < 3; i++) {
		positionOfSpace = entireLine.find(" ", startPoint);

		// If you cannot find a space in the string, you're at the end
		// and there are no more arguments on the line.
		if (positionOfSpace <= 0) {
			arguments[i] = entireLine.substr(startPoint);
			break;
		} else if (positionOfSpace > 0) {
			arguments[i] = entireLine.substr(startPoint, positionOfSpace - startPoint);
			startPoint = positionOfSpace+1;
		}
	}

	command = arguments[0];
	arg1 = arguments[1];
	arg2 = arguments[2];
}

// Finds a single playlist in the list of playlists with the supplied name.
// Virtually the same thing as unique name, but written for clarity.
int findPlaylist(string playlistName, vector<Playlist>& playlistList) {
	// If the playlist is found, return the position it was found at
	for (int i = 0; i < playlistList.size(); i++) {
		if (playlistList[i].getPlayListName() == playlistName) {
			return i;
		}
	}
	// If the playlist wasn't found, return -1
	return -1;
}

// Deletes a playlist in the list of playlists with a given name if it exists.
bool deletePlayList(string playlistName, vector<Playlist>& playlistList) {
	int playlistToBeDeletedPosition = findPlaylist(playlistName, playlistList);

	if (playlistToBeDeletedPosition == -1) {
		// There is no playlist that was actually found. Denoted by a playlist with name
		// "empty".
		return false;
	} else {
		// Remove the playlist from the list of playlists, and return true.
		playlistList.erase(playlistList.begin()+playlistToBeDeletedPosition);
		return true;
	}
}

// Saves all user playlists to a given file.
void savePlaylists(ofstream& outputFile, vector<Playlist>& playlistList) {
	for (int i = 0; i < playlistList.size(); i++) {
		outputFile << playlistList[i].printPlaylist() << "\n";
	}
}

// Provide a help screen informing the user of how commands work.
string help() {
	string output = "",
		   list,
		   view,
		   create,
		   modify,
		   deleteText,
		   save,
		   exitText;

	list = "List              \t The name of each playlist together with the number\n                 \t of songs in that playlist is displayed on the terminal.";
	view = "View <playlist>   \t The songs in the playlist whose name is supplied\n                 \t to the View command is then displayed.\n                 \t The first output line is the name of the playlist,\n                 \t and the subsequent lines are the song descriptions";;
	create = "Create  <playlist> \t Create a new playlist.\n                 \t If the given name matches the name of an existing playlist,\n                 \t the command returns saying the name is in use.";
	modify = "Modify  <playlist> \t Opens playlist modification mode.\n                 \t Songs can then be inserted into and deleted from the playlist.\n                 \t If the playlist provided doesn't exist, the main menu is displayed.";
	deleteText = "Delete <playlist> \t Delete a playlist.\n                 \t If the name given does not match an existing playlist,\n                 \t the main menu is displayed.";
	save = "Save <filename>   \t All playlists are saved to a file whose name is given.";
	exitText = "Exit              \t The program exits.";

	output = list + "\n" + view + "\n" + create + "\n" + modify
				  + "\n" + deleteText + "\n" + save + "\n" + exitText + "\n";

	return output;
}