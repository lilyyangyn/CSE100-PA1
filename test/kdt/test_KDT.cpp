#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "KDT.hpp"
#include "NaiveSearch.hpp"
#include "Point.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/**
 * A simple test fixture from which multiple tests can
 * be written. The structure of the KDT built from this
 * may vary. See test_BST.cpp for more information on
 * test fixtures.
 */
class SmallKDTFixture : public ::testing::Test {
  protected:
    vector<Point> vec;
    KDT kdt;

  public:
    SmallKDTFixture() {
        vec.emplace_back(Point({1.0, 3.2}));
        vec.emplace_back(Point({3.2, 1.0}));
        vec.emplace_back(Point({5.7, 3.2}));
        vec.emplace_back(Point({1.8, 1.9}));
        vec.emplace_back(Point({4.4, 2.2}));
        kdt.build(vec);
    }
};

TEST_F(SmallKDTFixture, TEST_SIZE) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt.size(), 5);
}

TEST_F(SmallKDTFixture, TEST_NEAREST_POINT) {
    NaiveSearch naiveSearch;
    naiveSearch.build(vec);
    Point queryPoint({5.81, 3.21});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    ASSERT_EQ(*kdt.findNearestNeighbor(queryPoint), *closestPoint);
}

/* Empty KDT starts here */
TEST(KDTTests, EMPTY_TREE_SIZE) {
    KDT kdt;
    EXPECT_EQ(kdt.size(), 0);
}

TEST(KDTTests, EMPTY_TREE_HEIGHT) {
    KDT kdt;
    EXPECT_EQ(kdt.height(), -1);
}

TEST(KDTTests, EMPTY_TREE_BUILD) {
    KDT kdt;
    vector<Point> points;
    kdt.build(points);
    EXPECT_EQ(kdt.height(), -1);
    EXPECT_EQ(kdt.size(), 0);
}

TEST(KDTTests, EMPTY_TREE_FIND_NN) {
    KDT kdt;
    Point queryPoint;
    // EXPECT_EQ(kdt.findNearestNeighbor(queryPoint), NULL);
}

TEST(KDTTests, EMPTY_TREE_RANGE_SEARCH) {
    KDT kdt;
    vector<pair<double, double>> queryRegion;
    pair<double, double> x = pair<double, double>(INT_MIN, INT_MAX);
    queryRegion.push_back(x);
    vector<Point> result = kdt.rangeSearch(queryRegion);
    EXPECT_TRUE(result.empty());
}

/* Small KDT starts here */
/**
 * the KDT looks like the below:
 *               (3.2, 1.0)
 *                /      \
 *        (1.0, 3.2)    (5.7, 3.2)
 *         /            /
 * (1.8, 1.9)       (4.4, 2.2)
 */
TEST_F(SmallKDTFixture, TEST_HEIGHT) { EXPECT_EQ(kdt.height(), 2); }

TEST_F(SmallKDTFixture, TEST_BUILD_ORDER) {
    vector<Point> inorder = kdt.inorder();
    ASSERT_EQ(inorder.size(), 5);
    EXPECT_EQ(inorder[0], Point({1.8, 1.9}));
    EXPECT_EQ(inorder[1], Point({1.0, 3.2}));
    EXPECT_EQ(inorder[2], Point({3.2, 1.0}));
    EXPECT_EQ(inorder[3], Point({4.4, 2.2}));
    EXPECT_EQ(inorder[4], Point({5.7, 3.2}));
}

TEST_F(SmallKDTFixture, TEST_RANGE_SEARCH) {
    vector<pair<double, double>> queryRegion;
    vector<Point> result = kdt.rangeSearch(queryRegion);
    EXPECT_TRUE(result.empty());

    queryRegion.push_back(pair<double, double>(0, 5));
    queryRegion.push_back(pair<double, double>(1.5, 4));
    result = kdt.rangeSearch(queryRegion);
    NaiveSearch naiveSearch;
    naiveSearch.build(vec);
    vector<Point> naiveResult = naiveSearch.rangeSearch(queryRegion);

    ASSERT_EQ(result.size(), naiveResult.size());

    sort(naiveResult.begin(), naiveResult.end(), CompareValueAt(0));
    EXPECT_EQ(result, naiveResult);
}