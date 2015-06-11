#include "node.hpp"
#include "ppmc.hpp"

#include <iostream>

int main(int argc, char * argv[], char * envp[])
{
	PPMC *Tree = new PPMC();

	Tree->getRoot()->updateChildren("A", "", 0);

	Tree->getRoot()->updateChildren("B", "A", 1);
	Tree->getRoot()->updateChildren("B", "", 0);

	Tree->getRoot()->updateChildren("R", "AB", 2);
	Tree->getRoot()->updateChildren("R", "B", 1);
	Tree->getRoot()->updateChildren("R", "", 0);

	Tree->getRoot()->updateChildren("A", "BR", 2);
	Tree->getRoot()->updateChildren("A", "R", 1);
	Tree->getRoot()->updateChildren("A", "", 0);

	std::clog << "updates finished! " << std::endl;
	 
	Node *my_root = Tree->getRoot();

	for (std::map<std::string, Node*>::iterator it = my_root->getChildren()->begin(); it != my_root->getChildren()->end(); it++)
	{
		std::clog << my_root->getName() << " - " << it->first << ":" << it->second->getName() << std::endl;
		Node *cnode = (*my_root->getChildren())[it->first];
			
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