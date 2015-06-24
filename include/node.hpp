#ifndef __NODE_H
#define __NODE_H

#include <map>			// std::map
#include <string>		// std::string

#include <iostream>

class Node {
private:
	std::string name;
	int frequency;
	int childTotalFreq;
	std::map <std::string, Node*> children;
	int K; 

public:
	Node(void);
	~Node(void);
	Node(std::string s);

	std::map<std::string, Node*> * getChildren(void);
	void setChildren(std::string s, Node * newNode);

	int getK(void);
	void setK(int k);

	std::string getName(void);

	int getFrequency(void);
	int getChildTotalFreq(void);

	std::string updateContext(std::string ctx);
	void insertChild(std::string str);
	void updateChildren(std::string str, std::string ctx, int k);
};

#endif