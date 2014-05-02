/*
 * Empleados.h
 *
 *  Created on: 18/04/2014
 *      Author: javier
 */

#ifndef Empleados_H_
#define Empleados_H_

#include "../Semaforo.h"
#include "../MemoriaCompartida.h"

/**
 * Clase que representa al conjunto de empleados. Guarda un entero en MC.
 * Usa un semaforo binario, identificado con el caracter 'B'.
 * Tambien usa un segmento de Memoria Compartida identificada por el archivo y el caracter 'D'.
 */
class Empleados {
public:
	Empleados();
	/**
	 * Inicializa la cantidad de empleados libres.
	 * Sera usado por el proceso principal, sino los demas procesos leeran basura.
	 */
	void inicializar(int cantidad);
	/**
	 * Consulta si hay algun empleado libre.
	 */
	bool hayEmpleadoLibre();
	/**
	 * Devuelve al empleado, aumentando en una unidad la cantidad de empleados libres.
	 */
	void devolverEmpleado();

	/**
	 * Toma un empleado libre, decrementando la cantidad de libres.
	 */
	void tomarEmpleado();

	/**
	 * Elimina los recursos de IPC utilizados
	 */
	void eliminarRecursos();
	virtual ~Empleados();
private:
	Semaforo semaforo;
	MemoriaCompartida<int> memoria;
};

#endif /* Empleados_H_ */
