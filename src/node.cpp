#include "node.hpp"

Node::Node(void)
{
	frequency = 0;
	children_freq = 0;
}

Node::~Node(void){}

Node::Node(std::string s)
{
	name = s;
	frequency = 0;
	children_freq = 0;
}

std::map<std::string, Node*> * Node::getChildren(void)
{
	return &children;
}

void Node::setChildren(std::string s, Node * newNode)
{
	children[s] = newNode;
}

std::string Node::getName(void)
{
	return name;
}

int Node::getFrequency(void)
{
	return frequency;
}

void Node::updateFrequency(void)
{
	frequency = frequency + 1;
}

int Node::getChildrenFreq()
{
	return children_freq;
}

void Node::setChildrenFreq(int n)
{
	children_freq = n;
}

bool compareNodes(Node* i, Node* j)
{
	/* sort by frequency, but if the frequencies are equal then it is sorted by alphabetical order */
	if (i->getFrequency() == j->getFrequency()) 
	{
		std::string last_char_i = i->getName();
		std::string last_char_j = j->getName();
		last_char_i = last_char_i.substr(last_char_i.size() - 1);
		last_char_j = last_char_j.substr(last_char_j.size() - 1);

		return (last_char_i < last_char_j);
	}
	else return (i->getFrequency() > j->getFrequency());
}

std::vector<Node*> * Node::GetSortedChildren(std::vector<std::string> * del_symb)
{
	std::vector<Node*> *copy = new std::vector<Node*>;

	for(std::map<std::string, Node*>::iterator it = children.begin(); it != children.end(); it++)
	{
		copy->push_back(it->second);

		if (it->first == ESC) continue;
		else del_symb->push_back(it->first);
	}

	std::stable_sort(copy->begin(), copy->end(), compareNodes);

	return copy;
}

void Node::insertChild(std::string str)
{
	std::string new_name = name + str;

	Node *newNode = new Node(new_name);

	newNode->frequency += 1;
	children_freq += 1;
	
	if (children.count(ESC))
	{
		children[ESC]->frequency += 1;
		children_freq += 1;
	}

	Node *newESC = new Node(ESC);
	newNode->children[ESC] = newESC;

	children[str] = newNode;

}

void Node::updateChildren(std::string str, std::string ctx, int k)
{
	if (k > 0)
	{
		std::string new_ctx = ctx.substr(0,1);
		Node *cnode = children[new_ctx];
		cnode->updateChildren(str, ctx.substr(1, ctx.size() - 1 ), k-1);
	}

	else
	{
		if (children.count(str) == 0)	insertChild(str);
		else 
		{
			children[str]->updateFrequency();
			children_freq += 1;
		}
	}
}