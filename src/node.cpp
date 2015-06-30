#include "node.hpp"

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

std::map<std::string, Node*> * Node::getChildrens(void)
{
	return &childrens;
}

void Node::setChildren(std::string s, Node * newNode)
{
	childrens[s] = newNode;
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

int Node::getK(void)
{
	return K;
}

void Node::setK(int k)
{
	K = k;
}

int Node::getChildTotalFreq()
{
	return childTotalFreq;
}


void Node::insertChild(std::string str)
{
	std::string new_name = name + str;

	Node *newNode = new Node(new_name);

	newNode->frequency += 1;
	childTotalFreq += 2;
	childrens["ESC"]->frequency += 1;
	newNode->K = new_name.size();

	Node *newESC = new Node("ESC");
	newNode->childrens["ESC"] = newESC;

	childrens[str] = newNode;
}

// Need to be explained! :p
void Node::updateChildren(std::string str, std::string ctx, int k)
{
	if (k > 0)
	{
		std::string new_ctx = ctx.substr(0,1);
		Node *cnode = childrens[new_ctx];
		cnode->updateChildren(str, ctx.substr(1, ctx.size() - 1 ), k-1);
	}

	else 
	{
		if (childrens.count(str) == 0)
		{
			insertChild(str);
		}

		else 
		{
			childrens[str]->updateFrequency();
			childTotalFreq += 1;
		}
	}
}