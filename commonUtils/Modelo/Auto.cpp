/*
 * Auto.cpp
 *
 *  Created on: 18/04/2014
 *      Author: pablon
 */

#include "Auto.h"

Auto::Auto(int id, int dinero, long mtype) {
	this->id = id;
	this->dinero = dinero;
	this->mtype = mtype;
}

Auto::Auto(const st_auto& structAuto){
	fromStruct(structAuto);
}

Auto::Auto(std::string cadena){
	hidratar(cadena);
}

Auto::~Auto() {
}

std::string Auto::serializar(){
	std::string resultado = "";
	resultado += "ID:";
	resultado += StringUtils::intToFixedString(this->id, 3);
	resultado += SEPARADOR;
	resultado += "Dinero:";
	resultado += StringUtils::intToFixedString(this->dinero, 4);
	resultado += SEPARADOR;
	resultado += "Prioridad:";
	resultado += StringUtils::intToFixedString(this->mtype,1);
	return resultado;
}

void Auto::hidratar(std::string cadena){
	try {
		std::vector<std::string> partes = StringUtils::split(cadena, SEPARADOR);
		std::vector<std::string> idString = StringUtils::split(partes[0], ':');
		std::vector<std::string> dineroString = StringUtils::split(partes[1], ':');

		this->id = StringUtils::stringToInt(idString[1]);
		this->dinero = StringUtils::stringToInt(dineroString[1]);
	} catch (...){
		Logger log;
		log.error("Auto", "Parsing exception - Mensaje recibido: " + cadena);
		this->id = 0;
		this->dinero = 0;
	}
}

int Auto::getDinero(){
	return this->dinero;
}

int Auto::getID(){
	return this->id;
}

int Auto::getPrioridad(){
	return this->mtype;
}

st_auto Auto::getStruct(){
	st_auto  newAuto;
	newAuto.id = this->id;
	newAuto.dinero = this->dinero;
	newAuto.mtype = this->mtype;
	return newAuto;
}

void Auto::fromStruct(const st_auto& receivedAuto){
	this->id = receivedAuto.id;
	this->dinero = receivedAuto.dinero;
	this->mtype = receivedAuto.mtype;
}
