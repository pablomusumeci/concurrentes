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

std::vector<std::string> &StringUtils::split(std::string s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> StringUtils::split(std::string s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

