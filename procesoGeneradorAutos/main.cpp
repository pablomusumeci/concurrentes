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
#define tag "Generador de autos"
int main(int argc, char* argv[]) {
	Logger log;
	try {
		SIGINT_Handler sigint_handler;
		SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);
		Properties properties;
		std::string archivoFifo = properties.getProperty("fifo.generador.jde");
		std::string espera = properties.getProperty("constante.tiempo.generador");
		int tiempo = StringUtils::stringToInt(espera);

		log.info(tag, "Arranca el generador");
		AutoFactory factory;
		FifoEscritura canal(archivoFifo);
		canal.abrir() ;

		while( sigint_handler.getGracefulQuit() == 0){
			Auto* automovil = factory.generar();
			std::string mensaje = automovil->serializar();
			log.debug(tag, "Enviando auto: " + mensaje + " Largo: " + StringUtils::intToString(mensaje.length()));
			canal.escribir( static_cast < const void*>( mensaje.c_str() ) , mensaje.length());
			delete automovil;
			sleep(tiempo);
		}

		canal.cerrar();
		canal.eliminar();
		SignalHandler::getInstance()->destruir();
		log.info(tag, "Ejecucion finalizada.");
		return 0;
	} catch (char const* e) {
		log.error(tag, std::string(e));
		std::cout << "Error " << e << std::endl;
	}
}
