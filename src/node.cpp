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
	children["ESC"]->frequency += 1;
	newNode->K = new_name.size();

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
		if (!children.count(str)) 
		{
			insertChild(str);
		}

		else 
		{
			Node *cnode = children[str];
			cnode->frequency += 1;
			childTotalFreq += 1;
		}
	}
}