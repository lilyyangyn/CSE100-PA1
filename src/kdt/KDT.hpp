#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>     // pow, abs
#include <algorithm>  // sort, max, min
#include <limits>     // numeric_limits<type>::max()
#include <vector>     // vector<typename>
#include "Point.hpp"

using namespace std;

class KDT {
  private:
    /** Inner class which defines a KD tree node */
    class KDNode {
      public:
        KDNode* left;
        KDNode* right;
        Point point;

        KDNode(Point point) : point(point) {}
    };

    // root of KD tree
    KDNode* root;

    // number of dimension of data points
    unsigned int numDim;

    // smallest squared distance to query point so far
    double threshold;

    unsigned int isize;
    int iheight;

    // current nearest neighbor
    Point nearestNeighbor;

    // Extra Credit: smallest bounding box containing all points
    vector<pair<double, double>> boundingBox;

    // Extra Credit: result container
    // (Set during searching, and clear before another search)
    vector<Point> pointsInRange;

  public:
    /** Constructor of KD tree */
    KDT()
        : root(0),
          numDim(0),
          threshold(numeric_limits<double>::max()),
          isize(0),
          iheight(-1) {}

    /** Destructor of KD tree */
    virtual ~KDT() { deleteAll(root); }

    /** TODO */
    void build(vector<Point>& points) {
        if (points.empty()) {
            root = 0;
            isize = 0;
            iheight = 0;
            return;
        }

        numDim = points[0].numDim;
        iheight = -1;
        root = buildSubtree(points, 0, points.size(), 0, -1);
        isize = points.size();
    }

    /** TODO */
    Point* findNearestNeighbor(Point& queryPoint) {
        if (isize == 0) {
            return nullptr;
        }

        KDNode* curr = root;
        KDNode* prev;
        unsigned dim = 0;

        while (curr != nullptr) {
            prev = curr;
            if (queryPoint.valueAt(dim) < curr->point.valueAt(dim)) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
            dim = (dim + 1) % numDim;
        }

        prev->point.setDistToQuery(queryPoint);
        nearestNeighbor = prev->point;
        threshold = prev->point.distToQuery;

        findNNHelper(root, queryPoint, 0);

        return &nearestNeighbor;
    }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
    }

    /** TODO */
    unsigned int size() const { return isize; }

    /** TODO */
    int height() const { return iheight; }

  private:
    /** TODO */
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        if (start >= end) {
            return nullptr;
        }

        iheight = (iheight < height + 1) ? height + 1 : iheight;

        sort(points.begin(), points.end(), CompareValueAt(curDim));
        unsigned int median = floor((start + end) / 2);
        unsigned int nextDim = (curDim + 1) % numDim;

        KDNode* curNode = new KDNode(points[median]);
        curNode->left =
            buildSubtree(points, start, median, nextDim, height + 1);
        curNode->right =
            buildSubtree(points, median + 1, end, nextDim, height + 1);
        return curNode;
    }

    /** TODO */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
        if (node == nullptr) {
            return;
        }

        unsigned int nextDim = (curDim + 1) % numDim;
        if (queryPoint.valueAt(curDim) < node->point.valueAt(curDim)) {
            findNNHelper(node->left, queryPoint, nextDim);
            if (pow(node->point.valueAt(curDim) - queryPoint.valueAt(curDim),
                    2.0) <= threshold) {
                findNNHelper(node->right, queryPoint, nextDim);
            }
        } else {
            findNNHelper(node->right, queryPoint, nextDim);
            if (pow(queryPoint.valueAt(curDim) - node->point.valueAt(curDim),
                    2.0) <= threshold) {
                findNNHelper(node->left, queryPoint, nextDim);
            }
        }

        node->point.setDistToQuery(queryPoint);
        if (node->point.distToQuery < threshold) {
            nearestNeighbor = node->point;
            threshold = node->point.distToQuery;
        }
    }

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    /** TODO */
    static void deleteAll(KDNode* n) {
        if (n == nullptr) {
            return;
        }
        deleteAll(n->left);
        deleteAll(n->right);
        delete n;
    }

    // Add your own helper methods here
};
#endif  // KDT_HPP
