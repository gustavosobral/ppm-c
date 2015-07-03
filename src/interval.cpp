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

	for(std::vector<std::string>::iterator it = del_symb.begin(); it != del_symb.end(); it++)
	{
		//std::clog << "deleted: " << *it << std::endl;
		total -= (*cnode->getChildren())[*it]->getFrequency(); 
	}
}

void Interval::FindLowHigh(std::string str, std::vector<Node*> * children, Node * cnode)
{
	for(std::vector<Node*>::iterator it = children->begin(); it != children->end(); it++)
	{
		if (*it == (*cnode->getChildren())[str]) 
		{
			high = low + (*it)->getFrequency();
			break;
		} else
		{
			low += (*it)->getFrequency();
		}
	}
}