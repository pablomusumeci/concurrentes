#include "FifoEscritura.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "../Logger/Logger.h"

const std::string FifoEscritura::TAG  = "Fifo Escritura";

FifoEscritura::FifoEscritura(const std::string nombre) : Fifo(nombre) {

}

FifoEscritura::~FifoEscritura() {
}

void FifoEscritura::abrir() {
	Logger log;
	fd = open ( nombre.c_str(),O_WRONLY );
	if (fd == -1){
		printf ("PID : %d\n", getpid());
		printf ("Error no is : %d\n", errno);
        printf("Error description is : %s\n",strerror(errno));
        log.error(TAG, "Error abriendo Fifo de Escritura:" + std::string(strerror(errno)));
		throw("No se pudo abrir el fifo de escritura");
	}
}

ssize_t FifoEscritura::escribir(const void* buffer,const ssize_t buffsize) const {
	return write ( fd,buffer,buffsize );
}
