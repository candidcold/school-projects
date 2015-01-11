/*******************************************************************************
Title:         jukebox.cpp
Author:        David Morant
Created on:    October 22, 2014
Description:   Allow the user to create and manage playlists of songs featured 
			   in a song database.
Purpose:       Experience creating a menu based user interface, and using
			   linked lists and larger classes.
Usage:         ./jukebox songslist.txt 
						*OR*
			   ./jukebox
Build with:    g++ -o jukebox jukebox.cpp songs.cpp
Modifications: October 23rd: Handled file input. 
			   October 25th: Setup switch cases for main menu.
			   October 26th & 27th: Setup switch cases for modification menu.
			   Added while loops for switch cases, as it must continue until
			   certain commands are given.
********************************************************************************/
#include "songs.h"

int main(int argc, char *argv[]) {
	// Menus
	string mainMenu = "[L/l]\t\t List the names of all playlists \n[V/v] <playlist> View a playlist \n[C/c] <playlist> Create a new playlist ... \n[M/m] <playlist> Modify a playlist ... \n[D/d] <plstlist> Delete an existing playlist \n[S/s] <filename> Save all playlist \n[H/h] Help \n[Q/q] Exit.";
	string playlistModMenu = "[L/l] <first> <last>  	List songs from database from first to last \n[A/a] <artist_key>    	List all songs whose artist contains artist_key as a substring \n[T/t] <title_key>    	List all songs whose title contains title_key as a substring \n[B/b]             	Back to Main Menu \nInsert <songid> <pos>	Insert the songid into playlist as position <pos> \nDelete <songid>      	Delete songid from playlist \nShow                	Display the songs in the playlist";

	string command = "", 				// The user's command.
		   arg1 = "",					// The user's first argument.
		   arg2 = "",					// The user's second argument.
		   inputLine;					// The entire line of user input.

	int intCommand,						// The user's command in form int.
		playlistPosition;				// The position of a playlist in playlistList.

	Playlist userPlaylist;				// A generic usermade playlist.

	ifstream inputFile;					// A stream for an input file. 
	ofstream outputFile;				// A stream for an output file.

	list<Song> songDatabase;			// A list of all songs.
	vector<Playlist> playlistList;		// A vector of all playlists.

	bool songsStored;					// A flag to show if songs have been stored in the database.

	// Handle which file the program will end up using. 
	if (argv[1]) {
		inputFile.open(argv[1]);
	} else {
		inputFile.open("songs.csv");
	}


	// Check if the file being used can be opened. 
	if (!validFile(inputFile)) {
		cerr << "The file provided could not be opened!" << endl;
		exit(0);
	}

	// Store the songs in a database. After that, we're done with the inputfile.
	songsStored = storeSongs(songDatabase, inputFile);
	inputFile.close();


	// If all songs in the file are not formatted correctly, break out.
	if (songsStored == false) {
		cerr << "The file provided is not formatted correctly." << endl;
		exit(0);
	}

	cout << songDatabase.size() << " songs loaded \n" << endl;

	// Continue showing the main menu until the user chooses to exit.
	do {
		// Display the main menu and handle the arguments given.
		cout << "Main Menu:" << endl;
		cout << mainMenu << endl;
		cout << endl;
		cout << "What would you like to do?: ";
		getline(cin, inputLine);
		parseCLA(command, arg1, arg2, inputLine);
		intCommand = commandAsInt(command);


		// Preface: All commands that require additional arguments check to see
		// 			if that argument has been supplied.
		//
		//			Every time a playlist is a required argument, check to see
		//			if that playlist exists.
		//
		//			Each case echos back the command that the user input to let 
		// 			them know that their command has been executed.	
		switch (intCommand) {
			// The command was L
			case 1:
				// If they have no playlists, tell them.
				if (playlistList.size() == 0) {
					cout << "You have no playlists" << "\n" << endl;
					break;
				}

				// Otherwise, list all of their playlists
				for (int i = 0; i < playlistList.size(); i++) {
					cout << playlistList[i].getPlayListName() << ": " <<
					to_string(playlistList[i].getPlaylistSize()) << " songs" << endl;
				}

				cout << commandExecuted(command) << "\n" <<endl;
				break;

			// The command was V
			case 2:
				if (arg1 == "") {
					cerr << "You must provide the argument for command " + command << "\n" <<endl;
					break;
				} 

				playlistPosition = findPlaylist(arg1, playlistList);

				// If no playlist exists with that name, tell the user. 
				if (playlistPosition == -1) {
					cerr << "No playlist exists with the name " << arg1 << endl;
					break;
				}

				// Otherwise, list the songs.
				cout << playlistList[playlistPosition].getPlayListName() << endl;
				cout << playlistList[playlistPosition].listSongs() << endl;
				cout << commandExecuted(command) << "\n" <<endl;
				break;

			// The command was C
			// There is no break if this statement is successful, as the value of intCommand is 
			// being changed in order to access the modification menu.
			case 3:
				if (arg1 == "") {
					cerr << "You must provide the argument for command " + command << "\n" <<endl;
					break;
				} 

				playlistPosition = findPlaylist(arg1, playlistList);

				// If a playlist already exists with this name, tell the user and break.
				if (playlistPosition != -1) {
					cerr << "A playlist already exists with name " << arg1 << "\n" << endl;
					break;
				}

				// Make a playlist
				userPlaylist.setPlayListName(arg1);
				playlistList.push_back(userPlaylist);

				cout << commandExecuted(command) << "\n" <<endl;
				intCommand = 4;

			// The command was M
			// Continue showing the modification menu until they press B.
			case 4:
				if (arg1 == "") {
					cerr << "You must provide the argument for command " + command << "\n" <<endl;
					break;
				}

				playlistPosition = findPlaylist(arg1, playlistList);

				// If no playlist exists with which to modify, tell the user and break out.
				if (playlistPosition == -1) {
					cerr << "No playlist exists with the name " << arg1 << "\n" << endl;
					break;
				}

				do {
					// Display the modification menu and handle the arguments given.
					cout << "Playlist Modification Mode:" << endl;
					cout << playlistModMenu << endl;
					cout << endl;
					cout << "What would you like to do?: ";
					getline(cin, inputLine);
					parseCLA(command, arg1, arg2, inputLine);
					intCommand = commandAsInt(command);

					switch (intCommand) {
						// The command was L
						case 1:
							if (arg1 == "" || arg2 == "") {
								cerr << "You must provide the necessary arguments for command " + command << "\n" <<endl;
								break;
							}

							// Both arguments must be integers in order to list the songs
							// that fall within that range.
							if (atoi(arg1.c_str()) < 0 || atoi(arg2.c_str()) < 0) {
								cerr << "Arguments 1 and 2 must be integers" << "\n" << endl;
								break;
							}

							cout << playlistList[playlistPosition].listSongs(atoi(arg1.c_str()), atoi(arg2.c_str())) << endl;
							cout << commandExecuted(command) << "\n" << endl;
							break;

						// The command was A
						case 9:
							if (arg1 == "") {
								cerr << "You must provide the argument for command " + command << "\n" <<endl;
								break;
							} 

							cout << playlistList[playlistPosition].listSongsByArtist(arg1) << endl;

							cout << commandExecuted(command) << "\n" << endl;
							break;

						// The command was T
						case 10:
							if (arg1 == "") {
								cerr << "You must provide the argument for command " + command << "\n" <<endl;
								break;
							} 

							cout << playlistList[playlistPosition].listSongsWithTitle(arg1) << endl;

							cout << commandExecuted(command) << "\n" << endl;
							break;

						// The command was B
						case 11:
							cout << "Back to main menu" << endl;
							cout << "\n" << endl;
							break;

						// The command was Insert
						case 12:
							if (arg1 == "" || arg2 == "") {
								cerr << "You must provide the necessary arguments for command " + command << "\n" <<endl;
								break;
							}

							if (atoi(arg1.c_str()) < 0 || atoi(arg2.c_str()) < 0) {
								cerr << "Arguments 1 and 2 must be integers" << "\n" << endl;
								break;
							}

							playlistList[playlistPosition].insertSong(atoi(arg1.c_str()), atoi(arg2.c_str()), songDatabase);
							cout << commandExecuted(command) << "\n" << endl;
							break;

						// The command was Delete
						case 13:
							if (arg1 == "") {
								cerr << "You must provide the argument for command " + command << "\n" <<endl;
								break;
							}

							if (atoi(arg1.c_str()) < 0) {
								cerr << "Argument 1 must be an integer" << "\n" << endl;
								break;
							}

							playlistList[playlistPosition].deleteSong(atoi(arg1.c_str()));
							cout << commandExecuted(command) << "\n" << endl;
							break;

						// The command was Show
						case 14:
							cout << playlistList[playlistPosition].listSongs() << endl;
							cout << commandExecuted(command) << "\n" << endl;
							break;

						default:
							cout << "You've input an invalid command" << "\n" <<endl;
					}

				} while (intCommand != 11);

				break;

			// The command was D
			case 5:
				if (arg1 == "") {
					cerr << "You must provide the argument for command " + command << "\n" <<endl;
					break;
				}

				if (!deletePlayList(arg1, playlistList)) {
					cerr << "No playlist exists with the name " << arg1 << endl;
					break;
				}

				cout << commandExecuted(command) << "\n" << endl;
				break;

			// The command was S
			case 6:
				if (arg1 == "") {
					cerr << "You must provide the argument for command " + command << "\n" <<endl;
					break;
				}

				outputFile.open(arg1);
				savePlaylists(outputFile, playlistList);
				outputFile.close();
				cout << commandExecuted(command) << "\n" <<endl;
				break;

			// The command was H
			case 7:
				cout << help() << endl;
				cout << endl;
				break;

			// The command was Q
			case 8:
				break;

			// An invalid command was given
			default:
				cout << "You've not provided a valid command" << "\n" << endl;
		}
		// Quitting is command 8.
	} while (intCommand != 8);


	return 0;
}

