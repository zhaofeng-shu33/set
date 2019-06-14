#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include "set_stl.h"

using Set = stl::CSet;
using Partition = stl::Partition;

TEST(SET, GETSET) {
    Set s;
    s.AddElement(6);
    s.AddElement(4);
    Set::iterator s_it = s.begin();
    ASSERT_EQ(*s_it, 4);
    s_it++;
    ASSERT_EQ(*s_it, 6);
}
TEST(SET, IsSubSet) {
    Set A(std::string("0100"));
    Set B(std::string("00"));
    EXPECT_TRUE(B.IsSubSet(A));
    B.AddElement(1);
    EXPECT_TRUE(B.IsSubSet(A));
    B.AddElement(0);
    EXPECT_FALSE(B.IsSubSet(A));
    A.AddElement(2);
    EXPECT_FALSE(A.IsSubSet(B));
}
TEST(SET, Operation) {
    Set A(std::string("0101"));
    Set B(std::string("0110"));
    Set C(std::string("0111")); // A \cup B
    Set D(std::string("0100")); // A \cap B

    Set A_CUP_B = A.Union(B);
    EXPECT_EQ(A_CUP_B, C);
    Set A_CAP_B = A.Intersection(B);
    EXPECT_EQ(A_CAP_B, D);
    EXPECT_TRUE(A != C);
    std::cout << A_CUP_B << std::endl;
}
TEST(SET, Complement) {
    Set A(std::string("0101"));
    Set B(std::string("1010"));
    Set C(std::string("10101"));

    EXPECT_EQ(A.Complement(4), B);
    EXPECT_EQ(A.Complement(5), C);
}

TEST(SET, TestLess) {
    Set A(std::string("0111")); // {1, 2, 3}
    Set B(std::string("01101")); // {1, 2, 4}
    Set C(std::string("011"));
    Set D(std::string("0101"));
    EXPECT_TRUE(A < B);
    EXPECT_FALSE(A < C);
    EXPECT_TRUE(A < D);
    EXPECT_FALSE(A < A);
}

TEST(SET, TestLargest) {
	Set B(std::string("01101")); // {1, 2, 4}
	EXPECT_EQ(*B.rbegin(), 4);
}

TEST(SET, COPY) {
	Set A;
	A.AddElement(1);
	A.AddElement(2);
	Set B;
	std::copy(A.begin(), A.end(), std::back_inserter(B));
	EXPECT_EQ(A, B);
}

TEST(SET, Partition) {
	Partition a, b, c;
	a.AddElement(stl::CSet(std::string("101")));
	a.AddElement(stl::CSet(std::string("01")));
	b.AddElement(stl::CSet(std::string("01")));
	b.AddElement(stl::CSet(std::string("101")));
	EXPECT_EQ(a, b);
	c = c.expand(stl::CSet());
	EXPECT_EQ(c.Cardinality(), 0);
	c = c.expand(stl::CSet(std::string("1")));
	c = c.expand(stl::CSet(std::string("01")));
	c = c.expand(stl::CSet(std::string("101")));
	EXPECT_EQ(a, c);
}
