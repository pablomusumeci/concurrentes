/*
 * Empleados.cpp
 *
 *  Created on: 18/04/2014
 *      Author: javier
 */

#include "Empleados.h"
#include "../Properties/Properties.h"
#include <stdlib.h>

struct _empleados{
	int empleados[MAX_EMPLEADOS];
};

Empleados::Empleados(): semaforo('C'), semaforoAcceso('B') {
	this->cantidad = 0;
	Properties properties;
	std::string archivo = properties.getProperty("process.commonFile");
	try {
		memoria.crear(archivo, 'D');
	} catch (std::string &e) {
		throw e;
	}
}

int Empleados::solicitarEmpleadoLibre() {
	// Espero a tener algun empleado libre
	semaforo.p();
	// si lo hya, tomo el semaforo binario
	semaforoAcceso.p();
	bloqueEmpleados empleados = memoria.leer();
	int surtidor = -1;
	for (int i=0; i < cantidad; ++i){
		if (empleados.empleados[i] == 0) {
			// Esta libre
			surtidor = i;
			empleados.empleados[i] = 1;
			break;
		}
	}
	memoria.escribir(empleados);
	// Libero el semaforo binario
	semaforoAcceso.v();
	return surtidor;
}

void Empleados::devolverEmpleado(int surtidor) {
	// Aunque no haya empleados libres, y por lo tanto, el semaforo vale cero,
	// entro y anoto al empleado libre.
	semaforoAcceso.p();
	bloqueEmpleados empleados = memoria.leer();
	empleados.empleados[surtidor] = 0;
	memoria.escribir(empleados);
	// Aumento el semaforo porque hay un empleado libre
	semaforo.v();
	// Libero el semaforo binario de control de acceso
	semaforoAcceso.v();
}

Empleados::~Empleados() {
}

void Empleados::inicializar(int cantidad) {
	this->cantidad = cantidad;
	bloqueEmpleados empleados;
	for (int i=0; i < cantidad; ++i){
		empleados.empleados[i] = 0;
	}
	memoria.escribir(empleados);
	semaforo.inicializar(cantidad);
	semaforoAcceso.inicializar(1);
}

void Empleados::eliminarRecursos() {
	semaforo.eliminar();
	semaforoAcceso.eliminar();
//	memoria.liberar();
}
