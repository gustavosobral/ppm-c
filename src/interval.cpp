#include "interval.hpp"

Interval::Interval()
{
	low = 0;
	high = 0;
	total = 0;
}

Interval::Interval(int l, int h, int t)
{
	low = l;
	high = h;
	total = t;
}

Interval::~Interval(){}

int Interval::getLow(void)
{
	return low;
}

int Interval::getHigh(void)
{
	return high;
}

int Interval::getTotal(void)
{
	return total;
}

void Interval::FindTotal(std::vector<std::string> del_symb, Node * cnode)
{
	total = cnode->getChildrenFreq(); 

	// Exclude frequencies of symbols deleted by exclusion rule from total 
	for(std::vector<std::string>::iterator it = del_symb.begin(); it != del_symb.end(); it++)
	{
		total -= (*cnode->getChildren())[*it]->getFrequency(); 
	}
}

void Interval::FindLowHigh(std::string str, std::vector<Node*> * sorted_children, Node * cnode)
{

	/* Increment low until cnode is found in the vector of sorted children. When cnode is found, calculate high
	by adding its frequency to low value */
	for(std::vector<Node*>::iterator it = sorted_children->begin(); it != sorted_children->end(); it++)
	{
		if (*it == (*cnode->getChildren())[str]) 
		{
			high = low + (*it)->getFrequency();
			break;
		} else {
			low += (*it)->getFrequency();
		}
	}
}