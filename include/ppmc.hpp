#ifndef __PPMC_H
#define __PPMC_H

#include "node.hpp"

#include <map>			// std::map
#include <string>		// std::string

class PPMC {
private:
	Node * root;

public:
	PPMC(void);
	~PPMC(void);
	Node * getRoot(void);
};

#endif