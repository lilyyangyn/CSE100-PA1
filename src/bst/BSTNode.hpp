#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

template <typename Data>

class BSTNode {
  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;
    Data const data;  // the const Data in this node.

    /** TODO */
    BSTNode(const Data& d) : data(d), left(NULL), right(NULL), parent(NULL) {}

    /** TODO */
    BSTNode<Data>* successor() {
        BSTNode<Data>* ptr = this;
        if (right != NULL) {
            // find first left-branch descendant in the right descendants
            ptr = ptr->right;
            while (ptr->left != NULL) {
                ptr = ptr->left;
            }
            return ptr;
        } else {
            // find first acestor with a left child
            while (ptr->parent != NULL) {
                if (ptr == ptr->parent->left) {
                    ptr = ptr->parent;
                    return ptr;
                }
                ptr = ptr->parent;
            }
        }
        return 0;
    }
};

/** DO NOT CHANGE THIS METHOD
 *  Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
