/*
 * GetOpt.h
 *
 *  Created on: 11/04/2014
 *      Author: pablon
 */

#ifndef GETOPT_H_
#define GETOPT_H_
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <iostream>
#include "StringUtils.h"

class GetOpt {
public:
	GetOpt(int argc, char **argv);
	void printUsage();
	int getSurtidores();
	int getEmpleados();
	int parse();
private:
	int empleados, surtidores;
	int argc;
	char** argv;
};

#endif /* GETOPT_H_ */
