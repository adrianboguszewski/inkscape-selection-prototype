#include <gtest/gtest.h>
#include "../src/ObjectSet.h"

class ObjectSetTest: public testing::Test {
public:
    ObjectSetTest() {
        A = new Object("A");
        B = new Object("B");
        C = new Object("C");
        D = new Object("D");
        E = new Object("E");
        F = new Object("F");
        G = new Object("G");
        H = new Object("H");
        X = new Object("X");
    }
    ~ObjectSetTest() {
        delete X;
        delete H;
        delete G;
        delete F;
        delete E;
        delete D;
        delete C;
        delete B;
        delete A;
    }
    Object* A;
    Object* B;
    Object* C;
    Object* D;
    Object* E;
    Object* F;
    Object* G;
    Object* H;
    Object* X;
    ObjectSet set;
};

TEST_F(ObjectSetTest, Basics) {
    EXPECT_EQ(0, set.size());
    set.add(A);
    EXPECT_EQ(1, set.size());
    EXPECT_TRUE(set.contains(A));
    set.add(B);
    set.add(C);
    EXPECT_EQ(3, set.size());
    EXPECT_TRUE(set.contains(B));
    EXPECT_TRUE(set.contains(C));
    EXPECT_FALSE(set.contains(D));
    EXPECT_FALSE(set.contains(X));
    set.remove(A);
    EXPECT_EQ(2, set.size());
    EXPECT_FALSE(set.contains(A));
    set.clear();
    EXPECT_EQ(0, set.size());
}

TEST_F(ObjectSetTest, Autoremoving) {
    Object* Q = new Object("Q");
    set.add(Q);
    EXPECT_TRUE(set.contains(Q));
    EXPECT_EQ(1, set.size());
    delete Q;
    EXPECT_EQ(0, set.size());
}

TEST_F(ObjectSetTest, BasicDescendants) {
    A->addChild(B);
    B->addChild(C);
    set.add(B);
    EXPECT_TRUE(set.contains(B));
    set.add(C);
    EXPECT_FALSE(set.contains(C));
    EXPECT_EQ(1, set.size());
    set.add(A);
    EXPECT_EQ(1, set.size());
    EXPECT_TRUE(set.contains(A));
    EXPECT_FALSE(set.contains(B));
}

TEST_F(ObjectSetTest, AdvancedDescendants) {
    A->addChild(B);
    A->addChild(C);
    A->addChild(X);
    B->addChild(D);
    B->addChild(E);
    C->addChild(F);
    C->addChild(G);
    C->addChild(H);
    set.add(A);
    set.remove(F);
    EXPECT_EQ(4, set.size());
    EXPECT_FALSE(set.contains(F));
    EXPECT_TRUE(set.contains(B));
    EXPECT_TRUE(set.contains(G));
    EXPECT_TRUE(set.contains(H));
    EXPECT_TRUE(set.contains(X));
}
