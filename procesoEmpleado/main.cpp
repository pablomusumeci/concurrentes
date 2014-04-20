/*
 * main.cpp
 *
 *  Created on: 05/04/2014
 *      Author: javier
 */
#include <cstdio>
#include <Logger/Logger.h>
#include <Properties/Properties.h>
#include <StringUtils.h>
#include <Semaforo.h>
#include <Modelo/Auto.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	Logger log;
	Properties properties;
	std::string tag = "Empleado" + StringUtils::intToString(getpid());
	std::string archivoSemaforo = properties.getProperty("semaforo.surtidores");
	Semaforo semaforoSurtidor(archivoSemaforo , 's');
	//TODO: tiempo en surtidor proporcional a la plata del auto
	int timeWorking = 5;
	log.info(tag, "Comienzo del proceso empleado");
	log.info(tag, "Empleado espera por surtidor libre ");
	semaforoSurtidor.p();
	log.info(tag, "Empleado trabajando ");
	sleep(timeWorking);
	semaforoSurtidor.v();
	log.info(tag, "Empleado termino de trabajar, libera surtidor");
	//TODO: empleado deposita en la caja

	return 0;
}

/**
 * Calcula el tiempo que el proceso empleado duerme
 * en base a la cantidad de dinero que tiene el auto
 * con el cual va a estar ocupado.
 */
int tiempoDeTrabajo(Auto& at){
	return (at.getDinero() % 10) + 2;
}
