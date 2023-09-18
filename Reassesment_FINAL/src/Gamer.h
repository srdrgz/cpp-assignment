/*
 * Gamer.h
 *
 *  Created on: 5 Aug 2021
 *      Author: sofia
 */

#ifndef GAMER_H_
#define GAMER_H_
#include <string>
#include <map>
#include <stdexcept>
#include "Person.h"

using namespace std;

class NoScoreException: public exception
{
};

class Gamer: public Person
{   public:

        // constructor should initialise name and registration number and score map to empty
        Gamer(const string &name, int regNo);

	   // method to return registration number
	   int getRegNo() const;

	   vector<pair<string,float>> scoresVector();
	   //adds score to scores map and updates accumulative score
	   void addScore(float score,string difficulty);
	   //methods to get max, min and average score of player
	   float MaxScore()const;
	   float MinScore()const;
	   float AverageScore()const;
	   //method to get highest score from the scores map per level
	   float highestScorePerLevel(string difficulty) const;
	   /*updateAccumulativeScore updates the temporary accumulative score map that lasts
	    * while the program is running and also updates a file with each players accumulative score for
	    *  each level that is kept even after the program is exited.
	    *  The method opens the scores files and copies all data into a temporary file("f2.txt"), except for the player whose
	    *  score is being updated. Then the scores file is removed and the temporary file is renamed as "scores.txt".
	    */
	   bool updateAccumulativeScore(string difficulty,float score);

    private:
	   multimap<string,float> scores;
	   int regNo;
	   string name;
	    // scores map, with each in range 0.0 to 100.0, and an
	   	//associated level of difficulty
	   map<string,float> accumulative_scores;
	   // scores map
	   //associated level of difficulty

    // friend function to output details of gamer to stream
    // Output name, regno, and accumulative score for easy, medium and hard level and average score on a single line
    // if the gamer has no scores "has no scores",output instead of the scores
    friend ostream& operator<<(ostream &str, const Gamer &s);
};

#endif /* GAMER_H_ */
