#include "Logger.h"
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include "../Lock/LockFile.h"

void Logger::warn(const string& tag, const string& msg) {
	if ((nivelDeLog & LOG_WARN) == 0)
		return;

	safeLog(tag, msg, LOG_WARN);
}

void Logger::error(const string& tag, const string& msg) {
	if ((nivelDeLog & LOG_ERROR) == 0)
		return;

	safeLog(tag, msg, LOG_ERROR);
}

void Logger::debug(const string& tag, const string& msg) {
	if (nivelDeLog != LOG_DEBUG)
		return;
	safeLog(tag, msg, LOG_DEBUG);
}

void Logger::info(const string& tag, const string& msg) {
	if ((nivelDeLog & LOG_INFO) == 0)
		return;

	safeLog(tag, msg, LOG_INFO);
}

void Logger::fatal(const string& tag, const string& msg) {
	if ((nivelDeLog & LOG_FATAL) == 0)
		return;
	safeLog(tag, msg, LOG_FATAL);
}

void Logger::safeLog(const string& tag, const string& msg, int level) {
	try {
		LockFile lockFile(logFileName);
		lockFile.tomarLock();
		log(tag, msg, level);
		lockFile.liberarLock();
	} catch (std::string &msj) {
		printf("%s\n", "Error fatal en la apertura del archivo de log.");
		throw msj;
	}
}

void Logger::log(const string& tag, const string& msg, int level) {

	struct tm *p_local_t;
	time_t t = time(NULL);
	p_local_t = localtime(&t);

	string sNivel("INFO");
	switch (level) {
	case LOG_FATAL:
		sNivel = "FATAL";
		break;
	case LOG_ERROR:
		sNivel = "ERROR";
		break;
	case LOG_WARN:
		sNivel = "WARN";
		break;
	case LOG_INFO:
		sNivel = "INFO";
		break;
	case LOG_DEBUG:
		sNivel = "DEBUG";
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
	else
		sep = "\t\t\t\t";

	//FORMATO: d-m-yyyy HH:mm:ss objeto mensaje
	archivoLog << getpid() << "\t" << p_local_t->tm_mday << "-"
			<< 1 + p_local_t->tm_mon << "-" << 1900 + p_local_t->tm_year << " "
			<< p_local_t->tm_hour << ":" << p_local_t->tm_min << ":"
			<< p_local_t->tm_sec << "\t" << sNivel << "\t" << tag << sep << msg
			<< endl;
}

void Logger::setLogLevel(int nivelLog) {
	nivelDeLog = nivelLog;
}

Logger::Logger() {
	nivelDeLog = NIVEL_GLOBAL;
	ifstream properties(APPLICATION_PROPERTIES);
	if (! properties.is_open()) {
		std::string msj = "No se pudo abrir el archivo de properties";
		throw(msj);
	}
	properties >> logFileName;
	properties.close();
	archivoLog.open(logFileName.c_str(),  std::ios::app);
}

Logger::~Logger() {
	archivoLog.close();
}
