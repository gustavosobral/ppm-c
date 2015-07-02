#ifndef __INTERVAL_H
#define __INTERVAL_H

#include "node.hpp"

#include <map>			// std::map
#include <string>		// std::string
#include <vector>		// std::vector

class Interval {
private:
	int low;
	int high;
	int total;
	
public:
	Interval();
	Interval(int low, int high, int total);
	~Interval();

	int getLow(void);
	int getHigh(void);
	int getTotal(void);

	void FindTotal(std::vector<std::string> del_symb, Node * cnode);
	void FindLowHigh(std::string str, std::vector<Node*> * children, Node * cnode);
	
};

#endif