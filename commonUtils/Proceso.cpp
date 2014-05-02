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
		if(retValue == -1) throw("process error, could not replace process image");
	} else if(pid > 0) {
		id = pid;
	} else {
		throw("process error, could not fork child process");
	}
}

bool Proceso::isRunning() {
	return kill(id, 0) == 0;
}

pid_t Proceso::getId(){
	if(!isRunning()) throw("process not running");
	return id;
}

int Proceso::getStatus(){
	if(!isRunning()) throw("process not running");
	return status;
}

void Proceso::waitProcess() {
	if (isRunning()) {
		if (waitpid(id, &status, 0) == -1) {
			throw("process error, could not wait for child process");
		}
	} else {
		Logger log;
		log.error("Proceso", "process error, process not running, PID: "+ StringUtils::intToString(getpid()));
	}
}

void Proceso::killProcess() {
	if (!isRunning()) throw("process error, process not running");
	if (kill(id, SIGKILL) == -1) throw("process error, could not kill process");
	id = 0;
	status = -1;
}

void Proceso::interrupt() {
	if (!isRunning()) throw("process error, process not running");
	if (kill(id, SIGINT) == -1) throw("process error, could not interrupt process");
//	id = 0;
//	status = -1;
}

Proceso::~Proceso() {
	waitProcess();
}
