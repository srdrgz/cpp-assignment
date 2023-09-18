/**
 * Gamer.cpp
 *
 *  Created on: 5 Aug 2021
 *      Author: sofia
 */
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <stdexcept>
#include "Gamer.h"

Gamer::Gamer(const string &name, int regNo):Person(name){
	this->name = name;
	this->regNo = regNo;
	this->scores.clear();
	this->accumulative_scores.insert(make_pair("easy",0.0));
	this->accumulative_scores.insert(make_pair("medium",0.0));
	this->accumulative_scores.insert(make_pair("hard",0.0));
}

int Gamer::getRegNo() const{
	return this->regNo;
}

vector<pair<string,float>> Gamer::scoresVector(){
	vector<pair<string,float>> scoresV;
	for(multimap<string,float>:: iterator it = this->scores.begin();it != this->scores.end();it++){
		scoresV.push_back(make_pair(it->first,it->second));
	}
	return scoresV;
}

/*updateAccumulativeScore updates the temporary accumulative score map that lasts
 * while the program is running and also updates a file with each players accumulative score for
 *  each level that is kept even after the program is exited.
 *  The method opens the scores files and copies all data into a temporary file("f2.txt"), except for the player whose
 *  score is being updated. Then the scores file is removed and the temporary file is renamed as "scores.txt".
 */
bool Gamer::updateAccumulativeScore(string difficulty, float score){
	for(multimap<string,float>:: iterator it = this->accumulative_scores.begin();it != this->accumulative_scores.end();it++){
			if(it->first == difficulty){it->second += score;}

		}
	 	ifstream f; //for reading records
	    f.open("scores.txt");
	    ofstream f2;
	    f2.open("f2.txt");
	    string n;

	   bool reading = true;
	    while (reading){
			if (!f.eof()){
				getline(f,n);
				stringstream ss(n);
				string element;
				bool belong = false;
				while (ss >> element){
					if (element == to_string(this->regNo)) {belong = true; }
				}
				if(!belong){if(!n.empty())f2 << n << endl;}
				//cout << "hello";
			}
			else{
				reading = false;
				f.close();
				f2.close();
			}
			}
	    remove("scores.txt");
	    rename("f2.txt", "scores.txt");

	    ofstream o;
	    o.open("scores.txt", ios::app);
	    string regNoUD = to_string(this->regNo);
	    float easy;
	    float medium;
	    float hard;
	    for(multimap<string,float>:: iterator it = this->accumulative_scores.begin();it != this->accumulative_scores.end();it++){
	    			if(it->first == "easy"){easy = it->second;}
	    			if(it->first == "medium"){medium = it->second;}
	    			if(it->first == "hard"){hard = it->second;}
	    		}
	    o << regNoUD << " " << easy << " " << medium << " " << hard << endl;
	    o.close();

	return 1;
}
//adds score to scores map and updates accumulative score
void Gamer::addScore(float score, string difficulty){
	this->scores.insert(make_pair(difficulty, score));
	updateAccumulativeScore(difficulty,score);

}
//gets max score from scores map
float Gamer::MaxScore()const{
	vector<float> SetOfScores;
		    for (auto it = this->scores.begin(); it != this->scores.end(); it++) {
		            SetOfScores.push_back(it->second);
		    }


	float highest = SetOfScores[0];
	for (int i=1; i< SetOfScores.size();i++){
		if(SetOfScores[i] > highest) highest = SetOfScores[i];
	}

	return highest;
}
float Gamer::MinScore()const{
	vector<float> SetOfScores;
		    for (auto it = this->scores.begin(); it != this->scores.end(); it++) {
		            SetOfScores.push_back(it->second);
		    }

	float lowest = SetOfScores[0];
	for (int i=1; i< SetOfScores.size();i++){
		if(SetOfScores[i] < lowest) lowest = SetOfScores[i];
	}

	return lowest;
}
//inserts accumulative scores into vector, loops through vector, sums scores and divides by 3 to get average
float Gamer::AverageScore()const{

	vector<float> SetOfScores;
		    for (auto it = this->accumulative_scores.begin(); it != this->accumulative_scores.end(); it++) {
		            SetOfScores.push_back(it->second);
		    }

	float sum = 0;
	for (int i=1; i< SetOfScores.size();i++){
		sum += SetOfScores[i];
	}
	float average = sum/SetOfScores.size();
	return average;
}

//gets the highest score per level from scores map
float Gamer::highestScorePerLevel(string difficulty) const {
		vector<float> SetOfScores;
	    for (auto it = this->scores.begin(); it != this->scores.end(); it++) {
	        if (it->first == difficulty)
	            SetOfScores.push_back(it->second);
	    }

	float highest = SetOfScores[0];
	for (int i=1; i< SetOfScores.size();i++){
		if(SetOfScores[i] > highest) highest = SetOfScores[i];
	}

	return highest;
}

ostream& operator<<(ostream &str, const Gamer &s){
	string hard = "hard";
	float easyAcc;
	float hardAcc;
	float mediumAcc;
	for (auto it = s.accumulative_scores.begin(); it != s.accumulative_scores.end(); it++) {
			if(it->first == "easy"){easyAcc = it->second;}
			if(it->first == "medium"){mediumAcc = it->second;}
			if(it->first == "hard"){hardAcc = it->second;}
	}
	if (s.accumulative_scores.empty()){
	str << "Name: " << s.name << "  RegNo: " << s.regNo<<". This player has no scores"; }

	else {
	str << "Name: " << s.name << "  RegNo: " << s.regNo<<"  Easy: " << easyAcc << "  Medium: "<< mediumAcc<< "  Hard: "<< hardAcc<<"  Average score: "<<s.AverageScore() << endl;}
	return str;
}

