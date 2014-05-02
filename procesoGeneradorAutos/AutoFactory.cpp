/*
 * AutoFactory.cpp
 *
 *  Created on: 18/04/2014
 *      Author: pablon
 */

#include "AutoFactory.h"

AutoFactory::AutoFactory():id(1) {
}

AutoFactory::~AutoFactory() {
}

Auto* AutoFactory::generar(){
	Auto* automovil = new Auto(this->id, this->generarRandom());
	id++;
	return automovil;
}

int AutoFactory::generarRandom(){
	srand(time(NULL));
	int resultado = rand() % 299 + 1;
	return resultado;
}
