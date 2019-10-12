#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "Point.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

TEST(PointTests, TEST_EQUALS) {
    vector<double> p1Values{3, 4, 5, 6};
    Point p1(p1Values);

    vector<double> p2Values{3, 4, 5};
    Point p2(p2Values);

    ASSERT_NE(p1, p2);
}

TEST(PointTests, TEST_DISTANCE) {
    vector<double> p1Values{3, 4, 5, 6};
    vector<double> p2Values{3, 4, 5, 7};

    Point p1(p1Values);
    Point p2(p2Values);

    p1.setDistToQuery(p2);
    ASSERT_DOUBLE_EQ(p1.distToQuery, 1.0);
}

TEST(PointTests, TEST_VALUE_AT) {
    vector<double> p1Values{3, 4, 5, 6};
    Point p1(p1Values);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(p1.valueAt(i), p1Values[i]);
    }
}

TEST(PointTests, TEST_COMPARE) {
    vector<double> p1Values{3, 4, 5, 6};
    Point p1(p1Values);
    vector<double> p2Values{3, 4, 5, 2};
    Point p2(p1Values);
    vector<double> p3Values{3, 4, 5, 9};
    Point p3(p1Values);
    vector<double> p4Values{3, 4, 5, 1};
    Point p4(p1Values);

    vector<Point> vtr1;
    vtr1.push_back(p1);
    vtr1.push_back(p2);
    vtr1.push_back(p3);
    vtr1.push_back(p4);
    sort(vtr1.begin(), vtr1.end(), CompareValueAt(3));

    vector<Point> vtr2{p4, p2, p1, p3};

    EXPECT_EQ(vtr1, vtr2);
}

TEST(PointTests, TEST_OUTPUT) {
    vector<double> p1Values{3, 4, 5, 6};
    Point p1(p1Values);
    cout << p1 << endl;
    EXPECT_TRUE(1);
}

TEST(PointTests, TEST_NOT_EQUALS) {
    vector<double> p1Values{3, 4, 5, 6};
    Point p1(p1Values);

    vector<double> p2Values{3, 4, 5, 6};
    Point p2(p2Values);

    ASSERT_EQ(p1, p2);
}