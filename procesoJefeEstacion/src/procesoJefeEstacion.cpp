#include <iostream>
using namespace std;

#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <MemoriaCompartida.h>
#include <Logger/Logger.h>
#include <utils.h>

#define TAG "Jefe de Estacion"

int calcularRandom();

int main() {

	Logger log;
	log.info(TAG, "Comienzo del proceso jefe de estacion");
	std::string archivo = "datos.txt";
	try {
		MemoriaCompartida<int> *buffer = new MemoriaCompartida<int>(archivo, 'A');

		int resultado = buffer->leer();
		log.info(TAG, "Leo el numero " + intToString(resultado)
				+ " de la memoria compartida");
		log.info(TAG, "Fin del proceso" );
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
