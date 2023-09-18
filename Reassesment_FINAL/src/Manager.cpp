/*
 * Manager.cpp
 *
 *  Created on: 5 Aug 2021
 *      Author: sofia
 */
using namespace std;

#include <iostream>
#include <string>
#include "Manager.h"

Manager::Manager(const string &name, int regNo):Person(name){
	this->name = name;
	this->regNo = regNo;
}

int Manager::getRegNo()const{
	return this->regNo;
}
