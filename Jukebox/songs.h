/*******************************************************************************
Title:         songs.h
Author:        David Morant
Created on:    October 22, 2014
Description:   Allow the user to create and manage playlists of songs featured 
			   in a song database.
Purpose:       Experience creating a menu based user interface, and using
			   linked lists and larger classes.
Usage:         ./jukebox songslist.txt OR
			   ./jukebox 
Build with:    g++ -o jukebox jukebox.cpp songs.cpp
Modifications: October 24th: Created Song and Playlist classes. Added generic
			   functions like findPlaylist, uniqueName, etc.
			   October 26th: Changed playlistList to a vector as order of
			   playlists doesn't matter as long as they're all there.
			   However, songs matter in terms of order, so those were left
			   as lists.
********************************************************************************/
#ifndef SONGS_H
#define SONGS_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
using namespace std;

//////////////////////////////// Song Class Declaration //////////////////////////////

class Song {
private:
	// Private variables for every field of a Song
	string name, 
		   artist, 
		   album,
		   genre,
		   comments,
		   year;
	int timeInSeconds,
		size,
		id;

public:
	// Creates a song.
	// Requires a songId, a name, and an artist.
	// Other information is allowed.
	Song(string userSongId, string songName, string songArtist, 
		 string songAlbum = "", string songGenre =	"", int songSize = 0,
		 int songTime = 0, string songYear = "", string songComments = "");

	// Getters for private members. 
	string getName();
	string getArtist();
	string getAlbum();
	string getGenre();
	string getComments();
	string getYear();
	string getTime() const ;
	int getSize();
	int getSongId();

	// Formats the song to be used for display.
	//
	// Precondition: None.
	// Postcondition: String returned is an entire line correctly 
	// 				  formatted to be output. The song will not be altered.
	//
	// @bool leftJustified: Whether or not the text needs to be left justified.
	// @string text:        The text needed to be formatted.
	// @int size:           The size the formatted string must be.
	string formatString(bool leftJustified, string text, int size) const ;	

	// Formats an entire line for display.
	//
	// Precondition:  A song has been created.
	// Postcondition: The line has been formatted. The song will not be altered.
	string formatLine() const;
};


//////////////////////////// Playlist Class Declaration ////////////////////////////////////

class Playlist {
private:
	list<Song> songList; // A list of songs within the playlist.
	string name;         // The name of the playlist.

public:
	// Initializes an empty playlist.
	Playlist();
	Playlist(string playlistName);

	// Getters and setters for private members.
	int getPlaylistSize();
	string getPlayListName();
	void setPlayListName(string playlistName);

	// Returns a list of all songs in a range if one is supplied.
	// Otherwise returns a list of all songs.
	//
	// Precondition:  A playlist has been created.
	// Postcondition: The songs of the playlist have been correctly formatted.
	//
	// @int first: The position the user wishes to start from.
	// @int last:  The position the user wishes to end at.
	string listSongs();  
	string listSongs(int first, int last); 

	// Finds all songs by their respective qualities.
	//
	// Precondition:  A playlist has been created.
	// Postcondition: The songs of the playlist from artist have been correctly formatted.
	//
	// @string artist: The name of the artist the user wishes to find.
	string listSongsByArtist(string artist);

	// Finds all songs by their respective qualities.
	//
	// Precondition:  A playlist has been created.
	// Postcondition: The songs of the playlist with title have been correctly formatted.
	//
	// @string title:  The title the user wishes to find.
	string listSongsWithTitle(string title);

	// Searches a field for all that match with a given query.	
	// Returns a vector of pointers to all matching songs.
	list<Song> fieldSearch(int field, string query);

	// Deletes the song with the given songId.
	void deleteSong(int id);

	// Inserts song with songId id into position if possible.
	//
	// Precondition:  A songDatabase has already been created.
	// Postcondition: A song will be inserted into the playlist at its position.
	//
	// @int id:                  The id of the song that is to be added.
	// @int position:			 The position you want to enter the song into.
	// @list<Song> songDatabase: The songDatabase. 
	void insertSong(int id, int position, list<Song> songDatabase);

	// Returns a string that represents a playlist.
	string printPlaylist();
};

////////////////////////////////// Generic Function Declaration ///////////////////////////////

// Checks if a given file is valid.
//
// Precondition:  An input file has already been opened. 
// Postcondition: The file's validity has been determined.
//
// @string filename: the name of a file to be checked.
bool validFile(ifstream& inputfile);

// Echoes back the command the user input to let them know something has happened.
//
// Precondition: A command has been executed.
// Postcondition: None.
//
// @string command: The command from the command line that was input.
string commandExecuted(string command);

// Checks if the heading of the file of songs is in the correct format.
// 
// Precondition: A file has already been opened.
// Postcondition: The heading has been verified or rejected.
//
// @string heading: The first line of a file of songs.
bool isProperHeading(string heading);

// Checks if the name given to create a playlist is unique.
//
// Precondition: A list of playlists exists + user is creating new playlist.
// Postcondition: None.
//
// @string playlistName: The name of a playlist the user wants to create.
// @vector<Playlist> playlistList: A list of all playlists that exist.
bool uniqueName(string playlistName, vector<Playlist>& playlistList);

// Accepts an entire line and creates a song from it.
//
// Precondition: A file/line of songs has already been recognized as valid.
// Postcondition: A song is created from that line of the file.
//
// @string fileLine: An entire line from the file of songs
Song createSong(string fileLine, int songid);

// Stores all songs made by the file.
// 
// Precondition: A song database and an input file have been provided.
// Postcondition: All songs available in the file are made and stored.
//
// @list<Song>& songDatabase: A list containing all songs in the database.
// @ifstream& inputFile: The file that contains a list of songs.
bool storeSongs(list<Song>& songDatabase, ifstream& inputFile);

// Deletes a Playlist with the given name from the list of Playlists
// 
// Precondition: A list of playlists exist.
// Postcondition: Playlist with name PlaylistName is deleted if it ever existed.
//
// @string playlistName: The name of a playlist the user wants to create.
// @vector<Playlist> playlistList: A list of all playlists that exist.
bool deletePlayList(string playlistName, vector<Playlist>& playlistList);

// Saves all playlists and outputs them to a file named filename.
//
// Precondition: The user has already provided a filename that they wish to create.
// Postcondition: All playlists have been saved. 
//
// @fstream ofstream: The file that will be written to.
// @vector<Playlist> playlistList: A list of all playlists that exist.
void savePlaylists(ofstream& ofstream, vector<Playlist>& playlistList);

// Validates that a given line is in the right format.
//
// Precondition:  A file has been accessed.
// Postcondition: The entire line has been checked to see if it is valid.
//
// @string fileLine: A single line of the file containing songs.
bool validLine(string fileLine);

//
// Precondition:  The user put a command on the input line
// Postcondition: The command will be returned as an int from 1-14
//
//
// @string command: The command the user input.
int commandAsInt(string command);

// Parses the command line arguments for ease of access.
//
// Precondition:  At least a command was given on the command line.
// Postcondition: At least a command has been assigned a value. 
//
// @string& command:   The command to be executed.
// @string& arg1:      The first argument on the line after the command.
// @string& arg2:      The second argument on the line after the command.
// @string entireLine: The entire line of user input.
void parseCLA(string& command, string& arg1, string& arg2, string entireLine);

// Finds a Playlist with the the name playlistName
//
// Precondition:  There is a list of playlists.
// Postcondition: The playlist was found if it exists.
//
// @string playlistName:           The name of the playlist wanting to be found.
// @vector<Playlist> playlistList: A list of all playlists that exist.
int findPlaylist(string playlistName, vector<Playlist>& playlistList);

// Provides an explanation for all commands.
string help();

#endif