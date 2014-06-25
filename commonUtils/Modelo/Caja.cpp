/*
 * Caja.cpp
 *
 *  Created on: 18/04/2014
 *      Author: javier
 */

#include "Caja.h"
#include <string>
#include "../StringUtils.h"
#include "../Properties/Properties.h"

Caja::Caja(){
	Logger log;
	Properties properties;
	std::string archivo = properties.getProperty("process.empleado");
	try {
		colaPeticiones = new Cola<st_peticion>(archivo,'d');
		colaRespuestas = new Cola<st_peticion>(archivo,'e');
	} catch (std::string &e) {
		log.fatal("Caja", e);
		throw e;
	}
}

Caja::~Caja() {
	delete colaPeticiones;
	delete colaRespuestas;
}

// devuelve nuevo saldo
int Caja::depositar(int cobro, long prioridad, std::string TAG){
	st_peticion peticion;
	pid_t id = getpid();
	peticion.mtype = prioridad;
	peticion.id = id;
	peticion.dinero = cobro;

	// request para escribir en caja
	log.debug(TAG, "Esperando acceso a la caja.");
	int resultado = colaPeticiones->escribir(peticion);

	if (resultado < 0){
		log.debug(TAG, "Error enviando peticion para escribir en la caja.");
		return -1;
	}
	// leo respuesta dirigida a mi
	resultado = colaRespuestas->leer(id ,&peticion);

	if (resultado < 0){
			log.debug(TAG, "Error leyendo peticion de la caja.");
			return -1;
	}

	return peticion.dinero;
}

int Caja::consultar(long prioridad, std::string TAG){
	return depositar(0, prioridad, TAG);
}


void Caja::eliminarRecursos() {
	// se destruyen en el procesoPrincipal
	colaPeticiones->destruir();
	colaRespuestas->destruir();
}
