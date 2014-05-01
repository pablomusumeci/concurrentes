/*
 * main.cpp
 *
 *  Created on: 18/04/2014
 *      Author: javier
 */

#include <cstdio>
#include <Logger/Logger.h>
#include <Fifo/FifoEscritura.h>
#include <Modelo/Auto.h>
#include <Properties/Properties.h>
#include <Seniales/SignalHandler.h>
#include <Seniales/SIGINT_Handler.h>
#include "AutoFactory.h"

int main(int argc, char* argv[]) {
	try {
	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);
	std::string tag = "Generador de autos";
	Properties properties;
	std::string archivoFifo = properties.getProperty("fifo.generador.jde");
	Logger log;
	log.info(tag, "Arranca el generador");
	AutoFactory factory;
	FifoEscritura canal(archivoFifo);
	canal.abrir() ;

	while( sigint_handler.getGracefulQuit() == 0){
		Auto* automovil = factory.generar();
		std::string mensaje = automovil->serializar();
		log.info(tag, "Enviando auto: " + mensaje + " Largo: " + StringUtils::intToString(mensaje.length()));
		canal.escribir( static_cast < const void*>( mensaje.c_str() ) , mensaje.length());
		delete automovil;
		sleep(2);
	}

	canal.cerrar();
	canal.eliminar();
	log.info(tag, "Ejecucion finalizada.");
	return 0;
	} catch (char const* e) {
		std::cout << "Error " << e << std::endl;
	}
}
