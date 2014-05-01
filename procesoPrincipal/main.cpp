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
#include <vector>
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

	std::vector<Proceso> empleados;

	std::string archivo = "";
	std::string procesoJefeEstacion = "";
	std::string procesoGenerador = "";
	std::string archivoSemaforo = "";
	std::string archivoEmpleado = "";

	// Lectura de Properties
	try{
		Properties properties;
		archivo = properties.getProperty("process.commonFile");
		procesoJefeEstacion = properties.getProperty("process.jefeEstacion");
		procesoGenerador = properties.getProperty("process.generadorAutos");
		archivoSemaforo = properties.getProperty("semaforo.surtidores");
		archivoEmpleado = properties.getProperty("process.empleado");
	} catch (...){
		log.fatal(TAG, "Error leyendo las properties");
		return 1;
	}

	/* Descomentar para leer opciones por parametro
	GetOpt options(argc,argv);
	options.parse();
	int CantSurtidores = options.getSurtidores();
	int CantEmpleados = options.getEmpleados();
	*/

	//TODO: Borrar para la entrega
	int CantSurtidores = 2;
	int CantEmpleados = 3;

	/**
	 * Variables compartidas entre los procesos.
	 */
	Empleados arrayEmpleados;
	Caja caja;

	try{
		log.info(TAG, "Comienzo de ejecucion");

		log.info(TAG, "Levanto jefe de estacion");
		Proceso JefeEstacion(procesoJefeEstacion);

		log.info(TAG, "Levanto generador de autos");
		Proceso Generador(procesoGenerador);

		/**
		 * Descomentar para usar la caja en los empleados
		 */
		inicializarCajaYListaDeEmpleados(CantEmpleados, caja, arrayEmpleados);

		Semaforo semaforoSurtidor(archivoSemaforo,'s');
		semaforoSurtidor.inicializar(CantSurtidores);

		log.info(TAG, "Levanto empleados");
		for (int i = 0; i < CantEmpleados; i++){
			Proceso empleado(archivoEmpleado);
			empleados.push_back(empleado);
		}
		/**
		 * Limpieza de los semaforos y MC de la caja y el vector de empleados
		 */
		std::cout << "Para terminar, ingresar un caracter: " ;
		getchar();

		for (std::vector<Proceso>::iterator it = empleados.begin() ; it != empleados.end(); ++it){
			log.info(TAG, "Cerrando empleado ID: " + it->getId());
			it->interrupt();
		}
		Generador.interrupt();
		JefeEstacion.interrupt();
		destruirCajaYListaDeEmpleados(caja, arrayEmpleados);
		semaforoSurtidor.eliminar();

	}catch(char* e){
		log.error(TAG, e);
		std::cout << e << std::endl;
	}catch(std::string& e){
		log.error(TAG, e);
		std::cout << e << std::endl;
	}
}
