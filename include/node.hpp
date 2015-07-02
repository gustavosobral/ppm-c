#ifndef __NODE_H
#define __NODE_H

#include <map>			// std::map
#include <string>		// std::string
#include <vector>		// std::vector
#include <iostream>

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
	int getChildTotalFreq(void);
	void setChildTotalFreq(int);

	std::vector<Node*> * CopyChildren(std::vector<std::string> * del_symb);
	std::string updateContext(std::string ctx);
	void insertChild(std::string str);
	void updateChildren(std::string str, std::string ctx, int k);
	void updateFrequency(void);

};

#endif