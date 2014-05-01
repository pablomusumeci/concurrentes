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
#include <Modelo/Auto.h>
#define TAG "Jefe de Estacion"
#define TAM_BUFFER 18
int calcularRandom();

int main() {

	Logger log;
	log.info(TAG, "Comienzo del proceso jefe de estacion");
	Properties properties;
	std::string archivo = properties.getProperty("process.commonFile");
	std::string archivoFifo = properties.getProperty("fifo.generador.jde");
	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	FifoLectura canal(archivoFifo);
	char buffer [ TAM_BUFFER ];
	memset(buffer, '\0', TAM_BUFFER);
	canal.abrir();
	while (sigint_handler.getGracefulQuit() == 0){
		ssize_t bytesLeidos = canal.leer ( static_cast <void*>( buffer ) , TAM_BUFFER );
		std :: string mensaje = buffer;
		mensaje.resize(bytesLeidos);
		Auto automovil(mensaje);
		log.info(TAG, "Recibi: " + automovil.serializar());
	}

	try{
		canal.cerrar();
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
