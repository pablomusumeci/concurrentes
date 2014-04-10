/*
 * main.cpp
 *
 *  Created on: 05/04/2014
 *      Author: javier
 */
#include <cstdio>
#include <Logger/Logger.h>

using namespace std;

int main(int argc, char* argv[]){
	std::string tag = "Empleado";
	std::string mensaje = "Trabajando...";
	Logger log;
	log.info(tag, mensaje+ "5");
	log.error(tag, mensaje+ "4");
	log.fatal(tag, mensaje+ "3");
	log.debug(tag, mensaje+ "2");
	log.warn(tag, mensaje + "1");

	return 0;
}

