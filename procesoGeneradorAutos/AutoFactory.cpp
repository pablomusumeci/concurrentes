/*
 * AutoFactory.cpp
 *
 *  Created on: 18/04/2014
 *      Author: pablon
 */

#include "AutoFactory.h"

AutoFactory::AutoFactory():id(1) {
	srand(time(NULL));
}

AutoFactory::~AutoFactory() {
	srand(time(NULL));
}

// probabilidad 20% de que sea VIP
Auto* AutoFactory::generar(){
	long mtype = NORMAL; // prioridad comun
	if (rand() % 5 < 2) mtype = VIP; // prioridad vip
	Auto* automovil = new Auto(this->id, this->generarRandom(), mtype);
	id++;
	return automovil;
}

int AutoFactory::generarRandom(){
	int resultado = rand() % 299 + 1;
	return resultado;
}
