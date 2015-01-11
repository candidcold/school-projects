/*******************************************************************************
Title:         dictionary.cpp
Author:        David Morant
Created on:    September 26, 2014
Description:   Finds all words in a dictionary that can be made
               out of the letters of a given word.
Purpose:       Demonstrates backtracking and partial solutions to
               check a combination of letters against a dictionary,
               and appends more characters if possible.
Usage:         ./findwords dictionaryfile.txt
Build with:    g++ -o findwords find_words.cpp dictionary.cpp
Modifications: September 26: Changed binary search to sequential
                             search due to memory constraints.

               September 27: Refined algorithm for finding all
                             combinations of letters in a word.

               September 28: Added flexibility by using vectors
                             instead of fixed sized arrays.
********************************************************************************/
#include "dictionary.h"

// ***** Function Definitions *****

// Checks if a given file is valid.
bool validFile(string filename){
  ifstream inputfile(filename.c_str()); // File to be checked

  // If the file is false, that means it does not exist.
  if (inputfile) {

    // If the file isn't good, it's not able to be opened.
    if (inputfile.good()){
      return true;
    } else {
      cerr << "ERROR! File: " << filename << " cannot be opened" << endl;
      return false;
    }

  } else {
    cerr << "ERROR! File: " << filename << " does not exist" << endl;
    return false;
  }

}

// Populates an array, dictionary, based on the contents of a provided file.
void populateDictionary(string filename, vector<string>& dictionary){
  ifstream inputStream; // Inputstream of file containing words.
  string word;          // A single word.

  inputStream.open((filename).c_str());

  // Goes through the file and populates the dictionary if there
  // are more possible words to be extracted.
  do {
    inputStream >> word;

    // If after trying to get the next string you find you're at the end of the
    // file get out of there.
    if (inputStream.eof()){
      break;
    }

    // Add that word to the dictionary.
    dictionary.push_back(word);

  } while (!inputStream.eof());

  inputStream.close();
}

// Sequentially searches the dictionary for partial and full matches.
bool inDictionary(const vector<string>& dictionary, string searchKey,
                      vector<int>& foundWordPositions) {

  int wordCount = dictionary.size();
  for (int i = 0; i < wordCount; i ++) {

    // If part of the word isn't even in the dictionary, there's no reason
    // to further check if the full word is in the dictionary, therefore
    // you don't have to build upon it.
    if (searchKey == dictionary[i].substr(0,searchKey.length())) {

      // If part of the word is in the dictionary, check if it is actually
      // the full word. If it is, add it to the list of found words.
      if (searchKey == dictionary[i])
        foundWordPositions.push_back(i);

      return true;
    } // end if
  } // end for

  // If you finish searching without finding the word, it's not in the dictionary.
  return false;
}

// Finds all words that start with a given prefix.
bool findWords(string prefix, string remainingLetters,
               const vector<string>& dictionary,
               vector<int>& foundWordPositions,
               string initialWord) {


  // Base Case: if you've run out of remaining letters, you've found
  //            all possible words from this word.
  if (remainingLetters.length() <= 0) {
    return true;
  }

  bool wordFound = false;

  // Decrease the size of remainingLetters if you can't
  // find any word that starts with your prefix, as long as you can.
  //
  // If you can find a word, add a letter of remainingLetters to
  // your prefix until you've run out of remainingLetters.
  while (!wordFound && remainingLetters.length() > 0){

    // Search the dictionary for the word:
    // (a combination of a prefix and the next remaining letter)
    //
    // if the word is not in the dictionary, move on to the next
    // remaining letter.
    if (!inDictionary(dictionary,
                          prefix + remainingLetters[0],
                          foundWordPositions)) {

      // cout << "I was searching for: " << prefix + remainingLetters[0] << endl;

      // Move on to the next combination of base and remaining letters.
      remainingLetters = remainingLetters.substr(1);

    } else {

      // This combination is in the dictionary, but there may be more words
      // that begin with the same letters as this one.
      // Ex: cry is in the dictionary, but crying may be too.
      //
      // You pass the result of deleteLetters because remainingLetters is
      // NOT only the letters you've never tried before, but all letters
      // that aren't part of your prefix.
      wordFound = findWords(prefix + remainingLetters[0],
                            deleteLetters(initialWord, prefix + remainingLetters[0]),
                            dictionary, foundWordPositions, initialWord);

      // If this new word isn't in the dictionary, remove the last letter
      // and move on to the next letter of the remaining letters.
      if (!wordFound){
        remainingLetters = remainingLetters.substr(1);
      } // end inner if

    } // end outer if

  } // end while

  return wordFound;
}

// Delete the letters of lettersToDelete that are found within word.
string deleteLetters(string word, string lettersToDelete) {
  for (int i = 0; i < word.length(); i++) {
    for (int j = 0; j < lettersToDelete.length(); j++) {
      if (word[i] == lettersToDelete[j])
        word.erase(i, 1);
    }
  }
  return word;
}

// Sorts a list of numbers.
void sortWords(vector<int>& foundWordPositions) {
  sort(foundWordPositions.begin(), foundWordPositions.end());
}

// Deletes duplicate entries in the passed vector.
void deleteDuplicates(vector<int>& foundWordPositions) {
  for (int i = 1; i < foundWordPositions.size(); i++) {
    if (foundWordPositions[i] == foundWordPositions[i-1]) {
      foundWordPositions.erase(foundWordPositions.begin()+i-1);
      // You must send i back one position, or risk skipping a position
      i--;
    }
  }
}

// Change all letters in a given string to lowercase.
void changeToLowercase(string& userWord) {
  int userWordLength = userWord.length();
  char string[userWordLength+1];

  // You must account for the null character.
  for (int i = 0; i < userWordLength+1; i++) {
    string[i] = tolower(userWord[i]);
  }

  userWord = string;
}
