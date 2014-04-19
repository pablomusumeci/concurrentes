/*
 * Process.cpp
 *
 *  Created on: 18/04/2014
 *      Author: florencia
 */

#include "Process.h"


Process::Process(std::string fileName): file(fileName),id(0),status(0) {
	start();
}

Process::Process(const Process& process): file(process.file),id(0),status(0) {
	start();
}

void Process::start(){
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

bool Process::isRunning() {
	return kill(id, 0) == 0;
}

pid_t Process::getId(){
	if(!isRunning()) throw("process not running");
	return id;
}

int Process::getStatus(){
	if(!isRunning()) throw("process not running");
	return status;
}

void Process::waitProcess() {
	if (isRunning()) {
		if (waitpid(id, &status, 0) == -1) {
			throw("process error, could not wait for child process");
		}
	} else throw("process error, process not running");
}

void Process::killProcess() {
	if (!isRunning()) throw("process error, process not running");
	if (kill(id, SIGKILL) == -1) throw("process error, could not kill process");
	id = 0;
	status = -1;
}

Process::~Process() {
	waitProcess();
}
