#include "node.hpp"
#include "ppmc.hpp"

#include <iostream>
#include <gtest/gtest.h>
 
class PPMTest : public testing::Test
{
public:
  	Node *test_node;
  	PPMC *Tree;
 
  	virtual void SetUp()
  	{
  		test_node = new Node("");
		Node *newESC = new Node("ESC");
		test_node->setK(0);

		test_node->setChildren("ESC", newESC); 

		Tree = new PPMC(); 
  	}
 
	virtual void TearDown()
	{
	}

	void fillTree(std::string word, int size_word, int k)
	{
		int i, j;
		std::string ctx, str;

		for (j = 0; j < size_word; j++)
		{
			for (i = k; i > 0; i--)
			{
				str = word.substr(j,1);			
				if ( j-i >= 0 ) ctx = word.substr(j-i,i);
				else continue;
				//std::clog << "(" << str << "," << ctx << "," << i << ")" << std::endl;			
				test_node->updateChildren(str, ctx, i);
			}
			//std::clog << "(" << str << "," << "" << "," << i << ")" << std::endl;	
			test_node->updateChildren(str, "", i);
		}
	}

	void CheckTree(Node * cnode)
	{
		if ((*cnode->getChildrens()).empty()) return;

		std::map<std::string, Node*>::iterator it = cnode->getChildrens()->begin();
		while(it != cnode->getChildrens()->end())
		{
			//std::clog << cnode->getName() << " - " << it->second->getName() << ":" << it->first << std::endl;
			if (it->first != "ESC") EXPECT_EQ(it->second->getName(), cnode->getName() + it->first );
			CheckTree((*cnode->getChildrens())[it->first]);
			it++;
		}
	} 
 
};

TEST_F(PPMTest, insertChild)
{
	std::string str = "abc";
	test_node->insertChild(str);		
	EXPECT_EQ("abc", ((*test_node->getChildrens())[str])->getName());
}

TEST_F(PPMTest, updateChildren)
{
	std::string word = "ARARA";
	int k = 2;
	int size_word = word.size();

	fillTree(word, size_word, k);

	CheckTree(test_node);
}

TEST_F(PPMTest, getProb)
{
	std::string word = "ARARA";
	Tree->setAlphabet_size(2);

	int i;
	int k;
	int size_word = word.size();
	double expected[5] = {(double)1/2, 1, (double)1/4, (double)1/2, (double)1/2};
	std::string str, ctx;

	for (i = 0; i < size_word; i++)
	{
		str = word.substr(i,1);
		switch (i) 
		{
			case 0: 	ctx = "";
						k = 0;
			   			break;
			
			case 1: 	ctx = word.substr(0,1);
						k = 1;
						break;  
			
			default: 	ctx = word.substr(i-2,2);	 
						k = 2;
		}

		EXPECT_EQ(expected[i], Tree->PPMC::getProb(Tree->getRoot(), str, ctx, 0, k));
		Tree->PPMC::updateTree(Tree->getRoot(), str, ctx);		 

	}

	/*
	EXPECT_EQ((double) 1/2, Tree->PPMC::getProb(Tree->getRoot(), "A", "", 0, 0));
	updateTree(Tree->getRoot(), "A", "");
	
	EXPECT_EQ((double) 1, Tree->PPMC::getProb(Tree->getRoot(), "B", "A", 0, 1));
	updateTree(Tree->getRoot(), "B", "A");

	EXPECT_EQ((double) 1/4, Tree->PPMC::getProb(Tree->getRoot(), "a", "ar", 0, 2));
	updateTree(Tree->getRoot(), "", "ar");

	EXPECT_EQ((double) 1/2, Tree->PPMC::getProb(Tree->getRoot(), "r", "ra", 0, 2));
	updateTree(Tree->getRoot(), "r", "ra");

	EXPECT_EQ((double) 1/2, Tree->PPMC::getProb(Tree->getRoot(), "a", "ar", 0, 2));
	updateTree(Tree->getRoot(), "a", "ar");*/


}