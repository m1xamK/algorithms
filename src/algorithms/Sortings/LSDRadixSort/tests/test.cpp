#include <gtest/gtest.h>
#include <vector>
#include <../include/LSD/LSD.hpp>

TEST(sortParamw, LSDsort)
{
	std::string a = "dex";
	std::string b = "asd";
	std::string c = "sdf";
	std::string d = "fgh";
	std::string e = "jkh";
	std::string f = "kht";

	std::vector<std::string> input = { a,b,c,d,e,f };
	LSDSort(input);
	for (auto i : input) {
		std::cout << i << std::endl;
	}
}


TEST(sortParamw2, LSDsort2)
{
	std::string a = "dex";
	std::string b = "asd";
	std::string c = "sdf";
	std::string d = "fgh";
	std::string e = "jkh";
	std::string f = "kht";
	std::vector<std::string> exp = { b,a,d,e,f,c };
	std::vector<std::string> input = { a,b,c,d,e,f };
	LSDSort(input);
	ASSERT_EQ(exp, input);
}


TEST(sortParamw3, LSDsort3)
{
	std::string a = "aqqaa";
	std::string b = "qqbbb";
	std::string c = "wwccc";
	std::string d = "ddddd";
	std::string e = "rreee";
	std::string f = "fffff";
	std::vector <std::string> vec = { a,d,f,b,e,c };
	std::vector<std::string> input = { a,b,c,d,e,f };
	LSDSort(input);
	EXPECT_EQ(vec, input);
}


TEST(sortParamw4, LSDsort4)
{
	std::string a = "asdfg";
	std::string b = "sdfgh";
	std::string c = "werty";
	std::string d = "bnmcv";
	std::string e = "uiopq";
	std::string f = "zxccc";
	std::vector <std::string> vec = { a,d,b,e,c,f };

	
	std::vector<std::string> input = { a,b,c,d,e,f };
	LSDSort(input);
	EXPECT_EQ(vec, input);
}