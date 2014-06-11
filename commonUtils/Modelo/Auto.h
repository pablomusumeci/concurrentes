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

typedef struct st_auto {
	long mtype;
	int id;
	int dinero;
} st_auto;
		
class Auto {
	public:
		Auto(int id, int saldo, long mtype);
		Auto(std::string cadena);
		Auto(const st_auto& structAuto);
		virtual ~Auto();
		std::string serializar();
		int getDinero();
		int getID();
		int getPrioridad();
		st_auto getStruct();
		void fromStruct(const st_auto& structAuto);

	private:
		int id, dinero;
		long mtype;


		void hidratar(std::string cadena);
};

#endif /* AUTO_H_ */
