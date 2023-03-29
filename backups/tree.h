#ifndef TREE_H
#define TREE_H

#include "treeNode.h"
#include <iostream>
#include <string>


class Tree {
private:
    TreeNode* root;             // Pointer to the root node

    // ~~ InorderTreeWalk() Description ~~
    // Traverses the left subtree of a node,
    // then the node itself, finally the right subtree.
    string InorderTreeWalk(TreeNode* node) {
        std::string str = "";
        if (node != nullptr) {
            str += InorderTreeWalk((*node).GetLeft());
            str += std::to_string((*node).GetValue()) + " ";
            str += InorderTreeWalk((*node).GetRight());
        }
        return str;
    }

    // ~~ PreorderTreeWalk() Description ~~
    // Traverses the node first, then the left
    // subtree, and finally the right subtree.
    string PreorderTreeWalk(TreeNode* node) {
        std::string str = "";
        if (node != nullptr) {
            str += std::to_string((*node).GetValue()) + " ";
            str += PreorderTreeWalk((*node).GetLeft());
            str += PreorderTreeWalk((*node).GetRight());
        }
        return str;
    }

    // ~~ PostorderTreeWalk() Description ~~
    // Traverses the left subtree first, then the
    // right subtree, and finally the node.
    string PostorderTreeWalk(TreeNode* node) {
        std::string str = "";
        if (node != nullptr) {
            str += PostorderTreeWalk((*node).GetLeft());
            str += PostorderTreeWalk((*node).GetRight());
            str += std::to_string((*node).GetValue()) + " ";
        }
        return str;
    }

    //According to the slides: RotateLeft() will be the opposite of RotateRight() no real fancy differences (thankfully)
    void RotateLeft(TreeNode* x) {


        // Store the right child of node in y
        TreeNode* y = (*x).GetRight();

        // Set the left child of y as the right child of node
        (*x).SetRight((*y).GetLeft());
        if ((*y).GetLeft()) {
            (*y).GetLeft()->SetParent(x);
        }
        // Set the parent of y as the parent of node
        (*y).SetParent((*x).GetParent());
        // If node is the root of the tree, set y as the new root
        if (!(*x).GetParent()) {
            root = y;
        }
        // If node is the left child of its parent, set y as the new left child of the parent
        else if (x == (*x).GetParent()->GetLeft()) {
            (*x).GetParent()->SetLeft(y);
        }
        // If node is the right child of its parent, set y as the new right child of the parent
        else {
            (*x).GetParent()->SetRight(y);
        }
        //Set node as the left child of y
        (*y).SetLeft(x);
        // Set the parent of node as y
        (*x).SetParent(y);
        //Finished our left rotation :)
    }

    //According to slides rotateRig
    void RotateRight(TreeNode* x) {
        // Store the right child of node in y
        TreeNode* y = (*x).GetLeft();
        // Set the left child of y as the right child of node
        (*x).SetLeft((*y).GetRight());
        if ((*y).GetRight()) {
            (*y).GetRight()->SetParent(x);
        }
        // Set the parent of y as the parent of node
        (*y).SetParent((*x).GetParent());
        // If node is the root of the tree, set y as the new root
        if (!(*x).GetParent()) {
            root = y;
        }
        // If node is the left child of its parent, set y as the new left child of the parent
        else if (x == (*x).GetParent()->GetRight()) {
            (*x).GetParent()->SetRight(y);
        }
        // If node is the right child of its parent, set y as the new right child of the parent
        else {
            (*x).GetParent()->SetLeft(y);
        }
        // Set node as the left child of y
        (*y).SetRight(x);
        // Set the parent of node as y
        (*x).SetParent(y);
    }

    void InsertFixup(TreeNode* z) {
        TreeNode* y;
        while (z->GetParent()->GetColor() == false) {
            if (z->GetParent() == z->GetParent()->GetParent()->GetLeft()) {
                y = z->GetParent()->GetParent()->GetRight();
                if (y->GetColor() == false) {
                    z->GetParent()->SetColor(true);
                    y->SetColor(true);
                    z->GetParent()->GetParent()->SetColor(false);
                    z = z->GetParent()->GetParent();
                }
                else {
                    if (z == z->GetParent()->GetRight()) {
                        z = z->GetParent();
                        RotateLeft(z);
                    }
                    z->GetParent()->SetColor(true);
                    z->GetParent()->GetParent()->SetColor(false);
                    RotateRight(z->GetParent()->GetParent());
                }
            }
            else {
                y = z->GetParent()->GetParent()->GetLeft();
                if (y->GetColor() == false) {
                    z->GetParent()->SetColor(true);
                    y->SetColor(true);
                    z->GetParent()->GetParent()->SetColor(false);
                    z = z->GetParent()->GetParent();
                }
                else {
                    if (z == z->GetParent()->GetLeft()) {
                        z = z->GetParent();
                        RotateRight(z);
                    }
                    z->GetParent()->SetColor(true);
                    z->GetParent()->GetParent()->SetColor(false);
                    RotateLeft(z->GetParent()->GetParent());
                }
            }
        }

        root->SetColor(true);

        /*
        // Continue fixing the tree until the parent of 'traversalNode' is black or 'traversalNode' is the root
        while ((*traversalNode).GetParent() != nullptr && (*traversalNode).GetParent()->GetColor() == false) {
            // traversalNode's parent is a left child
            if ((*traversalNode).GetParent() == (*traversalNode).GetParent()->GetParent()->GetLeft()) {
                TreeNode* y = (*traversalNode).GetParent()->GetParent()->GetRight();  // y is traversalNode's uncle
                // Case 1: traversalNode's uncle is red
                if (y != nullptr && (*y).GetColor() == false) {
                    (*traversalNode).GetParent()->SetColor(true);                     // Change parent color to black
                    (*y).SetColor(true);                                  // Change uncle color to black
                    (*traversalNode).GetParent()->GetParent()->SetColor(false);       // Change grandparent color to red
                    traversalNode = (*traversalNode).GetParent()->GetParent();                    // Set traversalNode to its grandparent and continue fixing
                }
                // Case 2: traversalNode's uncle is black
                else {
                    // traversalNode is a right child
                    if (traversalNode == (*traversalNode).GetParent()->GetRight()) {
                        traversalNode = (*traversalNode).GetParent();                             // Set traversalNode to its parent
                        RotateLeft(traversalNode);                                  // Rotate left about traversalNode
                    }
                    // Case 3: traversalNode's uncle is black and traversalNode is a left child
                    (*traversalNode).GetParent()->SetColor(true);                     // Change parent color to black
                    (*traversalNode).GetParent()->GetParent()->SetColor(false);       // Change grandparent color to red
                    RotateRight((*traversalNode).GetParent()->GetParent());
                }
            }
            // Check on opposites
            else {
                TreeNode* y = (*traversalNode).GetParent()->GetParent()->GetLeft();
                if (y != nullptr && (*y).GetColor() == false) {
                    (*traversalNode).GetParent()->SetColor(true);
                    (*y).SetColor(true);
                    (*traversalNode).GetParent()->GetParent()->SetColor(false);
                    traversalNode = (*traversalNode).GetParent()->GetParent();
                }
                else {
                    if (traversalNode == (*traversalNode).GetParent()->GetLeft()) {
                        traversalNode = (*traversalNode).GetParent();
                        RotateRight(traversalNode);
                    }
                    (*traversalNode).GetParent()->SetColor(true);
                    (*traversalNode).GetParent()->GetParent()->SetColor(false);
                    RotateLeft((*traversalNode).GetParent()->GetParent());
                }
            }
        }
        // The root of the tree will ALWAYS be black
        (*root).SetColor(true);*/
    }

    void Transplant(TreeNode* u, TreeNode* v) {
        // Pseudocode from the book
        // Where u is the root of T
        if ((*u).GetParent() == nullptr) {
            root = v;
        }
        // Otherwise u is either a left child of parent
        else if (u == (*u).GetParent()->GetLeft()) {
            (*u).GetParent()->SetLeft(v);
        }
        // Or right child of parent
        else {
            (*u).GetParent()->SetRight(v);
        }
        // Could possibly be null too
        if (v != nullptr) {
            (*v).SetParent((*u).GetParent());
        }
    }

    TreeNode* Minimum(TreeNode* node) {
        while ((*node).GetLeft() != nullptr) {
            node = (*node).GetLeft();
        }
        return node;
    }

    void DeleteFixup(TreeNode* x) {
        // w is a pointer to the sibling of x
        TreeNode* w;

        while (x != root && (*x).GetColor() == true && x) {
            // is x a left child?
            if (x == (*x).GetParent()->GetLeft()) {
                w = (*x).GetParent()->GetRight();
                if ((*w).GetColor() == false) {
                    (*w).SetColor(true);
                    (*x).GetParent()->SetColor(false);
                    RotateLeft((*x).GetParent());
                    w = (*x).GetParent()->GetRight();
                }
                if ((*w).GetLeft()->GetColor() == true && (*w).GetRight()->GetColor() == true) {
                    (*w).SetColor(false);
                    x = (*x).GetParent();
                }
                else {
                    if (w->GetRight()->GetColor() == true) {
                        w->GetLeft()->SetColor(true);
                        w->SetColor(false);
                        RotateRight(w);
                        w = (*x).GetParent()->GetRight();
                    }
                    w->SetColor(x->GetParent()->GetColor());
                    x->GetParent()->SetColor(true);
                    w->GetRight()->SetColor(true);
                    RotateLeft(x->GetParent());
                    x = root;
                }
            }
            else {
                w = (*x).GetParent()->GetLeft();
                if ((*w).GetColor() == false) {
                    (*w).SetColor(true);
                    (*x).GetParent()->SetColor(false);
                    RotateRight((*x).GetParent());
                    w = (*x).GetParent()->GetLeft();
                }
                if ((*w).GetRight()->GetColor() == true && (*w).GetLeft()->GetColor() == true) {
                    (*w).SetColor(false);
                    x = (*x).GetParent();
                }
                else {
                    if (w->GetLeft()->GetColor() == true) {
                        w->GetRight()->SetColor(true);
                        w->SetColor(false);
                        RotateLeft(w);
                        w = (*x).GetParent()->GetLeft();
                    }
                    w->SetColor(x->GetParent()->GetColor());
                    x->GetParent()->SetColor(true);
                    w->GetLeft()->SetColor(true);
                    RotateRight(x->GetParent());
                    x = root;
                }
            }
        }
        if (x) {
            (*x).SetColor(true);
        }
        else {
            return;
        }

        
    }
public:
    // When created, a tree should be empty where the root is NULL
    Tree() {
        root = nullptr;
    }
    // When destroyed, a tree should be emptied where each node is deleted.
    ~Tree() {
        while (!root) {
            RemoveNode((*root).GetValue());
        }
    }

    // Return the root of the tree
    TreeNode* GetRoot() {
        return root;
    }

    void AddValue(int value) {
        TreeNode* z = new TreeNode(value);
        TreeNode* x = root;
        TreeNode* y = nullptr;

        while (x) {
            y = x;
            if (z->GetValue() < x->GetValue()) {
                x = x->GetLeft();
            }
            else {
                x = x->GetRight();
            }
        }
        z->SetParent(y);
        if (!y) {
            root = z;                           // Tree T was empty (null)
        }
        else if (z->GetValue() < y->GetValue()) {
            y->SetLeft(z);
        }
        else {
            y->SetRight(z);
        }
        z->SetLeft(nullptr);
        z->SetRight(nullptr);
        z->SetColor(false);
        InsertFixup(z);

        /*
        // traversalNode will be the placeholder node that we... well traverse over
        TreeNode* traversalNode = new TreeNode(value);

        // Traverse the tree to find the correct position for the new node
        TreeNode* y = nullptr;
        TreeNode* node = root;
        while (node != nullptr) {
            y = node;
            // if the new value is less than the current node's value
            if ((*traversalNode).GetValue() < (*node).GetValue()) {
                node = (*node).GetLeft(); // move to the left child
            }
            else {
                node = (*node).GetRight(); // move to the right child
            }
        }
        (*traversalNode).SetParent(y);    // Set the new node's parent to the last node visited in the above loop
        // Insert the new node as a child of the last node visited
        // If the tree was empty, make the new node the root
        if (y == nullptr) {
            root = traversalNode;
        }
        else if ((*traversalNode).GetValue() < (*y).GetValue()) {
            (*y).SetLeft(traversalNode);  // If the new value is less than parent's value, make it left child
        }
        else {
            (*y).SetRight(traversalNode); // If the new value is greater than or equal to the parent, make it right child
        }
        // wash
        (*traversalNode).SetLeft(nullptr);
        (*traversalNode).SetRight(nullptr);
        (*traversalNode).SetColor(false);

        // perform necessary rotations and color adjustments to keep red-black tree
        InsertFixup(traversalNode);*/
    }

    TreeNode* GetNode(int value) {
        TreeNode* node = root;
        while (node != nullptr) {
            if (value == (*node).GetValue()) {
                return node;
            }
            else if (value < (*node).GetValue()) {
                node = (*node).GetLeft();
            }
            else {
                node = (*node).GetRight();
            }
        }
        return nullptr;
    }



    void RemoveNode(int value) {
        
        TreeNode* z = GetNode(value);
        TreeNode* y = z;
        bool yOrigColor = y->GetColor();
        TreeNode* x;

        if (z->GetLeft() == nullptr) {
            x = z->GetRight();
            Transplant(z, x);
        }
        else if (z->GetRight() == nullptr) {
            x = z->GetLeft();
            Transplant(z, x);
        }
        else {
            y = Minimum(z->GetRight());
            yOrigColor = y->GetColor();
            x = y->GetRight();
            if (y != z->GetRight()) {
                Transplant(y, x);
                y->SetRight(z->GetRight());
                y->GetRight()->SetParent(y);
            }
            else {
                x->SetParent(y);
                Transplant(z, y);
                y->SetLeft(z->GetLeft());
                y->GetLeft()->SetParent(y);
                y->SetColor(z->GetColor());
            }
        }

        if (yOrigColor == true) {
            DeleteFixup(x);
        }
    }

    


    void PrintTreeWalk(int orderNumber) {
        std::string ret = "";
        switch (orderNumber) {
        case 1:
            ret = InorderTreeWalk(root);
            break;
        case 2:
            ret += PreorderTreeWalk(root);
            break;
        case 3:
            ret += PostorderTreeWalk(root);
            break;
        default:
            break;
        }
        if (ret.size() > 1)
            ret.erase(ret.size() - 1);
        cout << ret;
    }
};

#endif
