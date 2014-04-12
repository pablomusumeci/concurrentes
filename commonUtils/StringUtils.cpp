/*
 * StringUtils.cpp
 *
 *  Created on: 12/04/2014
 *      Author: pablon
 */

#include "StringUtils.h"

std::string StringUtils::intToString(int n){
	char c[200];
	sprintf(c, "%i", n);
	std::string res = c;
	return res;
}

int StringUtils::stringToInt(std::string s){
	int numb;
	std::istringstream ss( s );
	ss >> numb;
	return numb;
}

