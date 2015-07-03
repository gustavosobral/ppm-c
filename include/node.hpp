#ifndef __NODE_H
#define __NODE_H

#include <map>			// std::map
#include <string>		// std::string
#include <vector>		// std::vector
#include <iostream>
#include <algorithm>	// std::sort()

#define ESC "ESC"


class Node {
private:
	std::string name;
	int frequency;
	int children_freq;
	std::map <std::string, Node*> children;
	
public:
	Node(void);
	~Node(void);
	Node(std::string s);

	std::map<std::string, Node*> * getChildren(void);
	void setChildren(std::string s, Node * newNode);

	std::string getName(void);

	int getFrequency(void);

	int getChildrenFreq(void);
	void setChildrenFreq(int);

	std::vector<Node*> GetSortedChildren(std::vector<std::string> * del_symb);
	void InsertChild(std::string str);
	void UpdateChildren(std::string str, std::string ctx, int k);
	void UpdateFrequency(void);
	void DestructTree(void);
};

#endif