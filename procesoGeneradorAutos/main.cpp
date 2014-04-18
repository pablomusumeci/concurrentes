/*
 * main.cpp
 *
 *  Created on: 18/04/2014
 *      Author: javier
 */

#include <cstdio>
#include <Logger/Logger.h>

int main(int argc, char* argv[]) {
	std::string tag = "Generador de autos";
	std::string mensaje = "Generando...";
	Logger log;
	log.info(tag, mensaje + "1");

	return 0;
}

