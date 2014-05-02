/*
 * Empleados.cpp
 *
 *  Created on: 18/04/2014
 *      Author: javier
 */

#include "Empleados.h"
#include "../Properties/Properties.h"
#include <stdlib.h>

Empleados::Empleados(): semaforo('B') {
	Properties properties;
	std::string archivo = properties.getProperty("process.commonFile");
	try {
		memoria.crear(archivo, 'D');
	} catch (std::string &e) {
		throw e;
	}
}

bool Empleados::hayEmpleadoLibre() {
	// Tomo el semaforo binario
	semaforo.p();
	int libres = memoria.leer();
	// Libero el semaforo binario
	semaforo.v();
	return libres > 0;
}

void Empleados::devolverEmpleado() {
	// Aunque no haya empleados libres, y por lo tanto, el semaforo vale cero,
	// entro y anoto al empleado libre.
	semaforo.p();
	int empleados = memoria.leer();
	empleados++;
	memoria.escribir(empleados);
	// Libero el semaforo binario de control de acceso
	semaforo.v();
}

Empleados::~Empleados() {
}

void Empleados::inicializar(int cantidad) {
	memoria.escribir(cantidad);
	semaforo.inicializar(1);
}

void Empleados::eliminarRecursos() {
	semaforo.eliminar();
}

void Empleados::tomarEmpleado() {
	semaforo.p();
	int empleados = memoria.leer();
	empleados--;
	memoria.escribir(empleados);
	// Libero el semaforo binario de control de acceso
	semaforo.v();
}
