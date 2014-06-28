#include <iostream>
using namespace std;

#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <MemoriaCompartida.h>
#include <Logger/Logger.h>
#include <Properties/Properties.h>
#include <Seniales/SignalHandler.h>
#include <Seniales/SIGINT_Handler.h>
#include <StringUtils.h>
#include <Fifo/FifoLectura.h>
#include <Fifo/FifoEscritura.h>
#include <Modelo/Auto.h>
#include <Modelo/Empleados.h>
#include <Cola.h>

#define TAG "Jefe de Estacion"
#define TAM_BUFFER 31

int calcularRandom();

int main() {

	Logger log;
	log.info(TAG, "Comienzo del proceso jefe de estacion");
	Properties properties;
	std::string archivo = properties.getProperty("process.commonFile");
	std::string archivoFifoGenJde = properties.getProperty(
			"fifo.generador.jde");
	std::string archivoEmpleado = properties.getProperty("process.empleado");
	std::string archivoFifoJdeEmp = properties.getProperty("fifo.jde.empleado");
	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	FifoLectura canalGenJde(archivoFifoGenJde);
	FifoEscritura canalJdeEmp(archivoFifoJdeEmp);
	Cola<st_auto> cola(archivoEmpleado,'c');
	char buffer[ TAM_BUFFER];
	try {
		memset(buffer, '\0', TAM_BUFFER);
		canalGenJde.abrir();
		canalJdeEmp.abrir();

		// Grupo de empleados
		Empleados empleados;

		while (sigint_handler.getGracefulQuit() == 0) {
			st_auto autoRecibido;
			int resultado = cola.leer(-3, &autoRecibido);
			Auto automovil(autoRecibido);
			log.info(TAG, "Recibi: " + automovil.serializar());
			if(resultado > 0){
				if (empleados.hayEmpleadoLibre()) {

					std::string mensajeEnviar = automovil.serializar();
					//log.debug(TAG, "Enviando auto: " + mensajeEnviar);
					canalJdeEmp.escribir(
							static_cast<const void*>(mensajeEnviar.c_str()),
							mensajeEnviar.length());
				} else {
					// Rechazar el auto
					log.debug(TAG, "Se rechaza el auto con id "
							+ StringUtils::intToString(automovil.getID())
									+ " por falta de empleados libres");
				}
			}
		 }

		canalGenJde.cerrar();
		canalJdeEmp.cerrar();
		canalJdeEmp.eliminar();
		SignalHandler::getInstance()->destruir();
	} catch (char const* e) {
		log.error(TAG, e);
	} catch (std::string& e) {
		log.error(TAG, e);
	} catch (...) {
		log.error(TAG, "Error en apertura de canales");
	}

	log.info(TAG, "Fin de la lectura");
	return 0;

}

int calcularRandom() {
	srand(time(NULL));
	int resultado = rand() % 100 + 1;
	return resultado;
}
