#include "Proceso.h"
#include "Logger/Logger.h"
#include <unistd.h>
#include <sys/types.h>
#include "StringUtils.h"

Proceso::Proceso(std::string fileName): file(fileName),id(0),status(0) {
	start();
}

Proceso::Proceso(const Proceso& process): file(process.file),id(0),status(0) {
	start();
}

void Proceso::start(){
	int pid = fork();
	if (pid == 0) {
		int retValue = execl(file.c_str(), file.c_str(), NULL);
		if(retValue == -1) throw("Error en el proceso. No se puede reemplazar la imagen del ejecutable.");
	} else if(pid > 0) {
		id = pid;
	} else {
		throw("Error en el proceso. No se puede forkear.");
	}
}

bool Proceso::isRunning() {
	return kill(id, 0) == 0;
}

pid_t Proceso::getId(){
	if(!isRunning()) throw("El proceso no esta en ejecucion.");
	return id;
}

int Proceso::getStatus(){
	if(!isRunning()) throw("El proceso no esta en ejecucion.");
	return status;
}

void Proceso::waitProcess() {
	if (isRunning()) {
		if (waitpid(id, &status, 0) == -1) {
			throw("Error en el proceso, no se puede esperar al proceso hijo.");
		}
	} else {
		Logger log;
		log.error("Proceso", "Error en el proceso. El proceso no se esta ejecutando. PID: "+ StringUtils::intToString(getpid()));
	}
}

void Proceso::killProcess() {
	if (!isRunning()) throw("Error en el proceso. El proceso no se esta ejecutando.");
	if (kill(id, SIGKILL) == -1) throw("Error en el proceso. No se puede matar al proceso.");
	id = 0;
	status = -1;
}

void Proceso::interrupt() {
	if (!isRunning()) throw("Error en el proceso. El proceso no se esta ejecutando.");
	if (kill(id, SIGINT) == -1) throw("Error en el proceso. No se puede interrumpir el proceso.");
}

Proceso::~Proceso() {
	waitProcess();
}
