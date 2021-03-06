# include "Semaforo.h"
#include "Properties/Properties.h"

Semaforo::Semaforo(std::string nombre , char caracter ) {
	this->valorInicial = valorInicial ;
	key_t clave = ftok ( nombre.c_str() , caracter ) ;
	this->id = semget ( clave ,1 ,0666 | IPC_CREAT ) ;
}

Semaforo::~Semaforo() {
}

int Semaforo::getProcesosEsperando(){
	return semctl ( this->id , 0 , GETVAL) ;
}

int Semaforo::inicializar (int valorInicial) {
	this->valorInicial = valorInicial;
	union semnum {
		int val ;
		struct semid_ds * buf ;
		ushort * array ;
	};
	semnum init ;
	init.val = this->valorInicial ;
	int resultado = semctl ( this->id , 0 , SETVAL , init ) ;
	return resultado ;
}

/**
 * Decrementa en 1 el valor del semaforo
 */
int Semaforo::p() {
	struct sembuf operacion ;
	operacion.sem_num = 0; // numero de semaforo
	operacion.sem_op = -1; // restar 1 al s e m a f o r o
	operacion.sem_flg = SEM_UNDO ;
	int resultado = semop ( this->id , &operacion ,1 ) ;
	return resultado ;
}

/**
 * Incrementa en uno el valor del semaforo
 */
int Semaforo::v() {
	struct sembuf operacion ;
	operacion.sem_num = 0; // numero de semaforo
	operacion.sem_op = 1; // sumar 1 al semaforo
	operacion.sem_flg = SEM_UNDO ;
	int resultado = semop ( this->id , &operacion ,1 ) ;
	return resultado ;
}

void Semaforo::eliminar() {
	semctl ( this->id , 0 , IPC_RMID ) ;
}

Semaforo::Semaforo(char caracter) {
	Properties properties;
	std::string nombre = properties.getProperty("process.commonFile");
	this->valorInicial = valorInicial ;
	key_t clave = ftok ( nombre.c_str() , caracter ) ;
	this->id = semget ( clave ,1 ,0666 | IPC_CREAT ) ;

}
