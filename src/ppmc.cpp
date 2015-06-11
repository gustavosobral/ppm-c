#include "ppmc.hpp"

PPMC::~PPMC(void){}

/* create Tree */ 
PPMC::PPMC(void)
{

	Node *root = new Node("");
	Node *newESC = new Node("ESC");

	root->setChildren("ESC", newESC); 
}


Node * PPMC::getRoot(void)
{
	return root;
}