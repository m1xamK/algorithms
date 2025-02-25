#include "pch.h"
#include "../PatriciaTree/PatriciaTree.h"
#include <bitset>

TEST(PatriciaTreeTests, InsertTest)
{
	PatriciaTree<std::bitset<8>> a;
	a.Insert('a');
	a.Insert('v');
	a.Insert('b');
	a.Insert('e');
	a.Insert('l');
	a.Insert('j');
	a.Output();
	a.Draw("graph1.gv");
}

TEST(SearchTests, EmptyTree)
{
	PatriciaTree<std::bitset<8>> a;
	EXPECT_EQ(nullptr, a.Search('a'));
	EXPECT_EQ(nullptr, a.Search('b'));
	EXPECT_EQ(nullptr, a.Search('c'));
}

TEST(SearchTests, ExistElements)
{
	PatriciaTree<std::bitset<8>> a;
	a.Insert('a');
	a.Insert('v');
	a.Insert('l');
	a.Insert('b');
	a.Insert('j');
	EXPECT_EQ('a', a.Search('a')->GetKey());
	EXPECT_EQ('v', a.Search('v')->GetKey());
	EXPECT_EQ('l', a.Search('l')->GetKey());
	EXPECT_EQ('b', a.Search('b')->GetKey());
	EXPECT_EQ('j', a.Search('j')->GetKey());
}

TEST(SearchTests, NonExistElements)
{
	PatriciaTree<std::bitset<8>> a;
	a.Insert('a');
	a.Insert('v');
	a.Insert('l');
	a.Insert('b');
	a.Insert('j');
	EXPECT_EQ(nullptr, a.Search('k'));
	EXPECT_EQ(nullptr, a.Search('t'));
	EXPECT_EQ(nullptr, a.Search('r'));
	EXPECT_EQ(nullptr, a.Search('n'));
	EXPECT_EQ(nullptr, a.Search('m'));
}

TEST(PatriciaTreeTests, WalkTest)
{
	PatriciaTree<std::bitset<8>> a;
	a.Insert('a');
	a.Insert('v');
	a.Insert('b');
	a.Insert('e');
	a.Insert('l');

	std::vector<char> res;
	res = a.Walk(a.GetRoot(), res);
	std::vector<char> exp = { '\0', 'a', 'v' ,'l', 'e', 'b' };

	for (int i = 0; i < res.size(); ++i)
	{
		EXPECT_EQ(exp[i], res[i]);
	}
}
