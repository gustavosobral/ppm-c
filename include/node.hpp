#ifndef __NODE_H
#define __NODE_H

#include <map>			// std::map
#include <string>		// std::string

class Node {
private:
	std::string name;
	int frequency;
	int childTotalFreq;
	std::map <std::string, Node*> childrens;

public:
	Node(void);
	~Node(void);
};

#endif