/*
 * Caja.h
 *
 *  Created on: 18/04/2014
 *      Author: javier
 */

#ifndef CAJA_H_
#define CAJA_H_

#include "../Semaforo.h"
#include "../MemoriaCompartida.h"

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
	 * establece el valor inicial de la caja, inicializando a su vez,
	 * la memoria compartida y el semaforo.
	 */
	void inicializar(int montoInicial);
	/**
	 * Suma al valor de la caja. Es bloqueante.
	 */
	void depositar(int monto);
	/**
	 * Devuelve el valor actual de la caja. Tambien es bloqueante.
	 * Si se interrumpe al proceso mientras esperaba en la caja,
	 * devuelve -1
	 */
	int consultar();
	void eliminarRecursos();
	virtual ~Caja();
private:
	Semaforo semaforo;
	MemoriaCompartida<int> memoria;
};

#endif /* CAJA_H_ */
