#include "ppmc.hpp"

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

	root->setChildrenFreq(root->getChildrenFreq() - (*root_children)[ESC]->getFrequency());
	
	delete (*root_children)[ESC];
	root_children->erase(ESC);
}

void PPMC::Update(Entry entry)
{
	std::string str = entry.getSymbol();
	std::string ctx = entry.getContext();

	for (int i = ctx.size(); i > 0; i--)
	{
		root->UpdateChildren(str, ctx, i);
		ctx = ctx.substr(1,i-1);
	}
	root->UpdateChildren(str, "", 0);

	if ((*root->getChildren()).count(ESC) && alphabet_size == 0) RemoveESC();
}


void PPMC::SymbolIsNotChild(Node * cnode, Entry * entry)
{
	entry->EncodeESC(cnode, mAc);
	
	/* if the context is "" (empty), then the symbol is only found in k = -1 */
	if (entry->getContext() == "")
	{
		alphabet_size = entry->Encode(alphabet_size, mAc);
		return;
	}
	/* else the search restart in k = k - 1 */
	else
	{
		entry->UpdateContext();
		return GetProbability(root, entry);
	}
}

void PPMC::GetProbability(Node * cnode, Entry * entry)
{
	/* checks if the context of current node is equal to the context wanted */
	if (cnode->getName() == entry->getContext())
	{
		/* checks if the symbol (str) is a child of current node */
		if (!(*cnode->getChildren()).count(entry->getSymbol()))
		{			
			SymbolIsNotChild(cnode, entry);
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
		Node *new_node = (*cnode->getChildren())[child];
		return GetProbability(new_node, entry);
	}
}