/*
 * Caja.cpp
 *
 *  Created on: 18/04/2014
 *      Author: javier
 */

#include "Caja.h"
#include <string>
#include "../Properties/Properties.h"

Caja::Caja():semaforo('A') {
	Logger log;
	Properties properties;
	std::string archivo = properties.getProperty("process.commonFile");
	try {
		memoria.crear(archivo, 'E');
	} catch (std::string &e) {
		log.fatal("Caja", e);
		throw e;
	}
}

Caja::~Caja() {
}

void Caja::depositar(int cobro){
	int ret = semaforo.p();
	if (ret == -1 ){
		return;
	}
	int monto = memoria.leer();
	memoria.escribir(monto + cobro);
	semaforo.v();
}

int Caja::consultar(){
	int ret = semaforo.p();
	if (ret == -1){
		return -1;
	}
	int monto = memoria.leer();
	semaforo.v();
	return monto;
}

void Caja::inicializar(int montoInicial) {
	semaforo.inicializar(1);
	memoria.escribir(montoInicial);
}

void Caja::eliminarRecursos() {
	semaforo.eliminar();
}
