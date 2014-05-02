# ifndef SEMAFORO_H_
# define SEMAFORO_H_
# include <sys/ipc.h>
# include <sys/sem.h>
# include <sys/types.h>
#include <iostream>
#include <stdio.h>
#include <string.h>


class Semaforo {
	private :
		int id ;
		int valorInicial ;

	public :
		Semaforo (std::string nombre , char caracter ) ;
		Semaforo (char caracter ) ;
		int inicializar (int valorInicial);
		virtual ~ Semaforo () ;
		int p () ; // decrementa
		int v () ; //incrementa
		int getProcesosEsperando();
		void eliminar () ;

};
# endif /*SEMAFORO_H_*/
