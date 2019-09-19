#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include "set_stl.h"
namespace stl {
    TEST(SET, MakeDense) {
        CSet A(std::string("1111"));
        EXPECT_EQ(A, CSet::MakeDense(4));
    }
    TEST(SET, GETSET) {
        CSet s;
        s.AddElement(6);
        s.AddElement(4);
        CSet::iterator s_it = s.begin();
        ASSERT_EQ(*s_it, 4);
        s_it++;
        ASSERT_EQ(*s_it, 6);
    }
    TEST(SET, IsSubSet) {
        CSet A(std::string("0100"));
        CSet B(std::string("00"));
        EXPECT_TRUE(B.IsSubSet(A));
        B.AddElement(1);
        EXPECT_TRUE(B.IsSubSet(A));
        B.AddElement(0);
        EXPECT_FALSE(B.IsSubSet(A));
        A.AddElement(2);
        EXPECT_FALSE(A.IsSubSet(B));
    }
    TEST(SET, Operation) {
        CSet A(std::string("0101"));
        CSet B(std::string("0110"));
        CSet C(std::string("0111")); // A \cup B
        CSet D(std::string("0100")); // A \cap B

        CSet A_CUP_B = A.Union(B);
        EXPECT_EQ(A_CUP_B, C);
        CSet A_CAP_B = A.Intersection(B);
        EXPECT_EQ(A_CAP_B, D);
        EXPECT_TRUE(A != C);
        std::cout << A_CUP_B << std::endl;
    }
    TEST(SET, Complement) {
        CSet A(std::string("0101"));
        CSet B(std::string("1010"));
        CSet C(std::string("10101"));

        EXPECT_EQ(A.Complement(4), B);
        EXPECT_EQ(A.Complement(5), C);
    }

    TEST(SET, Difference) {
        CSet A(std::string("0101")); // {1, 3}
        CSet B(std::string("1010")); // {0, 2}
        CSet C(std::string("10101")); // {0, 2, 4}
        CSet D(std::string("0011")); // {2, 3}

        CSet A1 = A.Difference(B);
        EXPECT_EQ(A1, A);
        CSet B1 = C.Difference(B);
        EXPECT_EQ(B1, CSet(std::string("00001")));
        CSet C1 = D.Difference(A);
        EXPECT_EQ(C1, CSet(std::string("001")));
    }

    TEST(SET, TestLess) {
        CSet A(std::string("0111")); // {1, 2, 3}
        CSet B(std::string("01101")); // {1, 2, 4}
        CSet C(std::string("011"));
        CSet D(std::string("0101"));
        EXPECT_TRUE(A < B);
        EXPECT_FALSE(A < C);
        EXPECT_TRUE(A < D);
        EXPECT_FALSE(A < A);
    }

    TEST(SET, TestLargest) {
        CSet B(std::string("01101")); // {1, 2, 4}
        EXPECT_EQ(*B.rbegin(), 4);
    }

    TEST(SET, COPY) {
        CSet A;
        A.AddElement(1);
        A.AddElement(2);
        CSet B;
        std::copy(A.begin(), A.end(), std::back_inserter(B));
        EXPECT_EQ(A, B);
    }

    TEST(SET, Partition) {
        Partition a, b, c;
        a.AddElement(CSet(std::string("101")));
        a.AddElement(CSet(std::string("01")));
        b.AddElement(CSet(std::string("01")));
        b.AddElement(CSet(std::string("101")));
        EXPECT_EQ(a, b);
        c = c.expand(CSet());
        EXPECT_EQ(c.Cardinality(), 0);
        c = c.expand(CSet(std::string("1")));
        c = c.expand(CSet(std::string("01")));
        c = c.expand(CSet(std::string("101")));
        EXPECT_EQ(a, c);
    }

    TEST(SET, Constructor) {
        CSet A(3, 0b101);
        CSet B("101");
        EXPECT_EQ(A, B);
    }
}
namespace stl_new{

    // test constructor and iterator
    TEST(SET, iterator_test) {
        CSet s(3);
        ASSERT_FALSE(s.HasElement(0));
        ASSERT_FALSE(s.HasElement(1));
        s.AddElement(1);
        s.AddElement(2);
        CSet::const_iterator s_it = s.begin();
        ASSERT_EQ(*s_it, 1);
        s_it++;
        ASSERT_EQ(*s_it, 2);
        s_it++;
        ASSERT_EQ(s_it, s.end());
        s.clear();
        ASSERT_EQ(s.Cardinality(), 0);
    }

    TEST(SET, test_union) {
        CSet a1(3);
        CSet a2(3);
        a1.AddElement(1);
        a2.AddElement(1);
        a2.AddElement(2);
        a1.Union(a2);
        std::stringstream ss;
        ss << a1;
        ASSERT_EQ(ss.str(), "{1, 2}");
    }

    TEST(SET, make_dense) {
        CSet a(4, true);
        ASSERT_FALSE(a.IsEmpty());
        ASSERT_EQ(a.Cardinality(), 4);
        ASSERT_TRUE(a.HasElement(0));
        ASSERT_TRUE(a.HasElement(1));
        ASSERT_TRUE(a.HasElement(2));
        ASSERT_TRUE(a.HasElement(3));
    }

    TEST(SET, Intersection_Empty) {
        CSet a(3);
        CSet b(3);
        a.AddElement(1);
        b.AddElement(0);
        ASSERT_TRUE(a.Intersection_Empty(b));
        ASSERT_TRUE(b.Intersection_Empty(a));
        b.AddElement(1);
        ASSERT_FALSE(a.Intersection_Empty(b));
    }

    TEST(SET, output_format) {
        CSet a(3);
        a.AddElement(1);
        a.AddElement(2);
        std::stringstream ss;
        ss << a;
        ASSERT_EQ(ss.str(), "{1, 2}");
    }

    TEST(Partition, addElement) {
        Partition a;
        CSet s(2, true);
        a.AddElement(s);
        ASSERT_EQ(a.Cardinality(), 1);
        a.clear();
        ASSERT_EQ(a.Cardinality(), 0);
    }

    TEST(Partition, expand) {
        Partition a;
        CSet s(5);
        s.AddElement(1);
        a.expand(s);
        CSet s2(5);
        s2.AddElement(2);
        a.expand(s2);
        CSet s3(5);
        s3.AddElement(1);
        s3.AddElement(3);
        a.expand(s3);
        ASSERT_EQ(a.Cardinality(), 2);
        CSet s4(5);
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
        std::stringstream ss;
        ss << a;
        ASSERT_EQ(ss.str(), "{{2}, {1, 3, 4}}");
    }

    TEST(Partition, make_fine) {
        Partition a = Partition::makeFine(3);
        ASSERT_EQ(a.Cardinality(), 3);
    }
}