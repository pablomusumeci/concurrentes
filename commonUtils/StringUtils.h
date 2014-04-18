/*
 * StringUtils.h
 *
 *  Created on: 12/04/2014
 *      Author: pablon
 */

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdio.h>

class StringUtils {
public:
	static int stringToInt(std::string s);
	static std::string intToString(int n);
	static std::vector<std::string> &split(std::string s, char delim, std::vector<std::string> &elems);
	static std::vector<std::string> split(std::string s, char delim);
};

#endif /* STRINGUTILS_H_ */
