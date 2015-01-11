/*******************************************************************************
Title:         dictionary.h
Author:        David Morant
Created on:    September 26, 2014
Description:   Finds all words in a dictionary that can be made
               out of the letters of a given word.
Purpose:       Demonstrates backtracking and partial solutions to
               check a combination of letters against a dictionary,
               and appends more characters if possible.
Usage:         ./findwords dictionaryfile.txt
Build with:    g++ -o findwords find_words.cpp dictionary.cpp
Modifications: September 26: Improved Documentation

               September 27: Refined algorithm for finding all
                             combinations of letters in a word.

               September 28: Added flexibility by using vectors
                             instead of fixed sized arrays.
********************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Checks if a given file is valid.
//
// Precondition:  None.
// Postcondition: None.
//
// @string filename:                  the name of a file to be checked.
bool validFile(string filename);


// Populates an array, dictionary, based on the contents of a provided file.
//
// Precondition:  The accompanying file is valid.
// Postcondition: A dictionary has been created.
//
// @string filename:                  the name of a file containing a list of words.
// @vector<string>& dictionary:       an empty list to be filled with the words found in filename.
void populateDictionary(string filename, vector<string>& dictionary);


// Sequentially searches the dictionary for partial and full matches.
//
// Precondition:  A dictionary exists.
// Postcondition: A vector contains the indexes of all words that were found
//                in the dictionary.
//
// @vector<string>& dictionary:       a populated list of words.
// @string searchKey:                 a string of letters to be searched.
// @vector<int>& foundWordPositions:  a list of the positions where words were found.
bool inDictionary(const vector<string>& dictionary, string searchKey,
                      vector<int>& foundWordPositions);


// Finds all words that start with a given prefix.
//
// Precondition:  A dictionary has already been created.
// Postcondition: All possible words starting with a given prefix have been found.
//
// @string prefix:                    the beginning portion of the string you're looking for.
// @string remainingLetters:          a string of characters that can be appended
//                                    to the prefix.
// @vector<string>& dictionary:       a populated list of words.
// @vector<int>& foundWordPositions:  a list of the positions where words were found.
// @string originalWord:              the original word that the user had input.
bool findWords(string prefix, string remainingLetters,
               const vector<string>& dictionary,
               vector<int>& foundWordPositions,
               string originalWord);


// Delete the letters of lettersToDelete that are found within word.
//
// Precondition:  None.
// Postcondition: None.
// return:        a string of characters missing the letters of lettersToDelete.
//
// @string word:                     a given string of characters.
// @string lettersToDelete:          a string of letters to be deleted from word.
string deleteLetters(string word, string lettersToDelete);


// Sorts a list of numbers.
//
// Precondition:  foundWordPositions is a vector of integers with a size > 0.
// Postcondition: The integers in foundWordPositions are sorted.
//
// @vector<int>& foundWordPositions: a list of positions to be sorted
void sortWords(vector<int>& foundWordPositions);


// Deletes duplicate entries in a vector of ints.
//
// Precondition:  foundWordPositions is a sorted list of integers.
// Postcondition: No two values in foundWordPositions are the same.
//
// @vector<int>& foundWordPositions: a list of positions.
void deleteDuplicates(vector<int>& foundWordPositions);


// Change all letters in a given string to lowercase.
//
// Precondition:  userWord is a string without spaces.
// Postcondition: All characters in the user's word will be lowercase if possible.
//
// @string& userWord:                a string to be converted to lowercase.
void changeToLowercase(string& userWord);

#endif
