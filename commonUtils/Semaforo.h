/*
 * Semaforo.h
 *
 *  Created on: 17/04/2014
 *      Author: javier
 */

#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include <string>
#include<sys/sem.h>

class Semaforo {
public:
	Semaforo(const std::string& archivo, const char letra);
	void setValor(int semval);
	int getValor();
	void tomar();
	void liberar();
	void destruir();
	virtual ~Semaforo();
private:
	key_t key;
	int semid;
	struct sembuf wait;
	struct sembuf signal;
};

#endif /* SEMAFORO_H_ */
