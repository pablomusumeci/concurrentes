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
	Properties properties;
	std::string archivo = properties.getProperty("process.commonFile");
	try {
		memoria.crear(archivo, 'E');
	} catch (std::string &e) {
		throw e;
	}
}

Caja::~Caja() {
}


void Caja::depositar(int cobro){
	semaforo.p();
	int monto = memoria.leer();
	memoria.escribir(monto + cobro);
	semaforo.v();
}

int Caja::consultar(){
	semaforo.p();
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
