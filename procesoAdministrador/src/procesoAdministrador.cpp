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

	// Implementar

}

int calcularRandom() {
	srand(time(NULL));
	int resultado = rand() % 100 + 1;
	return resultado;
}

