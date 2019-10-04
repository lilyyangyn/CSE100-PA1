#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
     *  Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** TODO */
    virtual ~BST() { deleteAll(root); }

    /** TODO */
    virtual bool insert(const Data& item) {
        // if null tree, insert the node to the root
        if (isize == 0) {
            // BSTNode<Data> p(item);
            this->root = new BSTNode<Data>(item);
            isize++;
            iheight++;
            return true;
        }
        // travel down the tree
        int level = 0;
        BSTNode<Data>* ptr = root;
        while (ptr != NULL) {
            level++;
            if (item < ptr->data) {
                if (ptr->left != NULL) {
                    ptr = ptr->left;
                } else {
                    break;
                }
            } else if (ptr->data < item) {
                if (ptr->right != NULL) {
                    ptr = ptr->right;
                } else {
                    break;
                }
            } else {
                // duplicated data, insertion fails
                return false;
            }
        }
        // insert item
        if (item < ptr->data) {
            ptr->left = new BSTNode<Data>(item);
            ptr->left->parent = ptr;
        } else if (ptr->data < item) {
            ptr->right = new BSTNode<Data>(item);
            ptr->right->parent = ptr;
        }
        // update isize and iheight
        isize++;
        if (level > iheight) {
            iheight++;
        }
        return true;
    }

    /** TODO */
    virtual iterator find(const Data& item) const {
        BSTNode<Data>* ptr = root;
        while (ptr != NULL) {
            if (ptr->data < item) {
                ptr = ptr->right;
            } else if (item < ptr->data) {
                ptr = ptr->left;
            } else {
                return BSTIterator<Data>(ptr);
            }
        }
        return BSTIterator<Data>(NULL);
    }

    /** TODO */
    unsigned int size() const { return isize; }

    /** TODO */
    int height() const { return iheight; }

    /** TODO */
    bool empty() const { return isize == 0; }

    /** TODO */
    iterator begin() const { return BST::iterator(first(root)); }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO */
    vector<Data> inorder() const {
        vector<Data> nodes;
        inorderTraversal(this->root, nodes);
        return nodes;
    }

  private:
    /** TODO */
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        if (root == NULL) {
            return 0;
        }
        BSTNode<Data>* ptr = root;
        while (ptr->left != NULL) {
            ptr = ptr->left;
        }
        return ptr;
    }

    /** TODO */
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
        if (n == NULL) {
            return;
        }
        deleteAll(n->left);
        deleteAll(n->right);
        delete n;
    }

    static void inorderTraversal(BSTNode<Data>* n, vector<Data>& nodes) {
        if (n == NULL) {
            return;
        }
        inorderTraversal(n->left, nodes);
        nodes.push_back(n->data);
        inorderTraversal(n->right, nodes);
    }
};

#endif  // BST_HPP
