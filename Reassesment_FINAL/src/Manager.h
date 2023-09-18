/*
 * Manager.h
 *
 *  Created on: 5 Aug 2021
 *      Author: sofia
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include <string>
#include <vector>
#include <stdexcept>
#include "Person.h"

using namespace std;

class Manager: public Person
{   public:
        // constructor should initialise name and registration number using arguments
        Manager(const string &name, int regNo);

	   // method to return registration number
	   int getRegNo() const;

    private:
	   int regNo;
	   string name;
};




#endif /* MANAGER_H_ */
