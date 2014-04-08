#ifndef LOCKFILE_H_
#define LOCKFILE_H_

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "../Logger/Logger.h"

class LockFile {

private:
	struct flock fl;
	int fd;
	std::string nombre;
	static const std::string TAG;

public:
	LockFile ( const std::string nombre );
	~LockFile();

	int tomarLock ();
	int liberarLock ();
	std::string getNombre();
};

#endif /* LOCKFILE_H_ */
