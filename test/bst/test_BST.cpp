#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}

// TODO: add more BST tests here

/* Empty BST test starts here */
TEST(BSTTests, EMPTY_TREE_SIZE_TEST) {
    // assert the empty BST has correct size
    BST<int> bst;
    EXPECT_EQ(bst.size(), 0);
}

TEST(BSTTests, EMPTY_TREE_EMPTY_TEST) {
    // assert the empty BST is empty
    BST<int> bst;
    EXPECT_TRUE(bst.empty());
}

TEST(BSTTests, EMPTY_TREE_FIND_TEST) {
    // assert no matching node is found in the empty BST
    BST<int> bst;
    EXPECT_EQ(bst.find(0), BSTIterator<int>(NULL));
}

TEST(BSTTests, Empty_TREE_ITERATE_THROUGH_TEST) {
    // assert the begin and end iterators in the small BST
    // are both zero
    BST<int> bst;
    EXPECT_EQ(bst.begin(), BSTIterator<int>(NULL));
    EXPECT_EQ(bst.end(), BSTIterator<int>(NULL));
}

/* Small BST test starts here */
TEST_F(SmallBSTFixture, SMALL_HEIGHT_TEST) {
    // assert that the small BST has the correct height
    EXPECT_EQ(bst.height(), 2);
    bst.insert(2);
    EXPECT_EQ(bst.height(), 2);
    bst.insert(25);
    EXPECT_EQ(bst.height(), 3);
}

TEST_F(SmallBSTFixture, SMALL_EMPTY_TEST) {
    // assert the small BST is not empty
    EXPECT_FALSE(bst.empty());
}

TEST_F(SmallBSTFixture, SMALL_FIND_TEST) {
    // assert the find function works well in the small BST
    EXPECT_EQ(*(bst.find(3)), 3);
    EXPECT_EQ(*(bst.find(-33)), -33);
    EXPECT_EQ(bst.find(0), BSTIterator<int>(NULL));
}

TEST_F(SmallBSTFixture, SMALL_ITERATE_THROUGH_TEST) {
    // assert the in-order traversal in the small BST
    // can be performed using iterator
    vector<int> itrVec;
    for (BST<int>::iterator itr = bst.begin(); itr != bst.end(); itr++) {
        itrVec.push_back(*(itr));
    }
    for (int i = bst.size() - 1; i > 0; i--) {
        EXPECT_GT(itrVec[i], itrVec[i - 1]);
    }
}

TEST_F(SmallBSTFixture, SMALL_INORDER_TEST) {
    // assert the small BST satisfies the property:
    // left descendants < current node < right descendants
    vector<int> inorderVec = bst.inorder();
    for (int i = bst.size() - 1; i > 0; i--) {
        EXPECT_GT(inorderVec[i], inorderVec[i - 1]);
    }
}

/* Test of destructor starts here */
TEST(BSTTests, DESTRUCTOR_TEST) {
    BST<int>* treePtr = new BST<int>();
    delete treePtr;

    treePtr = new BST<int>();
    vector<int> input{3, 4, 1, 100, -33};
    insertIntoBST(input, *treePtr);
    delete treePtr;

    EXPECT_TRUE(1);
}
