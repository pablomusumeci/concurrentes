#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>

using namespace std;

#define NIVEL_GLOBAL LOG_DEBUG

#ifndef LOG_LEVEL
#define LOG_LEVEL

#define LOG_INFO 1
#define LOG_WARN 2
#define LOG_ERROR 4
#define LOG_FATAL 8
#define LOG_DEBUG 15

#endif /*LOG_LEVEL*/

#define APPLICATION_PROPERTIES "application.properties"

class Logger {

private:
	ofstream archivoLog;
	// nivel de log con el que logeamos. Por defecto, DEBUG.
	int nivelDeLog;
	void log(const string& tag, const string& msg, int level);
	std::string logFileName;

	void safeLog(const string& tag, const string& msg, int level);
public:
	Logger();
	~Logger();
	void fatal(const string&, const string&);
	void error(const string&, const string&);
	void warn(const string&, const string&);
	void debug(const string&, const string&);
	void info(const string&, const string&);

	void setLogLevel(int);
};

#endif /* LOGGER_H_ */
