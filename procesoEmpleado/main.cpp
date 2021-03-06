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
#define TAM_BUFFER 31
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
	std::string archivoEmpleado = properties.getProperty("process.empleado");
	std::string base = properties.getProperty("constante.tiempo.empleado");
	int tiempoBase = StringUtils::stringToInt(base);

	FifoLectura canalJdeEmp(archivoFifoJdeEmp);
	Semaforo semaforoFifoJdeEmp(archivoSemaforoJdeEmp, 's');
	Caja caja;
	char buffer [ TAM_BUFFER ];
	memset(buffer, '\0', TAM_BUFFER * sizeof(char));
	canalJdeEmp.abrir();
	Empleados empleados;
	Cola<st_surtidor> colaSurtidores(archivoEmpleado,'f');
	int saldoNuevo = 0;
	log.info(tag, "Comienzo del proceso empleado");
	while( sigint_handler.getGracefulQuit() == 0 and saldoNuevo >= 0){
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
				int resultado = 0;
				st_surtidor surtidor;
				resultado = colaSurtidores.leer(1, &surtidor);
				if(resultado > 0){
					log.debug(tag, "Empleado trabajando " + StringUtils::intToString(tiempoTrabajo) + " - Surtidor: " + StringUtils::intToString(surtidor.id));
					int tiempoRestante = 0;
					tiempoRestante = sleep(tiempoTrabajo);
					sleep(tiempoRestante);
					log.debug(tag, "Devolviendo Surtidor: " + StringUtils::intToString(surtidor.id));
					colaSurtidores.escribir(surtidor);
					// Deposito en la caja
					int dineroAuto = automovil.getDinero();
					// Recibo el saldo nuevo
					saldoNuevo = caja.depositar(dineroAuto, 2 ,tag);

					if (saldoNuevo == -1){
						log.debug(tag, "No se pudo acceder a la caja debido a que esta fue removida");
					} else {
						log.debug(tag, "Deposito $" +  StringUtils::intToString(dineroAuto) + " - Saldo Nuevo $" + StringUtils::intToString(saldoNuevo));
					}
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
					log.debug(tag, "Recibi señal mientras esperaba en el semaforo para acceder al FIFO.");
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


