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
#include <Semaforo.h>
#include <GetOpt.h>
#include <Proceso.h>
#include <Modelo/Caja.h>
#include <Modelo/Empleados.h>

#define TAG "Proceso principal"

void inicializarCajaYListaDeEmpleados(int cantEmpleados, Caja& caja, Empleados& empleados){
	// Monto incial de la caja = 0
	caja.inicializar(0);
	empleados.inicializar(cantEmpleados);
}

void destruirCajaYListaDeEmpleados(Caja& caja, Empleados& empleados){
	caja.eliminarRecursos();
	empleados.eliminarRecursos();
}

int main(int argc, char* argv[]) {

	Logger log;
	Properties properties;

	// Lectura de Properties
	std::string archivo = properties.getProperty("process.commonFile");
	std::string procesoJefeEstacion = properties.getProperty("process.jefeEstacion");
	std::string procesoGenerador = properties.getProperty("process.generadorAutos");
	std::string archivoSemaforo = properties.getProperty("semaforo.surtidores");
	std::string archivoEmpleado = properties.getProperty("process.empleado");


	/* Descomentar para leer opciones por parametro
	GetOpt options(argc,argv);
	options.parse();
	int surtidores = options.getSurtidores();
	int surtidores = options.getSurtidores();
	*/

	//TODO: Borrar para la entrega
	int surtidores = 2;
	int empleados = 3;

	/**
	 * Variables compartidas entre los procesos.
	 */
	Empleados arrayEmpleados;
	Caja caja;

	try{
		log.info(TAG, "Comienzo de ejecucion");

		/* JDE
		log.info(TAG, "Levanto jefe de estacion");
		Proceso JefeEstacion(procesoJefeEstacion);
		*/

		/* Generador
		log.info(TAG, "Levanto generador de autos");
		Proceso Generador(procesoGenerador);
		*/

		/**
		 * Descomentar para usar la caja en los empleados
		 */
		inicializarCajaYListaDeEmpleados(empleados, caja, arrayEmpleados);

		Semaforo semaforoSurtidor(archivoSemaforo,'s');
		semaforoSurtidor.inicializar(surtidores);

		log.info(TAG, "Levanto empleados");
		for (int i = 0; i < empleados; i++){
			Proceso empleado(archivoEmpleado);
		}
		/**
		 * Limpieza de los semaforos y MC de la caja y el vector de empleados
		 */
		std::cout << "Para terminar, ingresar un caracter: " ;
		getchar();
		destruirCajaYListaDeEmpleados(caja, arrayEmpleados);
		semaforoSurtidor.eliminar();

	}catch(char* e){
		log.error(TAG, e);
		std::cout << e << std::endl;
	}
}
