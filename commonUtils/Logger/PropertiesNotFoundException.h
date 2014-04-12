/*
 * PropertiesNotFoundException.h
 *
 *  Created on: 12/04/2014
 *      Author: javier
 */

#ifndef PROPERTIESNOTFOUNDEXCEPTION_H_
#define PROPERTIESNOTFOUNDEXCEPTION_H_

#include <string>

class PropertiesNotFoundException {
public:
	PropertiesNotFoundException(const std::string &msj);
	virtual ~PropertiesNotFoundException();
private:
	std::string msj;
};

#endif /* PROPERTIESNOTFOUNDEXCEPTION_H_ */
