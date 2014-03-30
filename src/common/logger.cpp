#include "logger.h"
#include <sstream>
ofstream logger::archivoLog;
int logger::nivelDeLog = NIVEL_GLOBAL;

void logger::warn(const string& tag, const string& msg){
	if ((logger::nivelDeLog & LOG_WARN) == 0)
		return;

	log(tag, msg, LOG_WARN);
}

void logger::error(const string& tag, const string& msg) {
	if ((logger::nivelDeLog & LOG_ERROR) == 0)
		return;

	log(tag, msg, LOG_ERROR);
}

void logger::debug(const string& tag, const string& msg) {
	if (logger::nivelDeLog != LOG_DEBUG)
		return;
	log(tag, msg, LOG_DEBUG);
}

void logger::info(const string& tag, const string& msg) {
	if ((logger::nivelDeLog & LOG_INFO) == 0)
		return;

	log(tag, msg, LOG_INFO);
}


void logger::fatal(const string& tag, const string& msg) {
	if ((logger::nivelDeLog & LOG_FATAL) == 0)
		return;
	log(tag, msg, LOG_FATAL);
}

void logger::log(const string& tag, const string& msg, int level) {
	static int i = 0;
	struct tm *p_local_t;
	time_t t = time(NULL);
	p_local_t = localtime(&t);
	stringstream out;

	out << 	"[" << p_local_t->tm_mday << "-" << 1 + p_local_t->tm_mon
			<< "-" << 1900 + p_local_t->tm_year << " "
			<< p_local_t->tm_hour << ":" << p_local_t->tm_min
			<< ":" << p_local_t->tm_sec << "]" ;

	string timeStamp = "log " + out.str() + ".txt";
	if (i == 0){
		logger::archivoLog.open( timeStamp.c_str() );
		archivoLog << "  Fecha y  hora\t\t" << " Tipo\t\t" << "Lugar del mensaje\t\t\t" << "Mensaje" << endl ;
		i++;
	}

	string sNivel("[INFO]\t");
	switch (level) {
	case LOG_FATAL:
		sNivel = "[FATAL]\t";
		break;
	case LOG_ERROR:
		sNivel = "[ERROR]\t";
		break;
	case LOG_WARN:
		sNivel = "[WARN]\t";
		break;
	case LOG_INFO:
		sNivel = "[INFO]\t";
		break;
	case LOG_DEBUG:
		sNivel = "[DEBUG]\t";
		break;
	default:
		break;
	}

	string sep;
	if (tag.size() >= 16)
		sep = "\t";
	else if (tag.size() >= 12)
		sep = "\t\t";
	else if (tag.size() >= 8)
		sep = "\t\t\t";
	else sep = "\t\t\t\t";

	//FORMATO: d-m-yyyy HH:mm:ss objeto mensaje
	archivoLog << "[" << p_local_t->tm_mday << "-" << 1 + p_local_t->tm_mon
			<< "-" << 1900 + p_local_t->tm_year << " "
			<< p_local_t->tm_hour << ":" << p_local_t->tm_min
			<< ":" << p_local_t->tm_sec << "]" << "\t" << sNivel << "\t" << tag << sep << msg
			<< endl;
}

void logger::setLogLevel(int nivelLog){
	logger::nivelDeLog = nivelLog;
}
