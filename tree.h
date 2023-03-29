#ifndef TREE_H
#define TREE_H

#include "treeNode.h"
#include <iostream>
#include <string>


class Tree {
private:
    
    TreeNode* nil = new TreeNode();
    TreeNode* root = nil;             // Pointer to the root node

    // ~~ InorderTreeWalk() Description ~~
    // Traverses the left subtree of a node,
    // then the node itself, finally the right subtree.
    string InorderTreeWalk(TreeNode* node) {
        std::string str = "";
        if (node != nil && node != NULL) {
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
        if (node != nil && node != NULL) {
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
        if (node != nil) {
            str += PostorderTreeWalk((*node).GetLeft());
            str += PostorderTreeWalk((*node).GetRight());
            str += std::to_string((*node).GetValue()) + " ";
        }
        return str;
    }

    //According to the slides: RotateLeft() will be the opposite of RotateRight() no real fancy differences (thankfully)
    void RotateLeft(TreeNode* node) {
        // Store the right child of node in y
        TreeNode* y = (*node).GetRight();
        // Set the left child of y as the right child of node
        (*node).SetRight((*y).GetLeft());
        if ((*y).GetLeft() != nil) {
            (*y).GetLeft()->SetParent(node);
        }
        // Set the parent of y as the parent of node
        (*y).SetParent((*node).GetParent());
        // If node is the root of the tree, set y as the new root
        if ((*node).GetParent() == nil) {
            root = y;
        }
        // If node is the left child of its parent, set y as the new left child of the parent
        else if (node == (*node).GetParent()->GetLeft()) {
            (*node).GetParent()->SetLeft(y);
        }
        // If node is the right child of its parent, set y as the new right child of the parent
        else {
            (*node).GetParent()->SetRight(y);
        }
        //Set node as the left child of y
        (*y).SetLeft(node);
        // Set the parent of node as y
        (*node).SetParent(y);
        //Finished our left rotation :)
    }

    //According to slides rotateRig
    void RotateRight(TreeNode* node) {
        // Store the right child of node in y
        TreeNode* y = (*node).GetLeft();
        // Set the left child of y as the right child of node
        (*node).SetLeft((*y).GetRight());
        if ((*y).GetRight() != nil) {
            (*y).GetRight()->SetParent(node);
        }
        // Set the parent of y as the parent of node
        (*y).SetParent((*node).GetParent());
        // If node is the root of the tree, set y as the new root
        if ((*node).GetParent() == nil) {
            root = y;
        }
        // If node is the left child of its parent, set y as the new left child of the parent
        else if (node == (*node).GetParent()->GetRight()) {
            (*node).GetParent()->SetRight(y);
        }
        // If node is the right child of its parent, set y as the new right child of the parent
        else {
            (*node).GetParent()->SetLeft(y);
        }
        // Set node as the left child of y
        (*y).SetRight(node);
        // Set the parent of node as y
        (*node).SetParent(y);
    }

    void InsertFixup(TreeNode* z) {
        // Continue fixing the tree until the parent of 'z' is black or 'z' is the root
        while ((*z).GetParent()->GetColor() == false) {
            // z's parent is a left child
            if ((*z).GetParent() == (*z).GetParent()->GetParent()->GetLeft()) {
                TreeNode* y = (*z).GetParent()->GetParent()->GetRight();  // y is z's uncle
                // Case 1: z's uncle is red
                if ((*y).GetColor() == false) {
                    (*z).GetParent()->SetColor(true);                     // Change parent color to black
                    (*y).SetColor(true);                                  // Change uncle color to black
                    (*z).GetParent()->GetParent()->SetColor(false);       // Change grandparent color to red
                    z = (*z).GetParent()->GetParent();                    // Set z to its grandparent and continue fixing
                }
                // Case 2: z's uncle is black
                else {
                    // z is a right child
                    if (z == (*z).GetParent()->GetRight()) {
                        z = (*z).GetParent();                             // Set z to its parent
                        RotateLeft(z);                                  // Rotate left about z
                    }
                    // Case 3: z's uncle is black and z is a left child
                    (*z).GetParent()->SetColor(true);                     // Change parent color to black
                    (*z).GetParent()->GetParent()->SetColor(false);       // Change grandparent color to red
                    RotateRight((*z).GetParent()->GetParent());
                }
            }
            // Check on opposites
            else {
                TreeNode* y = (*z).GetParent()->GetParent()->GetLeft();
                if ((*y).GetColor() == false) {
                    (*z).GetParent()->SetColor(true);
                    (*y).SetColor(true);
                    (*z).GetParent()->GetParent()->SetColor(false);
                    z = (*z).GetParent()->GetParent();
                }
                else {
                    if (z == (*z).GetParent()->GetLeft()) {
                        z = (*z).GetParent();
                        RotateRight(z);
                    }
                    (*z).GetParent()->SetColor(true);
                    (*z).GetParent()->GetParent()->SetColor(false);
                    RotateLeft((*z).GetParent()->GetParent());
                }
            }
        }
        // The root of the tree will ALWAYS be black
        (*root).SetColor(true);
    }

    void Transplant(TreeNode* u, TreeNode* v) {
        // Pseudocode from the book
        // Where u is the root of T
        if ((*u).GetParent() == nil || (*u).GetParent() == NULL) {
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
         (*v).SetParent((*u).GetParent());
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


        while (x != root && (*x).GetColor() == true) {
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
         (*x).SetColor(true);


    }
public:
    // When created, a tree should be empty where the root is NULL
    Tree() {
    }

    ~Tree() {}

    // Return the root of the tree
    TreeNode* GetRoot() {
        if (root == nil) return NULL;
        else return root;
    }

    void AddValue(int value) {
        // traversalNode will be the placeholder node that we... well traverse over
        TreeNode* z = new TreeNode(value);

        TreeNode* x = root;
        TreeNode* y = nil;
        
        while (x != nil && x != NULL) {
            y = x;
            // if the new value is less than the current x's value
            if ((*z).GetValue() < (*x).GetValue()) {
                x = (*x).GetLeft(); // move to the left child
            }
            else {
                x = (*x).GetRight(); // move to the right child
            }
        }
        (*z).SetParent(y);    // Set the new x's parent to the last x visited in the above loop
        // Insert the new x as a child of the last x visited
        // If the tree was empty, make the new x the root
        if (y == nil || y == NULL) {
            root = z;
        }
        else if ((*z).GetValue() < (*y).GetValue()) {
            (*y).SetLeft(z);  // If the new value is less than parent's value, make it left child
        }
        else {
            (*y).SetRight(z); // If the new value is greater than or equal to the parent, make it right child
        }
        // wash
        (*z).SetLeft(nil);
        (*z).SetRight(nil);
        (*z).SetColor(false);

        // perform necessary rotations and color adjustments to keep red-black tree
        InsertFixup(z);
    }

    TreeNode* GetNode(int value) {
        TreeNode* node = root;
        while (node != nil && node != NULL) {
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
        return NULL;
    }



    void RemoveNode(int value) {

        

        // Find the node to remove
        TreeNode* z = GetNode(value);
        TreeNode* y = z;
        TreeNode* x;

        // If the root is nil
        if (root == nil || z == nullptr) {
            return;
        }

        // Keep the original color of y for comparison
        bool yOriginalColor = (*y).GetColor();

        // z has max 1 child available
        if ((*z).GetLeft() == nil || (*z).GetLeft() == NULL) {
            x = (*z).GetRight();
            Transplant(z, (*z).GetRight());
        }
        else if ((*z).GetRight() == nil || (*z).GetLeft() == NULL) {
            x = (*z).GetLeft();
            Transplant(z, (*z).GetLeft());
        }
        else {
            y = Minimum((*z).GetRight());
            yOriginalColor = (*y).GetColor();
            x = (*y).GetRight();
            if (y != z->GetRight()) {
                Transplant(y, y->GetRight());
                y->SetRight(z->GetRight());
                y->GetRight()->SetParent(y);
            }
            else {
                x->SetParent(y);
            }
            Transplant(z, y);
            (*y).SetLeft((*z).GetLeft());
            (*y).GetLeft()->SetParent(y);
            (*y).SetColor((*z).GetColor());
        }
        if (yOriginalColor == true) {
            DeleteFixup(x);
        }

        delete z;
    }




    void PrintTreeWalk(int orderNumber) {
        std::string ret = "";
        switch (orderNumber) {
        case 1:
            ret = InorderTreeWalk(root);
            if (ret.size() > 1)
                ret.erase(ret.size() - 1);
            cout << ret;
            break;
        case 2:
            ret += PreorderTreeWalk(root);
            if (ret.size() > 1)
                ret.erase(ret.size() - 1);
            cout << ret;
            break;
        case 3:
            ret += PostorderTreeWalk(root);
            if (ret.size() > 1)
                ret.erase(ret.size() - 1);
            cout << ret;
            break;
        default:
            break;
        }

    }
};

#endif