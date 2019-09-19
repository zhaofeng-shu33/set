#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include "set_stl.h"

using Set = stl::CSet;
using Partition = stl::Partition;

// test constructor and iterator
TEST(SET, iterator_test) {
    Set s(3);
    ASSERT_FALSE(s.HasElement(0));
    ASSERT_FALSE(s.HasElement(1));
    s.AddElement(1);
    s.AddElement(2);
    Set::const_iterator s_it = s.begin();
    ASSERT_EQ(*s_it, 1);
    s_it++;
    ASSERT_EQ(*s_it, 2);
    s_it++;
    ASSERT_EQ(s_it, s.end());
}

TEST(SET, make_dense) {
    Set a(4, true);
    ASSERT_FALSE(a.IsEmpty());
    ASSERT_EQ(a.Cardinality(), 4);
    ASSERT_TRUE(a.HasElement(0));
    ASSERT_TRUE(a.HasElement(1));
    ASSERT_TRUE(a.HasElement(2));
    ASSERT_TRUE(a.HasElement(3));
}

TEST(SET, Intersection_Empty) {
    Set a(3);
    Set b(3);
    a.AddElement(1);
    b.AddElement(0);
    ASSERT_TRUE(a.Intersection_Empty(b));
    ASSERT_TRUE(b.Intersection_Empty(a));
    b.AddElement(1);
    ASSERT_FALSE(a.Intersection_Empty(b));
}

TEST(SET, output_format) {
    Set a(3);
    a.AddElement(1);
    a.AddElement(2);
    std::stringstream ss;
    ss << a;
    ASSERT_EQ(ss.str(), "{1, 2}");
}

TEST(Partition, addElement) {
    Partition a;
    Set s(2, true);
    a.AddElement(s);
    ASSERT_EQ(a.Cardinality(), 1);
    a.clear();
    ASSERT_EQ(a.Cardinality(), 0);
}

TEST(Partition, expand) {
    Partition a;
    Set s(5);
    s.AddElement(1);
    a.expand(s);
    Set s2(5);
    s2.AddElement(2);
    a.expand(s2);
    Set s3(5);
    s3.AddElement(1);
    s3.AddElement(3);
    a.expand(s3);
    ASSERT_EQ(a.Cardinality(), 2);
    Set s4(5);
    s4.AddElement(3);
    s4.AddElement(4);
    a.expand(s4);
    ASSERT_EQ(a.Cardinality(), 2);
    Partition::const_iterator it = a.begin();
    ASSERT_TRUE(it->HasElement(2));
    it++;
    ASSERT_TRUE(it->HasElement(1));
    ASSERT_TRUE(it->HasElement(3));
    ASSERT_TRUE(it->HasElement(4));
    it++;
    ASSERT_EQ(it, a.end());
}

TEST(Partition, make_fine) {
    Partition a = Partition::makeFine(3);
    ASSERT_EQ(a.Cardinality(), 3);
}
