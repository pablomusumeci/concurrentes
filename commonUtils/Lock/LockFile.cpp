#include "LockFile.h"

const std::string LockFile::TAG = "LockFile";

LockFile :: LockFile ( const std::string nombre ) {

	this->nombre = nombre;
	this->fl.l_type = F_WRLCK;
	this->fl.l_whence = SEEK_SET;
	this->fl.l_start = 0;
	this->fl.l_len = 0;
	this->fd = open ( this->nombre.c_str(),O_CREAT|O_WRONLY,0777 );
	if (this->fd == -1){
		string msj = "No se pudo abrir el archivo para armar el lock";
		Logger::instance().error(TAG, msj);
		throw(msj);
	}
}

int LockFile :: tomarLock () {
	this->fl.l_type = F_WRLCK;
	return fcntl ( this->fd,F_SETLKW,&(this->fl) );
}

int LockFile :: liberarLock () {
	this->fl.l_type = F_UNLCK;
	return fcntl ( this->fd,F_SETLK,&(this->fl) );
}

LockFile :: ~LockFile () {
	if (close ( this->fd ) == -1){
		string msj = "Error al cerrar el Lock";
		Logger::instance().error(TAG, msj);
	}
}

std::string LockFile :: getNombre(){
	return this->nombre;
}
