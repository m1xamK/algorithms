#include <gtest/gtest.h>
#include "../src/fing_string.cpp"

TEST(FindString_make_image, FindString) {
	FindString test_str;
	std::unordered_map<char, int> map = test_str.makeImage("data");
	ASSERT_EQ(map['t'], 1);
	ASSERT_EQ(map['a'], 2);
	ASSERT_EQ(map['d'], 3);
}

TEST(FindString_boyerMooreSearch, FindString) {
	FindString test_str;
	ASSERT_EQ(test_str.boyerMooreSearch("data", "Hello data, dat"), true);
	ASSERT_EQ(test_str.boyerMooreSearch("ddt", "Hello data, dat"), false);
	ASSERT_EQ(test_str.boyerMooreSearch("make", "Hellomake data, dat"), true);
	ASSERT_EQ(test_str.boyerMooreSearch("data", "Hello daata, dat"), false);

}

int main(int args, char** argv){
	::testing::InitGoogleTest(&args, argv);
	return RUN_ALL_TESTS();
}