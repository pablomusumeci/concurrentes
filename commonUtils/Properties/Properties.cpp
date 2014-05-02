/*
 * Properties.cpp
 *
 *  Created on: 12/04/2014
 *      Author: javier
 */

#include "Properties.h"
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "../StringUtils.h"
#include "../Logger/PropertiesNotFoundException.h"

Properties::Properties() {
	std::ifstream properties(APPLICATION_PROPERTIES);
	if (!properties.is_open()) {
		std::string msj = "No se pudo abrir el archivo de properties";
		throw(new PropertiesNotFoundException(msj));
	}
	while (!properties.eof()) {
		std::string linea;
		getline(properties, linea);
		if (linea.empty()){
			continue;
		}
		std::vector<std::string> tokens = StringUtils::split(linea, '=');
		this->properties[tokens[0]] = tokens[1];
	}
}

std::string Properties::getProperty(const std::string clave) {
	return this->properties[clave];
}

std::string Properties::getProperty(const char* clave) {
	return this->getProperty(std::string(clave));
}

Properties::~Properties() {
}

