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
		char* copia = strdup(linea.c_str());
		char* aux;
		char* clave = strtok_r(copia, "=", &aux);
		char* valor = strtok_r(NULL, "=", &aux);
		this->properties[std::string(clave)] = std::string(valor);
		free(copia);
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

