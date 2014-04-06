#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include "MemoriaCompartida.h"

using namespace std;

int calcularRandom();

int main() {

	pid_t procId = fork();

	if (procId == 0) {
		sleep(5);
		// Llamo aljefe de estacion
		execl("../procesoJefeEstacion/Debug/procesoJefeEstacion", "");

	} else {

		std::string archivo = "datos.txt";
		MemoriaCompartida<int> memoria;
		try {
			memoria.crear(archivo, 'A');

			// escribe un dato para el hijo
			int random = calcularRandom();
			cout << "Padre: escribo el numero " << random
					<< " en la memoria compartida" << endl;
			memoria.escribir(random);

			// espera a que termine el hijo
			wait( NULL);
			// libera la memoria
			memoria.liberar();
		} catch (std::string &e) {
			cout << "Padre: error en memoria compartida: " << endl;
		}

		cout << "Padre: fin del proceso" << endl;
		exit(0);

	}

}

int calcularRandom() {
	srand(time(NULL));
	int resultado = rand() % 100 + 1;
	return resultado;
}

