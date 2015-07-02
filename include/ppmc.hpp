#ifndef __PPMC_H
#define __PPMC_H

#include "entry.hpp"
#include "node.hpp"
#include "arithmeticcoderc.hpp"

#include <map>			// std::map
#include <string>		// std::string
#include <cmath>		// std::string
#include <vector>		// std::vector

class PPMC {
private:
	Node * root;
	int alphabet_size;
	std::map<char,bool> char_map;
	ArithmeticCoderC * mAc;

public:
	PPMC(void);
	PPMC(ArithmeticCoderC * ac);
	~PPMC(void);
	Node * getRoot(void);
	int getAlphabetSize(void);
	void setAlphabetSize(int);

	void SymbolIsNotChild(Node * cnode, Entry * entry);
	void Update(Entry entry);
	void getProb(Node * cnode, Entry * entry);
	void RemoveESC(void);
};

#endif