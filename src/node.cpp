#include "node.hpp"
#define ESC "ESC"

Node::Node(void)
{
	frequency = 0;
	childTotalFreq = 0;
}

Node::~Node(void){}

Node::Node(std::string s)
{
	name = s;
	frequency = 0;
	childTotalFreq = 0;
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

int Node::getChildTotalFreq()
{
	return childTotalFreq;
}

void Node::setChildTotalFreq(int n)
{
	childTotalFreq = n;
}

std::vector<Node*> * Node::CopyChildren(std::vector<std::string> * del_symb)
{
	std::vector<Node*> *copy = new std::vector<Node*>;

	for(std::map<std::string, Node*>::iterator it = children.begin(); it != children.end(); it++)
	{
		copy->push_back(it->second);

		if (it->first == ESC) continue;
		else del_symb->push_back(it->first);
	}

	return copy;
}

void Node::insertChild(std::string str)
{
	std::string new_name = name + str;

	Node *newNode = new Node(new_name);

	newNode->frequency += 1;
	childTotalFreq += 1;
	
	if (children.count("ESC"))
	{
		children["ESC"]->frequency += 1;
		childTotalFreq += 1;
	}

	Node *newESC = new Node("ESC");
	newNode->children["ESC"] = newESC;

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
			childTotalFreq += 1;
		}
	}
}