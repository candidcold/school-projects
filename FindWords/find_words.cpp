/******************************************************************************
Title:         find_words.cpp
Author:        David Morant
Created on:    September 26, 2014
Description:   Finds all words in a dictionary that can be made
               out of the letters of a given word.
Purpose:       Demonstrates backtracking and partial solutions to
               check a combination of letters against a dictionary,
               and appends more characters if possible.
Usage:         ./findwords dictionaryfile.txt
Build with:    g++ -o findwords find_words.cpp dictionary.cpp
Modifications: September 27: Implemented sortWords and deleteDuplicates.
                             Improved error handling.

               September 28: Added flexibility by using vectors
                             instead of fixed sized arrays.
********************************************************************************/

#include "dictionary.h"

int main(int argc, char *argv[]) {

  vector<string> dictionary; // Store the words making up our dictionary.
  bool otherWords;           // Store the value of the call of findWords.
  string userWord,           // Store the user's word.
         userAnswer;         // Store the user's answer.

  // Check if the file the user provided on the command line
  // is a valid file to check.
  if (validFile(argv[1]))
    populateDictionary(argv[1], dictionary);
  else
    exit(0);

  do {

    cout << "Enter a string of characters without spaces: ";
    cin >> userWord;

    // If the user's word is invalid, prompt them to enter it again until
    // they get it right.
    while (userWord.length() < 2 || userWord.length() > 32){
      if (userWord.length() < 2) {
        cout << "Your string is too short, please try again: ";
        cin >> userWord;
      } else if (userWord.length() > 32) {
        cout << "Your string is too long, please try again: ";
        cin >> userWord;
      }
    }

    // You must reinitialize this value each time to avoid keeping older words
    // that were found.
    vector<int> foundWordPositions;

    // There are no uppercase letters in our dictionary, therefore we must
    // change all of the letters to lowercase before searching.
    changeToLowercase(userWord);
    cout << "Your word was: " << userWord << endl;

    // Search for possible words:
    // 1. Use 1 letter of the user's word as the prefix
    // 2. Obtain all letters of the user's word that are not the prefix
    // 3. Loop through until you've tried every possible letter as a prefix
    for (int i = 0; i < userWord.length(); i++) {
      otherWords = findWords(userWord.substr(i, 1),
                             userWord.substr(0, i) + userWord.substr(i+1),
                             dictionary,
                             foundWordPositions, userWord);
    }

    // Sort the words in our list of found words, and then delete duplicates
    sortWords(foundWordPositions);
    deleteDuplicates(foundWordPositions);

    if (foundWordPositions.size() == 0) {
      cout << "No words were found" << endl;
    } else {
      cout << "The found words were:" << endl;

      // Print all of the found words
      for (int i = 0; i < foundWordPositions.size(); i++){
        cout << dictionary[foundWordPositions[i]] << endl;
      }
    }


    cout << "Would you like to continue or quit? ";
    cin >> userAnswer;

    // Change the answer to lowercase to allow for different variations of the
    // word 'quit' for flexibility.
    changeToLowercase(userAnswer);
  } while (userAnswer != "quit");

  return 0;
}
