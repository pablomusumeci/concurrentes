/*
 * Process.h
 *
 *  Created on: 18/04/2014
 *      Author: florencia
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;

class Process {
public:
	Process(std::string fileName);
	Process(const Process& process);
	pid_t getId();
	int getStatus();
	bool isRunning();
	void waitProcess();
	void killProcess();
	virtual ~Process();

private:
	pid_t id;
	std::string file;
	int status;
	void start();
};



#endif /* PROCESS_H_ */
