/*
 * main.cpp
 *
 *  Created on: 05/04/2014
 *      Author: javier
 */
#include <cstdio>
#include <logger.h>

using namespace std;

int main(int argc, char* argv[]){
	std::string tag = "[Empleado]";
	std::string mensaje = "Trabajando...";
	logger::info(tag, mensaje);
	return 0;
}

