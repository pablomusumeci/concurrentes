/*
 * procesoCaja.cpp
 *
 *  Created on: 20/06/2014
 *      Author: javier
 */
#include <iostream>
#include <string>
#include "Logger/Logger.h"
#include <Properties/Properties.h>
#include <Seniales/SignalHandler.h>
#include <Seniales/SIGINT_Handler.h>
#include <Cola.h>
#include <unistd.h>
#include <StringUtils.h>
#include <errno.h>
int main(char *args[], int argc){

	Logger log;
	std::string TAG = "Proceso Caja";
	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);
	std::string archivoEmpleado = "";
	// Lectura de Properties
	try{
		Properties properties;
		archivoEmpleado = properties.getProperty("process.empleado");
	} catch (...){
		log.fatal(TAG, "Error leyendo las properties");
		return 1;
	}

	Cola<st_peticion> colaPeticiones(archivoEmpleado,'d');
	Cola<st_peticion> colaRespuestas(archivoEmpleado,'e');
	int caja = 0;
	st_peticion peticion;
	while (sigint_handler.getGracefulQuit() == 0) {

		int resultado = colaPeticiones.leer(-3, &peticion);
		if (resultado != -1){
			log.debug(TAG, "Peticion ID: " + StringUtils::intToString(peticion.id) + " $ " + StringUtils::intToString(peticion.dinero));
			caja += peticion.dinero;
			peticion.dinero = caja; // respondo con el dinero que hay ahora en la caja
			peticion.mtype = (long)peticion.id; // se lo envio al que me lo mando
			colaRespuestas.escribir(peticion);
		} else {
			if (errno == EINTR){
				log.debug(TAG, "Recibi señal mientras leia de colaPeticiones.");
			} else {
				log.error(TAG, "Error leyendo de colaPeticiones. ERRNO:" + StringUtils::intToString(errno));
			}
		}
	}

	SignalHandler::getInstance()->destruir();
	log.info(TAG, "Ejecucion finalizada");
	return 0;
}

