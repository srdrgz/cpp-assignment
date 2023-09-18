/*
 * ReadWords.cpp
 *
 *  Created on: 21 Aug 2021
 *      Author: sofia
 */

using namespace std;

#include "ReadWords.h"
#include <stdio.h>
#include <cctype>
#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>

string removePunct(string word){
	//removes trailing and leading punctuation and leaves all punctuation inside word
	int indexL;
	for(int x=0;x<word.size();x++){
		if(isalpha(word[x])){
			indexL = x;
			break;
		}
	}
	int indexT;
	for(int y=word.size()-1;y>=0;y--){
			if(isalpha(word[y])){
				indexT = y;
				break;
			}
		}
	string cleanWord;
	for(int i= indexL ; i<=indexT;i++){
		cleanWord = cleanWord + word[i];
	}
  return cleanWord;
}

ReadWords::ReadWords(const char *fname)
{   wordfile.open(fname);//open file
    if (!wordfile)
    {   cout << "Failed to open " << fname << endl;
        exit(1);
    }
    wordfile >> nextword;
    eoffound = false;
}

string ReadWords::getNextWord()
{
  string word = nextword;
  wordfile >> nextword; //one word lookahead

  if (wordfile.eof()) eoffound = true;

  word = removePunct(word);
  string wordLower = "";
  for(char const c: word){
	  char x = (char)tolower(c);
	  wordLower = wordLower + x;
  }
   bool isWord = false;
   //convert to lower
  for(char const &c:wordLower){
	  if(isalpha(c)) isWord=true;
  }
  //check that word contains a letter, and if not return an empty string;
  if(!isWord) wordLower="";
  return wordLower;
}

bool ReadWords::isNextWord()
{ return !eoffound;
}
//gets phrases for each word and adds it to the phrases array in the same position as the word it contains from the words array
bool ReadWords::getPhrase(string word, int position){
	ifstream f;
	f.open("mySample.txt");
	string n;
	bool reading = true;
		while (reading){
			if (!f.eof()){
				getline(f,n,'.');
				stringstream ss(n);
				string wordPhrase;
				bool belong = false;
				while (ss >> wordPhrase){
					if (wordPhrase == word) {belong = true; }
				}
				if(belong){this->phrases[position] = n;reading = false;break;}
				//cout << "hello";
			}
			else{
				reading = false;
				f.close();
			}
			}
	return 1;
}
//returns the phrase for the current word to be guessed
string ReadWords::getPhraseForWord(string word){
	string phrase;
	for(int i=0;i<=4;i++){
		if(words[i] == word) phrase = phrases[i];
	}

	return phrase;
}
//selects a random word from the words array
string ReadWords::selectWord(){
	int word = rand() % 5;
	return words[word];
}
//gets the words in the range from the arguments (level parameters)and inserts them into the words array
bool ReadWords::getWords(int min,int max){
	for(int i=0;i<=4;i++){
		bool size = false;
		string newWord;
		while(!size){
			newWord = getNextWord();
			if(newWord.size() >= min && newWord.size() <= max){
				size = true;
			}
		}
		words[i] = newWord;
		getPhrase(words[i],i);
	}
	close();
	return 0;
}

void ReadWords::close()
{ wordfile.close();
}



