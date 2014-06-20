/*
 * Caja.h
 *
 *  Created on: 18/04/2014
 *      Author: javier
 */

#ifndef CAJA_H_
#define CAJA_H_

#include "../Semaforo.h"
#include "../Cola.h"
#include "../MemoriaCompartida.h"
#include "../Logger/Logger.h"
#include <unistd.h>
/**
 * Clase Caja que se usa a modo de proxy para operar sobre ella.
 * Usa un semaforo, identificado por el archivo comun (de properties) y
 * el caracter A.
 * Usa un segmento de Memoria Compartida identificada por el archivo y el caracter E
 */
class Caja {
public:
	Caja();

	/**
	 * Suma al valor de la caja. Es bloqueante.
	 */
	int depositar(int monto, long prioridad, std::string TAG);
	/**
	 * Devuelve el valor actual de la caja. Tambien es bloqueante.
	 * Si se interrumpe al proceso mientras esperaba en la caja,
	 * devuelve -1
	 */
	int consultar(long prioridad, std::string TAG);
	void eliminarRecursos();
	virtual ~Caja();
private:
//	Semaforo semaforo;
	Logger log;
	Cola<st_peticion>* colaPeticiones;
	Cola<st_peticion>* colaRespuestas;
//	MemoriaCompartida<int> memoria;
};

#endif /* CAJA_H_ */
