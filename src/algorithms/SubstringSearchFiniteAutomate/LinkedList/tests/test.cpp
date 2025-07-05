#pragma once
#include "pch.h"
#include "../src/SearchSubStrFA.hpp"

TEST(searchTests, firstTest)
{
	EXPECT_TRUE(true);
	std::string txt = "AABAACAADAABAAABAA";
	std::string pat = "AABA";
	std::vector<int> expect = { 0,9,13 };

	EXPECT_EQ(expect, search(pat, txt));
}

TEST(searchTests, secondTest)
{
	EXPECT_TRUE(true);
	std::string txt = "sobaka sela na Penkova";
	std::string pat = "na";
	std::vector<int> expect = { 12 };

	EXPECT_EQ(expect, search(pat, txt));
}

TEST(searchTests, emptyTest)
{
	EXPECT_TRUE(true);
	std::string txt = "AABAACAADAABAAABAA";
	std::string pat = "noo";
	std::vector<int> expect = { };

	EXPECT_EQ(expect, search(pat, txt));
}
