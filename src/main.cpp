#include "node.hpp"
#include "ppmc.hpp"

#include <iostream>
#include <exception>

int main(int argc, char * argv[], char * envp[])
{
	PPMC *Tree = new PPMC();

	Node *root = Tree->getRoot();

	std::string word = "ABRACADABRA";
	int k = 2;
	int i, j;
	int size_word =  word.size();

	std::string str, ctx;


	for (j = 0; j < size_word; j++)
	{
		for (i = k; i > 0; i--)
		{
			str = word.substr(j,1);
			
			if ( j-i >= 0 ) ctx = word.substr(j-i,i);
			else continue;
			
			std::clog << "(" << str << "," << ctx << "," << i << ") - ";
			root->updateChildren(str, ctx, i);
		}

		std::clog << "(" << str << ", ," << i << ")" << std::endl;
		root->updateChildren(str, "", i);
	}


	std::clog << "updates finished! " << std::endl;
	 
	for (std::map<std::string, Node*>::iterator it = root->getChildren()->begin(); it != root->getChildren()->end(); it++)
	{
		std::clog << root->getName() << " - " << it->first << ":" << it->second->getName() << std::endl;
		Node *cnode = (*root->getChildren())[it->first];
			
		for (std::map<std::string, Node*>::iterator it2 = cnode->getChildren()->begin(); it2 != cnode->getChildren()->end(); it2++)
		{
			std::clog << cnode->getName() << " - " << it2->first << ":" << it2->second->getName() << std::endl;
			Node *ccnode = (*cnode->getChildren())[it2->first];
			
			for (std::map<std::string, Node*>::iterator it3 = ccnode->getChildren()->begin(); it3 != ccnode->getChildren()->end(); it3++)
			{
				std::clog << ccnode->getName() << " - " << it3->first << ":" << it3->second->getName() << std::endl;
			}
		}
	}
	
	return 0;
}