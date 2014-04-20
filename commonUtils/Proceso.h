/*
 * Process.h
 *
 *  Created on: 18/04/2014
 *      Author: florencia
 */

#ifndef PROCESO_H_
#define PROCESO_H_

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;

class Proceso {
public:
	Proceso(std::string fileName);
	Proceso(const Proceso& process);
	pid_t getId();
	int getStatus();
	bool isRunning();
	void waitProcess();
	void killProcess();
	virtual ~Proceso();

private:
	pid_t id;
	std::string file;
	int status;
	void start();
};



#endif /* PROCESO_H_ */
