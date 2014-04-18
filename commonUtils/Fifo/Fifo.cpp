#include "Fifo.h"
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

Fifo::Fifo(const std::string nombre) : nombre(nombre), fd(-1) {
	mknod ( static_cast<const char*>(nombre.c_str()),S_IFIFO|0666,0 );
}

Fifo::~Fifo() {
}

void Fifo::cerrar() {
	if (close ( fd ) == -1)
		throw("No se pudo cerrar el fifo");
	fd = -1;
}

void Fifo::eliminar() const {
	if (unlink ( nombre.c_str() ) == -1)
		throw("No se pudo borrar el fifo");
}
