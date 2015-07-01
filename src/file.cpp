#include "file.hpp"

File::File(const char * filePath, const char * option)
{
	// mSource = new fstream();
	// mTarget = new fstream();

	struct stat sb;
	stat(filePath, &sb);

	// Verify if the filePath passed is a regular file
	if(!S_ISREG(sb.st_mode))
	{
		char buf[256];
		std::snprintf(buf, sizeof buf, "Error: '%s'%s", filePath, " is not a regular file!");
		throw std::invalid_argument(buf);
	}

	mSource.open(filePath, ios::in | ios::binary);

	// Verify if the source file is open properly
	if(!mSource.is_open())
	{
		char buf[256];
		std::snprintf(buf, sizeof buf, "Error: Unable to open '%s'%s", filePath, " file!");
		throw std::invalid_argument(buf);
	}

	std::string filePathOutput(filePath);

	// Verify if the action is for Compression or for Extraction to create the target file
	if(strcmp(option, "C") == 0)
	{
		filePathOutput += ".ppmc";
		mTarget.open(filePathOutput.c_str(), std::ios::out | std::ios::binary);
	} else
	{
		mTarget.open(filePathOutput.substr(0, filePathOutput.find_last_of(".")).c_str(), std::ios::out | std::ios::binary);
	}

	// Verify if the target file is open properly
	if(!mTarget.is_open())
	{
		char buf[256];
		std::snprintf(buf, sizeof buf, "Error: Unable to open '%s'%s", filePathOutput.c_str(), " file!");
		throw std::invalid_argument(buf);
	}
}

File::~File(void){}

void File::encode(void)
{
	int k;
	PPMC *Tree;
	std::string str, ctx;
	// [ToDo] Getting file
	std::string word = "ABRACADABRA";
	int size_word;
	
	Tree = new PPMC(&ac);
	// [ToDo] Getting size from file
	Tree->setAlphabet_size(5);
	size_word = word.size();
	
	for (int i = 0; i < size_word; i++)
	{
		std::vector<double> *prob = new std::vector<double>;
		str = word.substr(i, 1);

		switch (i) 
		{
			case 0:
						ctx = "";
						k = 0;
			   		break;
			
			case 1:
						ctx = word.substr(0,1);
						k = 1;
						break;  
			
			default:
						ctx = word.substr(i-2,2);	 
						k = 2;
		}

		Tree->PPMC::getProb(Tree->getRoot(), str, ctx, 0, k, prob);
		Tree->PPMC::updateTree(str, ctx);		 
	}
}

void File::decode(void)
{
	// [ToDo]
}

void File::compress(void)
{
	std::clog << "# Compressing..." << std::endl;
	
	ac.SetFile(&mTarget);	
	encode();
	ac.EncodeFinish();

	mSource.close();
	mTarget.close();
}

void File::extract(void)
{
	std::clog << "# Extracting..." << std::endl;

	// ac.SetFile(mSource);
	// ac.DecodeStart();
	// See the Decode() method on ModelOrder0C.cc file 
	decode();

	mSource.close();
	mTarget.close();
}