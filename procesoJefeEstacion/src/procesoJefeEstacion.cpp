#include <iostream>
using namespace std;

#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include "MemoriaCompartida.h"
#include <Logger/Logger.h>
#include <utils.h>

#define TAG "Proceso Jefe de Estacion"

int calcularRandom();

int main() {

	Logger log;

	std::string archivo = "datos.txt";
	try {
		MemoriaCompartida<int> buffer(archivo, 'A');

		int resultado = buffer.leer();
		log.info(TAG, "Hijo: leo el numero " + intToString(resultado)
				+ " de la memoria compartida");
		log.info(TAG, "Hijo: fin del proceso" );
	} catch (std::string& mensaje) {
		log.error(TAG,  mensaje);
	}

	exit(0);

}

int calcularRandom() {
	srand(time(NULL));
	int resultado = rand() % 100 + 1;
	return resultado;
}
