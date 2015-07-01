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

PPMC::PPMC(ArithmeticCoderC * ac)
{
	root = new Node("");
	Node *newESC = new Node("ESC");
	root->setK(0);
	mAc = ac;

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
  return (i->getFrequency() > j->getFrequency());
}

void PPMC::removeESC(){

	int freq = (*root->getChildren())["ESC"]->getFrequency();

	root->setChildTotalFreq(root->getChildTotalFreq() - freq);
	delete (*root->getChildren())["ESC"];
	(*root->getChildren()).erase("ESC");
}

void PPMC::updateTree(std::string str, std::string ctx)
{
	int i;
	
	for (i = ctx.size(); i > 0; i--)
	{
		root->updateChildren(str, ctx, i);
		ctx = ctx.substr(1,i-1);
	}
	root->updateChildren(str, "", i);

	if ((*root->getChildren()).count("ESC") && alphabet_size == 0) removeESC();
}

void PPMC::getProb(Node * cnode, std::string str, std::string ctx, int level, int k, std::vector<double> * prob)
{
	/* checks if the context of current node is equal to the context wanted */
	if (cnode->getName() == ctx)
	{
		/* checks if the symbol (str) is a child of current node */
		if (!(*cnode->getChildren()).count(str))
		{
			encode(cnode, "ESC", prob);

			/* if the context is "" (empty), then the symbol is only found in k = -1 */
			if (ctx == "")
			{
				//qual intervalo em k = -1? a prob calculada sempre sera a menor e portanto o ultimo intervalo?
				encode(str, prob);
				return;
			}
			/* else the search restart in k = k - 1 */
			else
			{
				std::string new_ctx = ctx.substr(1, --k);
				return getProb(root, str, new_ctx, 0, k, prob);
			}
		}
		/* if the symbol is a child of cnode, then its propability is returned */
		else
		{
			encode(cnode, str, prob);
			return;
		}
	}
	/* if the context is not the wanted one, then the node is updated */ 
	else
	{	
		std::string child = ctx.substr(level,1);
		if (!(*cnode->getChildren()).count(child)) return;
		else
		{
			Node *new_node = (*cnode->getChildren())[child];
			return getProb(new_node, str, ctx, ++level, k, prob);
		}
	}
}

void PPMC::encode(Node * cnode, std::string str, std::vector<double> * prob)
{
	int low = 0;
	int high = 0;
	int total = cnode->getChildTotalFreq();
	double cprob;
	std::vector<Node*> copy_nodes;

	if (total == 0) return; /* node was created but not initialized */

	for(std::map<std::string, Node*>::iterator it = cnode->getChildren()->begin(); it != cnode->getChildren()->end(); it++)
	{
		copy_nodes.push_back(it->second);
	}

	std::stable_sort(copy_nodes.begin(), copy_nodes.end(), compareNodes);

	for(std::vector<Node*>::iterator it = copy_nodes.begin(); it != copy_nodes.end(); it++)
	{
		if (*it == (*cnode->getChildren())[str]) 
		{
			high = low + (*it)->getFrequency();
			break;
		}
		else
		{
			low += (*it)->getFrequency();
		}
	}

	// std::clog << "symbol: " << str << " - low = " << low << ", high = " << high << ", total = " << total << std::endl;

	cprob = (double) (high - low) / total;
	prob->push_back(cprob);

	mAc->Encode(low, high, total);
}

void PPMC::encode(std::string str, std::vector<double> * prob){

	int total = alphabet_size;
	int high = alphabet_size; 
	int low = alphabet_size - 1;

	double cprob = (double) (high - low) / total;
	prob->push_back(cprob);

	// std::clog << "symbol: " << str << " - low = " << low << ", high = " << high << ", total = " << total << std::endl;

	--alphabet_size;
}