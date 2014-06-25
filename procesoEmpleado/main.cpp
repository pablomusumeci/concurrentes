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
#include <Modelo/Empleados.h>
#include <Fifo/FifoLectura.h>
#include <Seniales/SignalHandler.h>
#include <Seniales/SIGINT_Handler.h>
#define TAM_BUFFER 30
/*
int depositarEnCaja(int monto){
	Caja caja;
	caja.depositar(monto);
	int montoNuevo = caja.consultar();
	return montoNuevo;
}*/

/**
 * Calcula el tiempo que el proceso empleado duerme
 * en base a la cantidad de dinero que tiene el auto
 * con el cual va a estar ocupado.
 */
int tiempoDeTrabajo(Auto& at, int base){
	return (at.getDinero() % base) + 1;
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
	std::string base = properties.getProperty("constante.tiempo.empleado");
	int tiempoBase = StringUtils::stringToInt(base);

	FifoLectura canalJdeEmp(archivoFifoJdeEmp);
	Semaforo semaforoFifoJdeEmp(archivoSemaforoJdeEmp, 's');
	Semaforo semaforoSurtidor(archivoSemaforoSurtidores, 's');
	Caja caja;
	char buffer [ TAM_BUFFER ];
	memset(buffer, '\0', TAM_BUFFER);
	canalJdeEmp.abrir();
	Empleados empleados;

	log.info(tag, "Comienzo del proceso empleado");
	while( sigint_handler.getGracefulQuit() == 0){
		int resultadoJde = semaforoFifoJdeEmp.p();
		if(resultadoJde != -1){
			ssize_t bytesLeidos = canalJdeEmp.leer ( static_cast <void*>( buffer ) , TAM_BUFFER);
			semaforoFifoJdeEmp.v();
			if(bytesLeidos > 0){
				// Se decrementa la cantidad de empleados libres
				empleados.tomarEmpleado();
				std :: string mensajeRecibido = buffer;
				mensajeRecibido.resize(bytesLeidos);
				Auto automovil(mensajeRecibido);

				log.debug(tag, "Recibi: " + automovil.serializar());
				int tiempoTrabajo = tiempoDeTrabajo(automovil, tiempoBase);

				// Espero al surtidor
				int resultado = semaforoSurtidor.p();
				if(resultado != -1){
					log.debug(tag, "Empleado trabajando " + StringUtils::intToString(tiempoTrabajo));
					int tiempoRestante = 0;
					tiempoRestante = sleep(tiempoTrabajo);
					sleep(tiempoRestante);
					semaforoSurtidor.v();
					// Deposito en la caja
					int dineroAuto = automovil.getDinero();
					//int montoTotal = depositarEnCaja(dineroAuto);
					int saldoNuevo = caja.depositar(dineroAuto, 2 ,tag);
					log.debug(tag, "Deposito $" +  StringUtils::intToString(dineroAuto) + " - Saldo Nuevo $" + StringUtils::intToString(saldoNuevo));
					// El empleado se vuelve a marcar como libre
					empleados.devolverEmpleado();
				} else {
					if (errno == EINTR)
						log.debug(tag, "Recibi señal mientras esperaba el surtidor.");
					else
						log.error(tag, "Error pidiendo surtidores. ERRNO:" + StringUtils::intToString(errno));
				}
			} else {
				if (errno == EINTR)
					log.debug(tag, "Recibi señal mientras esperaba el fifo.");
				else
					log.error(tag, "Error esperando auto. ERRNO:" + StringUtils::intToString(errno));
			}
		}
	}

	try{
		canalJdeEmp.cerrar();
		SignalHandler::getInstance()->destruir();
	} catch (...){
		log.error(tag, "Error cerrando fifo entre JDE y Empleado.");
	}

	log.info(tag, "Proceso empleado finalizado");
	return 0;
}


