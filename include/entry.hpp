#ifndef __ENTRY_H
#define __ENTRY_H

#include "node.hpp"
#include "arithmeticcoderc.hpp"

#include <map>			// std::map
#include <string>		// std::string
#include <vector>		// std::vector
#include <iostream>
#include <algorithm>	// std::sort()

class Entry {
private:
	std::string symbol;
	std::string context;
	int level;
	std::vector<std::string> * del_symb;
	std::vector<double> * prob;
	bool code_ESC;
	
public:
	Entry(void);
	~Entry(void);
	Entry(std::string symb, std::string ctx);

	std::string getSymbol(void);
	void setSymbol(std::string s);

	std::string getContext(void);
	void setContext(std::string s);

	int getLevel(void);

	std::vector<std::string> * getDelSymb(void);
	void setDelSymb(std::vector<std::string> * v);

	std::vector<double> * getProb(void);
	void setProb(std::vector<double> * v);

	bool getCodeESC(void);
	void setCodeESC(bool b);

	void ResetLevel(void);
	std::string NextChild(void);
	int Encode(int alphabet_size, ArithmeticCoderC * mAc);
	void Encode(Node * cnode, ArithmeticCoderC * mAc);
	
};

#endif