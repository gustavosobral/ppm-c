#include "../include/node.hpp"
#include "../include/ppmc.hpp"

#include <iostream>

int main(int argc, char * argv[], char * envp[])
{
	PPMC *Tree = new PPMC();

	Tree->getRoot()->updateChildren("A", "", 0);
	Tree->getRoot()->updateChildren("B", "A", 1);
	Tree->getRoot()->updateChildren("R", "AB", 2);
	
	Node *newNode = new Node("hello");
	//std::clog << newNode->getFrequency() << std::endl;

//	while(true){
/*
		std::clog << "name:" << Tree->getRoot()->getName() << std::endl;

		for (std::map<std::string, Node*>::iterator it = Tree->getRoot()->getChildren()->begin(); it != Tree->getRoot()->getChildren()->end(); it++)
		{
			std::clog << &it->first << ":" << &it->second << std::endl;
		}
	//}*/
	

	return 0;
}