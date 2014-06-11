/*
 * AutoFactory.h
 *
 *  Created on: 18/04/2014
 *      Author: pablon
 */

#ifndef AUTOFACTORY_H_
#define AUTOFACTORY_H_
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <Modelo/Auto.h>

class AutoFactory {
public:
	AutoFactory();
	Auto* generar();
	virtual ~AutoFactory();
private:
	int id;
	int generarRandom();
};

#endif /* AUTOFACTORY_H_ */
