#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <Logger/Logger.h>
#include <StringUtils.h>
#include <Seniales/SignalHandler.h>
#include <Seniales/SIGINT_Handler.h>
#include <Properties/Properties.h>
#include <Modelo/Caja.h>

using namespace std;

#define TAG "Administrador"

int main() {
	Logger log;
	log.info(TAG, "Arranca proceso admin");
	Properties properties;
	std::string espera = properties.getProperty("constante.tiempo.admin");
	int tiempo = StringUtils::stringToInt(espera);
	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);
	Caja caja;
	while (sigint_handler.getGracefulQuit() == 0){
		int valor = caja.consultar();
		log.info(TAG, "Caja $"+ StringUtils::intToString(valor));
		sleep(tiempo);
	}
	SignalHandler::getInstance()->destruir();
	log.info(TAG, "Ejecucion finalizada");
	return 0;


}

