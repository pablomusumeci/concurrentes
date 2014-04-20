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

#define MAX_EMPLEADOS 100

typedef struct _empleados bloqueEmpleados;

/**
 * Clase que representa la caja. Guarda un entero en MC.
 * Usa dos semaforos, identificado por el archivo comun (de properties) y
 * un caracter.
 * El semaforo binario de acceso usa el caracter 'B'.
 * EL de cantidad de empleados, el caracter 'C'.
 * Tambien usa un segmento de Memoria Compartida identificada por el archivo y el caracter 'D'.
 */
class Empleados {
public:
	Empleados();
	/**
	 * Inicializa el vector de empleados, estableciendo a todos como libres.
	 * Sera usado por el proceso principal, sino los demas procesos leeran basura.
	 */
	void inicializar(int cantidad);
	/**
	 * Busca un empleado libre, y devuelve su ID. Es bloqueante hasta que se desocupe alguno.
	 */
	int solicitarEmpleadoLibre();
	/**
	 * Devuelve al empleado, es decir, lo marca como libre segun el ID.
	 * Es bloqueante por el semaforo de acceso, es decir, cuando toma el control
	 * marca el empleado com libre, aunque el otro semaforo este en 0.
	 */
	void devolverEmpleado(int surtidor);
	void eliminarRecursos();
	virtual ~Empleados();
private:
	int cantidad;
	Semaforo semaforo;
	Semaforo semaforoAcceso;
	MemoriaCompartida<bloqueEmpleados> memoria;
};

#endif /* Empleados_H_ */
