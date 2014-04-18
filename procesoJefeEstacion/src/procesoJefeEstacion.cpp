#include <iostream>
using namespace std;

#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <MemoriaCompartida.h>
#include <Logger/Logger.h>
#include <Properties/Properties.h>
#include <StringUtils.h>
#include <Fifo/FifoLectura.h>
#include <Modelo/Auto.h>
#define TAG "Jefe de Estacion"

int calcularRandom();

int main() {

	Logger log;
	log.info(TAG, "Comienzo del proceso jefe de estacion");
	Properties properties;
	std::string archivo = properties.getProperty("process.commonFile");
	std::string archivoFifo = properties.getProperty("fifo.generador.jde");
	FifoLectura canal(archivoFifo);
	char buffer [ 40 ];
	canal.abrir();
	ssize_t bytesLeidos = canal.leer ( static_cast <void*>( buffer ) , 40 );

	while (bytesLeidos != 0){
		std :: string mensaje = buffer;
		mensaje.resize(bytesLeidos);
		Auto automovil(mensaje);
		log.info(TAG, "Recibi: " + automovil.serializar());
	}

	canal.cerrar();
	log.info(TAG, "Fin de la lectura");
	exit(0);

}

int calcularRandom() {
	srand(time(NULL));
	int resultado = rand() % 100 + 1;
	return resultado;
}
