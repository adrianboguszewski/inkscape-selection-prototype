#include "gtest/gtest.h"
#include "../src/Object.h"

class ObjectTest: public testing::Test {
public:
    ObjectTest() {
        object = new Object("parent");
        childOfChild = new Object("childOfChild");
        child = new Object("child");
        child2 = new Object("child2");
    }
    ~ObjectTest() {
        delete child2;
        delete childOfChild;
        delete child;
        delete object;
    }
    Object* object;
    Object* child;
    Object* childOfChild;
    Object* child2;
};

TEST_F(ObjectTest, AddChild) {
    EXPECT_EQ(0, object->getChildren().size());

    object->addChild(child);
    EXPECT_EQ(1, object->getChildren().size());
    EXPECT_EQ(child, &(object->getChildren().front()));
    EXPECT_EQ(object, child->getParent());
}

TEST_F(ObjectTest, IsDescendantOf) {
    object->addChild(child);
    child->addChild(childOfChild);
    object->addChild(child2);
    EXPECT_TRUE(child->isDescendantOf(object));
    EXPECT_TRUE(childOfChild->isDescendantOf(child));
    EXPECT_TRUE(childOfChild->isDescendantOf(object));
    EXPECT_TRUE(child2->isDescendantOf(object));
    EXPECT_FALSE(child->isDescendantOf(child2));
    EXPECT_FALSE(child2->isDescendantOf(child));
    EXPECT_FALSE(object->isDescendantOf(childOfChild));
    EXPECT_FALSE(object->isDescendantOf(child));
}
