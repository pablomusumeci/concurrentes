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
#define TAG "Jefe de Estacion"
#define TAM_BUFFER 18
int calcularRandom();

int main() {

	Logger log;
	log.info(TAG, "Comienzo del proceso jefe de estacion");
	Properties properties;
	std::string archivo = properties.getProperty("process.commonFile");
	std::string archivoFifoGenJde = properties.getProperty("fifo.generador.jde");
	std::string archivoFifoJdeEmp = properties.getProperty("fifo.jde.empleado");
	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	FifoLectura canalGenJde(archivoFifoGenJde);
	FifoEscritura canalJdeEmp(archivoFifoJdeEmp);
	char buffer [ TAM_BUFFER ];
	memset(buffer, '\0', TAM_BUFFER);
	canalGenJde.abrir();
	canalJdeEmp.abrir();

	// Grupo de empleados
	Empleados empleados;

	while (sigint_handler.getGracefulQuit() == 0){
		ssize_t bytesLeidos = canalGenJde.leer ( static_cast <void*>( buffer ) , TAM_BUFFER );
		if(bytesLeidos > 0){
			std :: string mensaje = buffer;
			mensaje.resize(bytesLeidos);
			Auto automovil(mensaje);
			log.info(TAG, "Recibi: " + automovil.serializar());

			//TODO: Verificar si hay empleado libre, en caso de que exista:

			std::string mensajeEnviar = automovil.serializar();
			log.info(TAG, "Enviando auto: " + mensajeEnviar + " Largo: " + StringUtils::intToString(mensajeEnviar.length()));
			canalJdeEmp.escribir( static_cast < const void*>( mensajeEnviar.c_str() ) , mensajeEnviar.length());
		}
	}

	try{
		canalGenJde.cerrar();
		canalJdeEmp.cerrar();
	} catch (std::string& e){
		log.error(TAG,e);
	}

	log.info(TAG, "Fin de la lectura");
	exit(0);

}

int calcularRandom() {
	srand(time(NULL));
	int resultado = rand() % 100 + 1;
	return resultado;
}
