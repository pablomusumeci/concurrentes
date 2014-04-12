/*
 * GetOpt.cpp
 *
 *  Created on: 11/04/2014
 *      Author: pablon
 */

#include "GetOpt.h"

GetOpt::GetOpt(int argc, char **argv):empleados(0),surtidores(0) {
	this->argc = argc;
	this->argv = argv;
}

int GetOpt::parse(){
	if (argc == 1) {
	      printUsage();
	      return 1;
	}

	const std::string op_cortas  = "he:s:";
	const struct option op_largas[] =
	  {
	      { "help",         0,  NULL,   'h'},
	      { "empleados",      1,  NULL,   'e'},
	      { "surtidores",       1,  NULL,   's'},
	      { NULL,           0,  NULL,   0  }
	  };

	int siguiente_opcion;

	  while (1)
	  {
	      /* Llamamos a la función getopt */
	      siguiente_opcion = getopt_long (argc, argv, op_cortas.c_str(), op_largas, NULL);

	      if (siguiente_opcion == -1)
	          break; /* No hay más opciones. Rompemos el bucle */

	      switch (siguiente_opcion)
	      {
	          case 'h' :
	        	  printUsage();
	              return 0;

	          case 'e':
	        	  empleados = StringUtils::stringToInt(optarg);
	        	  break;

	          case 's':
	        	  surtidores = StringUtils::stringToInt(optarg);
	        	  break;

	          case '?' : /* opción no valida */
	        	  printUsage();
	              return 1;

	          case -1 :
	              break;

	          default :
	              return 1;
		  }
	  }

	  return 0;
}

int GetOpt::getEmpleados(){
	return empleados;
}

int GetOpt::getSurtidores(){
	return surtidores;
}

const char* nombre_programa;

void GetOpt::printUsage()
{
   std::cout << "Uso: %s opciones [ argumentos ...]\n" << nombre_programa << std::endl;
   std::cout << "    -h  --help                  Enseña esta ayuda"  << std::endl;
   std::cout << "    -o  --output fichero        Escribe la salida al fichero\n"<< std::endl;
   std::cout <<      "    -v  --verbose               Imprime más información a la salida\n"<< std::endl;
}
