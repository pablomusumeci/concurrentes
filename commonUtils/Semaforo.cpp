/*
 * Semaforo.cpp
 *
 *  Created on: 17/04/2014
 *      Author: javier
 */

#include "Semaforo.h"
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>

Semaforo::Semaforo(const std::string& archivo, const char letra) {
	key = ftok(archivo.c_str(), letra);
	semid = semget(key, 1, IPC_CREAT);

	if (semid < 0){
		throw "Error en la creacion del semaforo";
	}

	wait.sem_num = 0;
	wait.sem_op = -1;
	wait.sem_flg = SEM_UNDO;

	signal.sem_num = 0;
	signal.sem_op = 1;
	signal.sem_flg = SEM_UNDO;
}

void Semaforo::setValor(int semval) {
	semctl(semid, 0, SETVAL, semval);
}

int Semaforo::getValor() {
	return semctl(semid, 0, GETVAL);
}

void Semaforo::tomar() {
	semop(semid, &wait, 1);
}

void Semaforo::liberar() {
	semop(semid, &signal, 1);
}

void Semaforo::destruir() {
	semctl(semid, 0, IPC_RMID);
}

Semaforo::~Semaforo() {

}

