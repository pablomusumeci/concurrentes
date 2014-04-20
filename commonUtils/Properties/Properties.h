/*
 * Properties.h
 *
 *  Created on: 12/04/2014
 *      Author: javier
 */

#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include <string>
#include <map>
#define APPLICATION_PROPERTIES "application.properties"

class Properties {
private:
	std::map<std::string, std::string> properties;
public:
	Properties();
	std::string getProperty(const char* clave);
	std::string getProperty(const std::string clave);
	virtual ~Properties();
};

#endif /* PROPERTIES_H_ */
