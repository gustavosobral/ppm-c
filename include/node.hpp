#ifndef __NODE_H
#define __NODE_H

#include <map>			// std::map
#include <string>		// std::string

class Node {
private:
	std::string name;
	int frequency;
	int childTotalFreq;
	std::map <std::string, Node*> children;

public:
	Node(void);
	~Node(void);
	Node(std::string s);

	std::map<std::string, Node*> * getChildren(void);
	void setChildren(std::string s, Node * newNode);

	std::string getName(void);

	int getFrequency(void);
	
	std::string updateContext(std::string ctx);
	void insertChild(std::string str);
	void updateChildren(std::string str, std::string ctx, int k);
};

#endif