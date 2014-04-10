#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include "MemoriaCompartida.h"
#include <Logger/Logger.h>
#include <utils.h>

using namespace std;

#define TAG "Proceso Administrador"

int calcularRandom();

int main() {

	pid_t procId = fork();

	Logger log;

	if (procId == 0) {
		sleep(5);
		// Llamo al jefe de estacion
		// Esto veamos como estandarizarlo...
		execl("../procesoJefeEstacion/Debug/procesoJefeEstacion", "");

	} else {

		std::string archivo = "datos.txt";
		MemoriaCompartida<int> memoria;
		try {
			memoria.crear(archivo, 'A');

			// escribe un dato para el hijo
			int random = calcularRandom();
			log.info(TAG, "Padre: escribo el numero " + intToString(random)
							+ " en la memoria compartida");
			memoria.escribir(random);

			// espera a que termine el hijo
			wait( NULL);
			// libera la memoria
			memoria.liberar();
		} catch (std::string &e) {
			log.error(TAG, "Padre: error en memoria compartida." );
		}

		log.info(TAG, "Padre: fin del proceso");
		exit(0);

	}

}

int calcularRandom() {
	srand(time(NULL));
	int resultado = rand() % 100 + 1;
	return resultado;
}

