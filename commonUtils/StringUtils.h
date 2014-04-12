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
#include <iostream>
#include <stdio.h>

class StringUtils {
public:
	static int stringToInt(std::string s);
	static std::string intToString(int n);
};

#endif /* STRINGUTILS_H_ */
