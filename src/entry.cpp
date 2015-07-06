#include "entry.hpp"

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

std::string Entry::ReturnSymbolOrESC()
{
	if (code_ESC) 
	{
		code_ESC = false;
		return ESC;
	} 
	else return symbol;
}

void Entry::UpdateProb(Interval interval)
{
	prob->push_back((double) (interval.getHigh() - interval.getLow()) / interval.getTotal());
}
	
void Entry::UpdateContext(void)
{
	std::string new_ctx = context.substr(1, context.size()-1 );
	context = new_ctx;
	level = 0;	
}

void Entry::EncodeESC(Node * cnode, ArithmeticCoderC * mAc)
{
	if (cnode->getChildrenFreq() != 0)
	{
		code_ESC = true;
		Encode(cnode, mAc); 
	}				
}

int Entry::Encode(int alphabet_size, ArithmeticCoderC * mAc)
{
	int high = alphabet_size;
	int low = --alphabet_size;
	Interval * interval = new Interval(low, high, high);

	UpdateProb(*interval);

	//std::clog << "symbol:" << symbol << " - low = " << low << ", high = " << high << ", total = " << high << std::endl;
	mAc->Encode(interval->getLow(), interval->getHigh(), interval->getTotal());
	
	delete interval;

	return alphabet_size;

}

void Entry::Encode(Node * cnode, ArithmeticCoderC * mAc)
{
	std::string str;
	std::vector<std::string> del_symb_copy;
	Interval *interval = new Interval();
	std::vector<Node*> *sorted_children = new std::vector<Node*>;

	str = ReturnSymbolOrESC();	// Returns which string will be encoded: an escape or a symbol

	interval->FindTotal(*del_symb, cnode);
	
	del_symb_copy = *del_symb;

	del_symb->clear();

	*sorted_children = cnode->Node::GetSortedChildren(del_symb_copy, del_symb);

	interval->FindLowHigh(str, sorted_children, cnode);	

	UpdateProb(*interval);

	//std::clog << "symbol: " << str << " - low = " << interval->getLow() << ", high = " << interval->getHigh() << ", total = " << interval->getTotal() << std::endl;
	mAc->Encode(interval->getLow(), interval->getHigh(), interval->getTotal());

	delete interval;
	delete sorted_children;
}