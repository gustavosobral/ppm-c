#include "ppmc.hpp"

PPMC::~PPMC(void){}

/* create Tree */ 
PPMC::PPMC(void)
{
	root = new Node("");
	Node *newESC = new Node("ESC");
	root->setK(0);

	root->setChildren("ESC", newESC); 
}

PPMC::PPMC(int n)
{
	root = new Node("");
	Node *newESC = new Node("ESC");
	root->setK(0);
	alphabet_size = n;

	root->setChildren("ESC", newESC); 
}


Node * PPMC::getRoot(void)
{
	return root;
}

int PPMC::getAlphabet_size(void)
{
	return alphabet_size;
}

void PPMC::setAlphabet_size(int n)
{
	alphabet_size = n;
}

bool compareNodes(Node* i, Node* j)
{
  return (i->getFrequency() < j->getFrequency());
}

void PPMC::updateTree(Node * cnode, std::string str, std::string ctx)
{
	int i;
	
	for (i = ctx.size(); i > 0; i--)
	{
		cnode->updateChildren(str, ctx, i);
		ctx = ctx.substr(1,i-1);
	}
	cnode->updateChildren(str, "", i);
}

double PPMC::getProb(Node * cnode, std::string str, std::string ctx, int level, int k)
{
	/* checks if the context of current node is equal to the context wanted */
	if (cnode->getName() == ctx)
	{
		/* checks if the symbol (str) is a child of current node */
		if (!(*cnode->getChildren()).count(str))
		{
			//codificar escape

			/* if the context is "" (empty), then the symbol is only found in k = -1 */
			if (ctx == "")
			{
				return (double)1/alphabet_size--;
			}
			/* else the search restart in k = k - 1 */
			else
			{
				std::string new_ctx = ctx.substr(1, --k);
				return getProb(root, str, new_ctx, 0, k);
			}
		}
		/* if the symbol is a child of cnode, then its propability is returned */
		else
		{
			int freq = (*cnode->getChildren())[str]->getFrequency();
			int total = cnode->getChildTotalFreq();
			// codificar simbolo 
			return (double)freq/total;
		}
	}
	/* if the context is not the wanted one, then the node is updated */ 
	else
	{	
		std::string child = ctx.substr(level,1);
		if (!(*cnode->getChildren()).count(child)) return 0;
		else
		{
			Node *new_node = (*cnode->getChildren())[child];
			return getProb(new_node, str, ctx, ++level, k);
		}
	}
}

void PPMC::encode(Node * cnode, std::string str)
{
	int low = 0;
	int high;
	int total = cnode->getChildTotalFreq();
	std::vector<Node*> copy_nodes;

	for(std::map<std::string, Node*>::iterator it = cnode->getChildren()->begin(); it != cnode->getChildren()->end(); it++)
	{
		copy_nodes.push_back(it->second);
	}

	std::stable_sort(copy_nodes.begin(), copy_nodes.end(), compareNodes);

	for(std::vector<Node*>::iterator it = copy_nodes.begin(); it != copy_nodes.end(); it++)
	{
		if (*it == cnode) 
		{
			high = low + (*it)->getFrequency();
			break;
		}
		else
		{
			low += (*it)->getFrequency();
		}
	}

	// aritmetic(low, high, total);

}