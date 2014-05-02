/*
 * main.cpp
 *
 *  Created on: 05/04/2014
 *      Author: javier
 */
#include <cstdio>
#include <Logger/Logger.h>
#include <Properties/Properties.h>
#include <StringUtils.h>
#include <Semaforo.h>
#include <Modelo/Auto.h>
#include <sys/types.h>
#include <unistd.h>
#include <Modelo/Caja.h>
#include <Fifo/FifoLectura.h>
#include <Seniales/SignalHandler.h>
#include <Seniales/SIGINT_Handler.h>
#define TAM_BUFFER 18

int depositarEnCaja(int monto){
	Caja caja;
	caja.depositar(monto);
	int montoNuevo = caja.consultar();
	return montoNuevo;
}

/**
 * Calcula el tiempo que el proceso empleado duerme
 * en base a la cantidad de dinero que tiene el auto
 * con el cual va a estar ocupado.
 */
int tiempoDeTrabajo(Auto& at){
	return (at.getDinero() % 10) + 2;
}

int main(int argc, char* argv[]){
	Logger log;
	Properties properties;
	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);
	std::string tag = "Empleado " + StringUtils::intToString(getpid());
	std::string archivoFifoJdeEmp = properties.getProperty("fifo.jde.empleado");
	std::string archivoSemaforoJdeEmp = properties.getProperty("semaforo.jde.empleado");
	std::string archivoSemaforoSurtidores = properties.getProperty("semaforo.surtidores");

	FifoLectura canalJdeEmp(archivoFifoJdeEmp);
	Semaforo semaforoFifoJdeEmp(archivoSemaforoJdeEmp, 's');
	Semaforo semaforoSurtidor(archivoSemaforoSurtidores, 's');
	char buffer [ TAM_BUFFER ];
	memset(buffer, '\0', TAM_BUFFER);
	canalJdeEmp.abrir();

	log.info(tag, "Comienzo del proceso empleado");
	while( sigint_handler.getGracefulQuit() == 0){
//		log.info(tag, "Libre");
		semaforoFifoJdeEmp.p();
//		log.info(tag, "Espera un auto en el fifo");
		ssize_t bytesLeidos = canalJdeEmp.leer ( static_cast <void*>( buffer ) , TAM_BUFFER);
		if(bytesLeidos >0){
			std :: string mensajeRecibido = buffer;
			mensajeRecibido.resize(bytesLeidos);
			Auto automovil(mensajeRecibido);
			int dineroAuto = automovil.getDinero();
			log.info(tag, "Recibi: " + automovil.serializar());
			int montoTotal = depositarEnCaja(dineroAuto);
			log.info(tag, "Deposito $" +  StringUtils::intToString(dineroAuto) + " - Saldo Nuevo $" + StringUtils::intToString(montoTotal));
		}
		semaforoFifoJdeEmp.v();
//		log.info(tag, "Libere semaforo ");
/*
		int tiempoTrabajo = tiempoDeTrabajo(automovil);
		log.info(tag, "Empleado espera por surtidor libre ");
		semaforoSurtidor.p();
		log.info(tag, "Empleado trabajando " + tiempoTrabajo);
		sleep(timeWorking);
		semaforoSurtidor.v();
		log.info(tag, "Empleado termino de trabajar, libera surtidor");*/
		//TODO: empleado deposita en la caja
		//int montoTotal = depositarEnCaja(dineroAuto);
		//log.info(tag, "Deposito $" +  StringUtils::intToString(dineroAuto) + " - Saldo Nuevo $" + StringUtils::intToString(montoTotal));
	}

	log.info(tag, "Proceso empleado finalizado");
	return 0;
}


