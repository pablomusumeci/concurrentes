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
	Logger::info(tag, mensaje+ "5");
	Logger::error(tag, mensaje+ "4");
	Logger::fatal(tag, mensaje+ "3");
	Logger::debug(tag, mensaje+ "2");
	Logger::warn(tag, mensaje + "1");

	return 0;
}

