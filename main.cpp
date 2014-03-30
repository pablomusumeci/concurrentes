/*
 * main.cpp
 *
 *  Created on: 29/03/2014
 *      Author: javier
 */


#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include "src/MemoriaCompartida.h"

int calcularRandom ();

int main () {

	std::string archivo = "main.cpp";
	pid_t procId = fork ();

	if ( procId == 0 ) {
		// codigo del hijo
		try {
			MemoriaCompartida<int> buffer ( archivo,'A' );

			std::cout << "Hijo: duermo 5 segundos..." << std::endl;
			sleep ( 5 );

			int resultado = buffer.leer ();
			std::cout << "Hijo: leo el numero " << resultado << " de la memoria compartida" << std::endl;
			std::cout << "Hijo: fin del proceso" << std::endl;
		} catch ( std::string& mensaje ) {
			std::cerr << mensaje << std::endl;
		}

		exit(0);
	} else {
		// codigo del padre
		try {
			MemoriaCompartida<int> buffer ( archivo,'A' );

			int random = calcularRandom ();
			std::cout << "Padre: escribo el numero " << random << " en la memoria compartida" << std::endl;
			buffer.escribir(random);

			// espera a que termine el hijo
			std::cout << "Padre: esperando a que termine el hijo" << std::endl;
			wait(NULL);

		} catch ( std::string& mensaje ) {
			std::cerr << mensaje << std::endl;
		}

		exit(0);
	}

}

int calcularRandom () {
	srand ( time(NULL) );
	int resultado = rand() % 100 + 1;
	return resultado;
}



