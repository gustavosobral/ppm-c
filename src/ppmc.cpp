#include "ppmc.hpp"
#define ESC "ESC"

PPMC::~PPMC(void){}

PPMC::PPMC(void)
{
	root = new Node("");
	Node *newESC = new Node(ESC);

	root->setChildren(ESC, newESC); 
}

PPMC::PPMC(ArithmeticCoderC * ac)
{
	root = new Node("");
	Node *newESC = new Node(ESC);
	mAc = ac;

	root->setChildren(ESC, newESC); 
}

Node * PPMC::getRoot(void)
{
	return root;
}

int PPMC::getAlphabetSize(void)
{
	return alphabet_size;
}

void PPMC::setAlphabetSize(int n)
{
	alphabet_size = n;
}

void PPMC::RemoveESC(){

	std::map<std::string,Node*> *root_children = root->getChildren();

	root->setChildTotalFreq(root->getChildTotalFreq() - (*root_children)[ESC]->getFrequency());
	
	delete (*root_children)[ESC];
	root_children->erase(ESC);
}

void PPMC::Update(Entry entry)
{
	std::string str = entry.getSymbol();
	std::string ctx = entry.getContext();

	for (int i = ctx.size(); i > 0; i--)
	{
		root->updateChildren(str, ctx, i);
		ctx = ctx.substr(1,i-1);
	}
	root->updateChildren(str, "", 0);

	if ((*root->getChildren()).count(ESC) && alphabet_size == 0) RemoveESC();
}

void PPMC::getProb(Node * cnode, Entry * entry)
{
	/* checks if the context of current node is equal to the context wanted */
	if (cnode->getName() == entry->getContext())
	{
		/* checks if the symbol (str) is a child of current node */
		if (!(*cnode->getChildren()).count(entry->getSymbol()))
		{
			/* encode if node was created and initialized */
			if (cnode->getChildTotalFreq() != 0) 
				{
					entry->setCodeESC(true);
					entry->Encode(cnode, mAc); 
				}
					
			/* if the context is "" (empty), then the symbol is only found in k = -1 */
			if (entry->getContext() == "")
			{
				alphabet_size = entry->Encode(alphabet_size, mAc);
				return;
			}
			/* else the search restart in k = k - 1 */
			else
			{
				std::string new_ctx = entry->getContext().substr(1);
				entry->setContext(new_ctx);
				entry->ResetLevel();

				return getProb(root, entry);
			}
		}
		/* if the symbol is a child of cnode, then its propability is returned */
		else
		{
			entry->Encode(cnode, mAc);
			return;
		}
	}
	/* if the context is not the wanted one, then the node is updated */ 
	else
	{	
		std::string child = entry->NextChild();
		if (!(*cnode->getChildren()).count(child)) return;
		else
		{
			Node *new_node = (*cnode->getChildren())[child];
			return getProb(new_node, entry);
		}
	}
}

