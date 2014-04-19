/*
 * main.cpp
 *
 *  Created on: 05/04/2014
 *      Author: javier
 */
#include <cstdio>
#include <Logger/Logger.h>
#include <Properties/Properties.h>
#include <Semaforo.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

string convertToString(const int& numero);

int main(int argc, char* argv[]){

	string tag = "Empleado " + convertToString(getpid());

//TODO: tiempo en surtidor proporcional a la plata del auto
	int timeWorking = 5;
	Logger log;
	log.info(tag, "Comienzo del proceso empleado ");
	Properties properties;
	std::string archivoSemaforo = properties.getProperty("semaforo.surtidores");
	Semaforo semaforoSurtidor(archivoSemaforo , 's');
	log.info(tag, "Empleado espera por surtidor libre ");

	semaforoSurtidor.p();
	log.info(tag, "Empleado trabajando ");
	sleep(timeWorking);
	semaforoSurtidor.v();
	log.info(tag, "Empleado termina de trabajar, libera surtidor ");

	return 0;
}

string convertToString(const int& numero){
	std::stringstream temp;
	std::string str;
	temp << numero;
	temp >> str;
	return str;
}
