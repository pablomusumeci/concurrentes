/*
 * utils.h
 *
 *  Created on: 10/04/2014
 *      Author: javier
 */

#ifndef UTILS_H_
#define UTILS_H_

std::string intToString(int n){
	char c[200];
	sprintf(c, "%i", n);
	std::string res = c;
	return res;
}

#endif /* UTILS_H_ */
