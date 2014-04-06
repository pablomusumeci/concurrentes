#include <iostream>
using namespace std;

#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include "MemoriaCompartida.h"

int calcularRandom();

int main() {

	std::string archivo = "datos.txt";
	try {
		MemoriaCompartida<int> buffer(archivo, 'A');

		int resultado = buffer.leer();
		std::cout << "Hijo: leo el numero " << resultado
				<< " de la memoria compartida" << std::endl;
		std::cout << "Hijo: fin del proceso" << std::endl;
	} catch (std::string& mensaje) {
		std::cerr << mensaje << std::endl;
	}

	exit(0);

}

int calcularRandom() {
	srand(time(NULL));
	int resultado = rand() % 100 + 1;
	return resultado;
}
