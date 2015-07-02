#include "file.hpp"

#include <unistd.h>		//	getopt()
#include <stdlib.h>		//	exit()
#include <iostream>		//	std::clog
#include <exception>	//	std::exception

const char * __progname = "ppm";
const char * __version = "0.1";
const char * __authors = "Gustavo Sobral and Francielly Cardoso";

static void usage(void)
{
	std::clog << std::endl;
	std::clog << "PPM-C version " << __version << std::endl;
	std::clog << "Copyright (C) 2015 " << __authors << std::endl;
	std::clog << std::endl;
	std::clog << "Usage: 	" << __progname << " <command> <file>" << std::endl;
	std::clog << std::endl;
	std::clog << "<Commands>" << std::endl;
	std::clog << " -c 		Compress file" << std::endl;
	std::clog << " -e 		Extract file" << std::endl;
	std::clog << " -h 		Show this help message" << std::endl;
}

int main(int argc, char * argv[], char * envp[])
{

	int i;
	int cflag = 0;
	int eflag = 0;

	while((i = getopt(argc, argv, "c:e:h")) != -1) {
		switch(i) {
			case 'c':
				cflag = 1;
				break;

			case 'e':
				eflag = 1;
				break;

			default:
				usage();
				exit(1);
		}
	}

	if(cflag ^ eflag) {

		try
		{
			if(cflag)
			{
				// Do compression
				File * f = new File(argv[2], "C");
				f->Compress();
			} else {
				// Do extraction
				File * f = new File(argv[2], "E");
				f->Extract();
			}
		} catch(std::exception &e)
		{
			std::clog << e.what() << std::endl;
		}
	} else {
		usage();
		exit(1);
	}

	exit(0);
}