#ifndef __FILE_H
#define __FILE_H

#include "ppmc.hpp"
#include "arithmeticcoderc.hpp"

#include <iostream>		//	std::clog
#include <fstream>		//	std::fstream
#include <string.h>		//	strcmp()

class File {
private:
	ArithmeticCoderC ac;
	std::fstream *mSource;
	std::fstream *mTarget;

public:
	File(const char * filePath, const char * option);
	~File(void);

	void compress();
	void extract();
};

#endif