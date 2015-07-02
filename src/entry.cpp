#include "entry.hpp"
#define ESC "ESC"

Entry::Entry(void){}

Entry::~Entry(void){}

Entry::Entry(std::string symb, std::string ctx)
{
	symbol = symb;
	context = ctx;
	level = 0;
	prob = new std::vector<double>;
	del_symb = new std::vector<std::string>;
	code_ESC = false;
}

std::string Entry::getSymbol(void)
{
	return symbol;
}

void Entry::setSymbol(std::string s)
{
	symbol = s;
}

std::string Entry::getContext(void)
{
	return context;
}

void Entry::setContext(std::string s)
{
	context = s;
}

int Entry::getLevel(void)
{
	return level;
}

std::vector<std::string> * Entry::getDelSymb(void)
{
	return del_symb;
}

void Entry::setDelSymb(std::vector<std::string> * v)
{
	del_symb = v;
}

std::vector<double> * Entry::getProb(void)
{
	return prob;
}

void Entry::setProb(std::vector<double> * v)
{
	prob = v;
}

bool Entry::getCodeESC(void)
{
	return code_ESC;
}

void Entry::setCodeESC(bool b)
{
	code_ESC = b;
}

void Entry::ResetLevel(void)
{
	level = 0;
}

std::string Entry::NextChild(void)
{
	return context.substr(level++,1);
}

bool compareNodes(Node* i, Node* j)
{
	/* sort by frequency, but if tre frequencies are equal then it is sorted by alphabetical order */
	if (i->getFrequency() == j->getFrequency()) 
	{
		std::string last_char_i = i->getName();
		std::string last_char_j = j->getName();
		last_char_i = last_char_i.substr(last_char_i.size() - 1);
		last_char_j = last_char_j.substr(last_char_j.size() - 1);

		return (last_char_i < last_char_j);
	}
	else return (i->getFrequency() > j->getFrequency());
}

int Entry::Encode(int alphabet_size, ArithmeticCoderC * mAc)
{
	int high = alphabet_size;
	int low = --alphabet_size;

	prob->push_back((double) (high - low) / high);

	mAc->Encode(low, high, high);

	std::clog << "symbol: " << symbol << " - low = " << low << ", high = " << high << ", total = " << high << std::endl;

	return alphabet_size;

}

void Entry::Encode(Node * cnode, ArithmeticCoderC * mAc)
{
	std::string str;
	int high, low = 0;
	int total = cnode->getChildTotalFreq();
	std::vector<Node*> *children;
	std::vector<std::string> del_symb_copy = *del_symb;

	if (code_ESC) str = ESC; 
	else str = symbol;
	
	del_symb->clear();

	children = cnode->Node::CopyChildren(del_symb);

	std::stable_sort(children->begin(), children->end(), compareNodes);

	for(std::vector<Node*>::iterator it = children->begin(); it != children->end(); it++)
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

	std::clog << "symbol: " << str << " - low = " << low << ", high = " << high << ", total = " << total << std::endl;

	for(std::vector<std::string>::iterator it = del_symb_copy.begin(); it != del_symb_copy.end(); it++)
	{
		std::clog << "deleted: " << *it << std::endl;
		total -= (*cnode->getChildren())[*it]->getFrequency(); 
	}

	prob->push_back((double) (high - low) / total);

	mAc->Encode(low, high, total);
}