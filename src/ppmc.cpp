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
	if (cnode->getName() == ctx)
	{
		if (!(*cnode->getChildrens()).count(str))
		{
			if (ctx == "")
			{
				return (double)1/alphabet_size--;
			}
			else
			{
				std::string new_ctx = ctx.substr(1, --k);
				return getProb(root, str, new_ctx, 0, k);
			}
		}
		else
		{
			int freq = (*cnode->getChildrens())[str]->getFrequency();
			int total = cnode->getChildTotalFreq();
			return (double)freq/total;
		}
	}
	else
	{
		std::string child = ctx.substr(level,1);
		if (!(*cnode->getChildrens()).count(child)) return 0;
		else
		{
			Node *new_node = (*cnode->getChildrens())[child];
			return getProb(new_node, str, ctx, ++level, k);
		}
	}
}