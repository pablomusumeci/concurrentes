/*
 * procesoCaja.cpp
 *
 *  Created on: 20/06/2014
 *      Author: javier
 */
#include <iostream>
#include <string>
#include "Logger/Logger.h"

int main(char *args[], int argc){
	std::cout << "Hello" << std::endl;
	Logger log;
	std::string tag, msj;
	tag = "PROCESO CAJA";
	msj = "corriendo...";
	log.info(tag, msj);
	return 0;
}

