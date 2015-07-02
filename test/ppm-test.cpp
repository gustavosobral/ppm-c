#include "node.hpp"
#include "ppmc.hpp"
#include "file.hpp"

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
		if ((*cnode->getChildren()).empty()) return;

		std::map<std::string, Node*>::iterator it = cnode->getChildren()->begin();
		while(it != cnode->getChildren()->end())
		{
			//std::clog << cnode->getName() << " - " << it->second->getName() << ":" << it->first << std::endl;
			if (it->first != "ESC") EXPECT_EQ(it->second->getName(), cnode->getName() + it->first );
			CheckTree((*cnode->getChildren())[it->first]);
			it++;
		}
	} 
 
};

TEST_F(PPMTest, insertChild)
{
	std::string str = "abc";
	test_node->insertChild(str);		
	EXPECT_EQ("abc", ((*test_node->getChildren())[str])->getName());
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
	//std::string word = "ARARA";
	
	std::string word = "ABRACADABRA";
	Tree->setAlphabetSize(5);

	int size_word = word.size();

	//std::vector<double> expected[5] = {(double)1/2, 1, (double)1/4, (double)1/2, (double)1/2};
	std::string str, ctx;
	std::vector<double> expected[11];
	Entry *entry, original_entry;
	
	expected[0].push_back((double)1/5);

	expected[1].push_back((double)1/2);
	expected[1].push_back((double)1/4);

	expected[2].push_back((double)1/2);
	expected[2].push_back((double)1/3);

	expected[3].push_back((double)1/6);

	expected[4].push_back((double)1/2);
	expected[4].push_back((double)3/6);
	expected[4].push_back((double)1/2);

	expected[5].push_back((double)2/9);

	expected[6].push_back((double)2/4);
	expected[6].push_back((double)4/8);
	expected[6].push_back((double)1);

	expected[7].push_back((double)3/7);

	expected[8].push_back((double)1/6);

	expected[9].push_back((double)1/2);

	expected[10].push_back((double)1/2);

	for (int i = 0; i < size_word; i++)
	{
		str = word.substr(i, 1);

		switch (i) 
		{
			case 0:		entry = new Entry(str, "");
			   			break;
			
			case 1:		entry = new Entry(str, word.substr(0,1));
						break;  
			
			default:	entry = new Entry(str, word.substr(i-2,2));	 

		}

		std::clog << "(" << str << "," << entry->getContext() << ")" << std::endl;
		original_entry = *entry;
		Tree->PPMC::getProb(Tree->getRoot(), entry);
		EXPECT_EQ(expected[i], *entry->getProb());
		Tree->PPMC::Update(original_entry);	 
	}
}