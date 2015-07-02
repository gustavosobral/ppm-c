#include "file.hpp"

File::File(const char * filePath, const char * option)
{
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
	ac = new ArithmeticCoderC();
}

File::~File(void){}

void File::LoadFile(void)
{
	// Gets the file size
	mSource.seekg(0, std::ios::end);
	std::size_t size = mSource.tellg();
	mSource.seekg(0, std::ios::beg);

	// Reads all file
	std::vector<char> v (size/sizeof(char));
	mSource.read((char *) &v[0], size);

	// Count the alphabetSize
	std::map<char, int> frequencies;

	for(unsigned int i = 0 ; i < size; i++)
	{
		frequencies[v[i]] = 1;
	}
	alphabetSize = frequencies.size();

	// Converts std::vector<char> to std::string
	entireFile = new std::string(v.begin(), v.end());
}

std::string File::getEntireFile(void)
{
	return * entireFile;
}

void File::Encode(void)
{
	PPMC *Tree;
	std::string str, ctx;
	std::string word = getEntireFile();
	int size_word;
	
	Tree = new PPMC(ac);
	Tree->setAlphabetSize(alphabetSize);
	size_word = word.size();
	Entry *entry, original_entry;
	
	for (int i = 0; i < size_word; i++)
	{
		str = word.substr(i, 1);

		switch (i) 
		{
			case 0:		entry = new Entry(str, "");
			   			break;
			
			case 1:		entry = new Entry(str, word.substr(0,1));
						break;  
			
			default:	entry = new Entry(str, word.substr(i-2,2));	 

		}

		original_entry = *entry;
		Tree->PPMC::getProb(Tree->getRoot(), entry);
		Tree->PPMC::Update(original_entry);	 
	}
}

void File::Decode(void)
{
	// [ToDo]
}

void File::Compress(void)
{
	std::clog << "# Compressing..." << std::endl;
	
	LoadFile();
	ac->SetFile(&mTarget);	
	Encode();
	ac->EncodeFinish();

	mSource.close();
	mTarget.close();
}

void File::Extract(void)
{
	std::clog << "# Extracting..." << std::endl;

	LoadFile();
	ac->SetFile(&mSource);
	ac->DecodeStart();
	Decode();

	mSource.close();
	mTarget.close();
}