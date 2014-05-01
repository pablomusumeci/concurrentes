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
#include <Modelo/Caja.h>
#include <Seniales/SignalHandler.h>
#include <Seniales/SIGINT_Handler.h>

int depositarEnCaja(int monto){
	Caja caja;
	caja.depositar(monto);
	int montoNuevo = caja.consultar();
	return montoNuevo;
}

int main(int argc, char* argv[]){
	Logger log;
	Properties properties;
	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);
	std::string tag = "Empleado" + StringUtils::intToString(getpid());
	std::string archivoSemaforo = properties.getProperty("semaforo.surtidores");
	Semaforo semaforoSurtidor(archivoSemaforo , 's');
	//TODO: tiempo en surtidor proporcional a la plata del auto
	int timeWorking = 5;
	log.info(tag, "Comienzo del proceso empleado");
	while( sigint_handler.getGracefulQuit() == 0){
		log.info(tag, "Empleado espera por surtidor libre ");
		semaforoSurtidor.p();
		log.info(tag, "Empleado trabajando ");
		sleep(timeWorking);
		semaforoSurtidor.v();
		log.info(tag, "Empleado termino de trabajar, libera surtidor");
		//TODO: empleado deposita en la caja
		int montoTotal = depositarEnCaja(10);
		log.info(tag, "Empleado deposito en caja, ahora hay " + StringUtils::intToString(montoTotal));
	}

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
