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
#include <Cola.h>
#include <Modelo/Auto.h>
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

	std::vector<Proceso*> empleados;

	std::string archivo = "";
	std::string procesoJefeEstacion = "";
	std::string procesoGenerador = "";
	std::string procesoAdmin = "";
	std::string archivoSemaforo = "";
	std::string archivoEmpleado = "";
	std::string archivoSemaforoJdeEmp = "";

	// Lectura de Properties
	try{
		Properties properties;
		archivo = properties.getProperty("process.commonFile");
		procesoJefeEstacion = properties.getProperty("process.jefeEstacion");
		procesoGenerador = properties.getProperty("process.generadorAutos");
		procesoAdmin = properties.getProperty("process.administrador");
		archivoSemaforo = properties.getProperty("semaforo.surtidores");
		archivoEmpleado = properties.getProperty("process.empleado");
		archivoSemaforoJdeEmp = properties.getProperty("semaforo.jde.empleado");
	} catch (...){
		log.fatal(TAG, "Error leyendo las properties");
		return 1;
	}

	/* Descomentar para leer opciones por parametro */
	GetOpt options(argc,argv);
	options.parse();
	int CantSurtidores = options.getSurtidores();
	int CantEmpleados = options.getEmpleados();



	/**
	 * Variables compartidas entre los procesos.
	 */
	Empleados arrayEmpleados;
	Caja caja;
	Cola<st_auto> colaGeneradorJde(archivoEmpleado,'c');

	try{
		log.info(TAG, "Comienzo de ejecucion");

		log.info(TAG, "Levanto jefe de estacion");
		Proceso* JefeEstacion= new Proceso(procesoJefeEstacion);

		log.info(TAG, "Levanto generador de autos");
		Proceso* Generador = new Proceso(procesoGenerador);

		log.info(TAG, "Levanto administrador");
		Proceso* Admin = new Proceso(procesoAdmin);

		inicializarCajaYListaDeEmpleados(CantEmpleados, caja, arrayEmpleados);

		// Controla acceso de empleados a surtidores
		Semaforo semaforoSurtidor(archivoSemaforo,'s');
		semaforoSurtidor.inicializar(CantSurtidores);

		// Controla acceso de empleados al fifo con el JDE
		Semaforo semaforoJdeEmpleados(archivoSemaforoJdeEmp,'s');
		semaforoJdeEmpleados.inicializar(1);

		log.info(TAG, "Levanto empleados");
		for (int i = 0; i < CantEmpleados; i++){

			Proceso* empleado = new Proceso(archivoEmpleado);
			log.info(TAG, "Creo empleado numero: " + StringUtils::intToString(i) + " - PID: " +StringUtils::intToString(empleado->getId()));
			empleados.push_back(empleado);
		}
		/**
		 * Limpieza de los semaforos y MC de la caja y el contador de empleados
		 */
		std::cout << "Para terminar, ingresar un caracter: " ;
		getchar();

		for (std::vector<Proceso*>::iterator it = empleados.begin() ; it != empleados.end(); ++it){
			log.info(TAG, "Cerrando empleado ID: " + StringUtils::intToString((int)(*it)->getId()));
			(*it)->interrupt();
			delete *it;
		}
		Generador->interrupt();
		delete Generador;
		JefeEstacion->interrupt();
		delete JefeEstacion;
		Admin->interrupt();
		delete Admin;

		log.debug(TAG, "Cuenta del semaforo semaforoSurtidor " + StringUtils::intToString(semaforoSurtidor.getProcesosEsperando()));
		log.debug(TAG, "Cuenta del semaforo semaforoJdeEmpleados " + StringUtils::intToString(semaforoJdeEmpleados.getProcesosEsperando()));
		destruirCajaYListaDeEmpleados(caja, arrayEmpleados);
		semaforoSurtidor.eliminar();
		semaforoJdeEmpleados.eliminar();
		colaGeneradorJde.destruir();

	}catch(char const* e){
		log.error(TAG, e);
		std::cout << e << std::endl;
	}catch(std::string& e){
		log.error(TAG, e);
		std::cout << e << std::endl;
	}
}
