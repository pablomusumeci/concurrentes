/*
 * Auto.h
 *
 *  Created on: 18/04/2014
 *      Author: pablon
 */

#ifndef AUTO_H_
#define AUTO_H_
#include "../StringUtils.h"
#include "../Logger/Logger.h"
#define SEPARADOR ';'

class Auto {
	public:
		Auto(int id, int saldo);
		Auto(std::string cadena);
		virtual ~Auto();
		std::string serializar();
		int getDinero();
		int getID();

	private:
		int id, dinero;
		void hidratar(std::string cadena);
};

#endif /* AUTO_H_ */
