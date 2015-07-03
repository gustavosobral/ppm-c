#ifndef __FILE_H
#define __FILE_H

#include "entry.hpp"
#include "ppmc.hpp"
#include "arithmeticcoderc.hpp"

#include <map>				// 	std::map
#include <iostream>			//	std::clog
#include <fstream>			//	std::fstream
#include <string.h>			//	strcmp()
#include <stdexcept>		//	std::invalid_argument()
#include <sys/stat.h>		//	stat()
#include <sys/types.h>		//	struct stat
#include <time.h>

class File {
private:
	ArithmeticCoderC * ac;
	std::fstream mSource;
	std::fstream mTarget;

	int alphabetSize;
	std::string * entireFile;

	void Encode(void);
	void Decode(void);

	void LoadFile(void);
public:
	File(const char * filePath, const char * option);
	~File(void);

	std::string getEntireFile(void);

	void Compress();
	void Extract();
};

#endif