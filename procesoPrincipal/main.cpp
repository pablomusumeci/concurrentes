/*
 * main.cpp
 *
 *  Created on: 12/04/2014
 *      Author: javier
 */

#include <Logger/Logger.h>
#include <Properties/Properties.h>
#include <MemoriaCompartida.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <Modelo/Auto.h>
#define TAG "Proceso principal"

int main(int argc, char* argv[]) {
	Logger log;
	log.info(TAG, "Comienzo de ejecucion");

	// Crear un segmento de memoria compartida:

	Properties properties;
	std::string archivo = properties.getProperty("process.commonFile");
	/*MemoriaCompartida<int> memoria;
	try {
		memoria.crear(archivo, 'A');

		// escribe un dato para el hijo
		int random = 5;
		log.info(TAG, "Escribo el numero 5 en la memoria compartida");
		memoria.escribir(random);
	} catch (std::string &e) {
		log.error(TAG, "Error en memoria compartida.");
		exit(1);
	}

	log.info(TAG, "Se creo la memoria compartida.");*/

	// Usar la clase Proceso para forkear el proceso generador de autos

	// Usar la clase Proceso para forkear el proceso jefe de estacion
	pid_t procIdJefeEstacion = fork();
	if (procIdJefeEstacion == 0) {
		log.info(TAG, "Levanto jefe de estacion");
		std::string procesoJefeEstacion = properties.getProperty(
				"process.jefeEstacion");
		execl(procesoJefeEstacion.c_str(), "procesoJefeEstacion", NULL);
	} else {
		// Usar la clase Proceso para forkear los procesos empleados
		pid_t procGenerador = fork();
			if (procGenerador == 0) {
				log.info(TAG, "Levanto generador");
				std::string procesoGenerador = properties.getProperty(
						"process.generadorAutos");
				execl(procesoGenerador.c_str(), "procesoGeneradorAutos", NULL);
		// Esperar por entrada estandar para finalizar
		/*printf("Para finalizar la ejecucion ingrese el caracter q.\n");
		char c;
		while ((c = getchar()) != 'q') {
			printf("Para finalizar la ejecucion ingrese el caracter q.\n");
		}

		// Esperar a todos los procesos
		int statusJefeStacion;
		waitpid(procIdJefeEstacion, &statusJefeStacion, 0);

		// No es necesario liberar la memoria porque eso se hace en el destructor.
//		memoria.liberar();

		log.info(TAG, "Fin de ejecucion");*/
		return 0;
		}
	}
}
