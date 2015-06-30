#include "file.hpp"

File::File(const char * filePath, const char * option)
{
	if(strcmp(option, "C") == 0)
	{
		std::clog << "Compression" << std::endl;
	} else
	{
		std::clog << "Extraction" << std::endl;
	}
}

File::~File(void){}

void File::compress(void)
{
	//	ac.SetFile( mTarget );
	//	Encode();
	//	ac.EncodeFinish();

	std::clog << "Compress" << std::endl;
}

void File::extract(void)
{
	//	ac.SetFile( mSource );
	//	ac.DecodeStart();
	//	Decode();

	std::clog << "Extract" << std::endl;
}