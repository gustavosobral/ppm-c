#include "node.hpp"

Node::Node(void){}

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


std::string Node::updateContext(std::string ctx)
{
	int i;
	int N = ctx.size() - 1;

	if (N < 1) return NULL;

	char new_ctx[N];
	std::string new_str;

	for (i = 0; i < N; i++) new_ctx[i] = ctx[i+1];

	new_str = new_ctx;

	return new_str;	
}

void Node::insertChild(std::string str)
{
	Node *newNode = new Node(str);

	newNode->frequency += 1;
	childTotalFreq += 1;
	children["ESC"]->frequency += 1;

	Node *newESC = new Node("ESC");
	newNode->children["ESC"] = newESC;

	children[str] = newNode;
}

void Node::updateChildren(std::string str, std::string ctx, int k)
{
	if (children[str] == NULL) insertChild(str);

	else 
	{
		Node *cnode = children[str];
		cnode->frequency += 1;
		childTotalFreq += 1;
	}

	if (k == 0) return;

	Node *cnode = children[ctx];
	cnode->updateChildren(str, updateContext(ctx) ,k-1);

	
}