#ifndef __PPMC_H
#define __PPMC_H

#include "node.hpp"
#include "arithmeticcoderc.hpp"

#include <map>			// std::map
#include <string>		// std::string
#include <cmath>		// std::string
#include <vector>		// std::vector
#include <algorithm>	// std::sort()

class PPMC {
private:
	Node * root;
	int alphabet_size;
	std::map<char,bool> char_map;
	ArithmeticCoderC * mAc;

public:
	PPMC(void);
	PPMC(int);
	PPMC(ArithmeticCoderC * ac);
	~PPMC(void);
	Node * getRoot(void);
	int getAlphabet_size(void);
	void setAlphabet_size(int);

	void updateTree(std::string str, std::string ctx);
	void getProb(Node * cnode, std::string str, std::string ctx, int level, int k, std::vector<double> * prob);
	void encode(std::string str, std::vector<double> * prob);
	void encode(Node * cnode, std::string str, std::vector<double> * prob);
	void removeESC(void);
};

#endif