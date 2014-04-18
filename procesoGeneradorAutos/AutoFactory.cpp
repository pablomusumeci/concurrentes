/*
 * AutoFactory.cpp
 *
 *  Created on: 18/04/2014
 *      Author: pablon
 */

#include "AutoFactory.h"

AutoFactory::AutoFactory():id(0) {
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
	int resultado = rand() % 100 + 1;
	return resultado;
}
