/*
 * Person.h
 *
 *  Created on: 5 Aug 2021
 *      Author: sofia
 */

#ifndef PERSON_H_
#define PERSON_H_
#include <string>

using namespace std;

class Person
{   public:
       Person(const string &name);
	   string getName() const;
	   void changeName(const string &newName);
    protected:
	   string name;
};




#endif /* PERSON_H_ */
