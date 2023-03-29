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
    void RotateLeft(TreeNode* node) {
        // Store the right child of node in y
        TreeNode* y = (*node).GetRight();
        // Set the left child of y as the right child of node
        (*node).SetRight((*y).GetLeft());
        if ((*y).GetLeft() != nullptr) {
            (*y).GetLeft()->SetParent(node);
        }
        // Set the parent of y as the parent of node
        (*y).SetParent((*node).GetParent());
        // If node is the root of the tree, set y as the new root
        if ((*node).GetParent() == nullptr) {
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
        if ((*y).GetRight() != nullptr) {
            (*y).GetRight()->SetParent(node);
        }
        // Set the parent of y as the parent of node
        (*y).SetParent((*node).GetParent());
        // If node is the root of the tree, set y as the new root
        if ((*node).GetParent() == nullptr) {
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

    void InsertFixup(TreeNode* traversalNode) {
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
        (*root).SetColor(true);
    }

    void Transplant(TreeNode* first, TreeNode* second) {
        // Switch two nodes around
        if ((*first).GetParent() == nullptr) {
            root = second;
        }
        else if (first == (*second).GetParent()->GetLeft()) {
            (*first).GetParent()->SetLeft(second);
        }
        else {
            (*first).GetParent()->SetRight(second);
        }
        if (second != nullptr) {
            (*second).SetParent((*first).GetParent());
        }
    }

    TreeNode* Minimum(TreeNode* node) {
        while ((*node).GetLeft() != nullptr) {
            node = (*node).GetLeft();
        }
        return node;
    }

    void DeleteFixup(TreeNode* node) {
        // While node is not the root, non-existant, and black
        while (node != nullptr && node != root && (*node).GetColor() == true) {
            // If node is a left child
            if (node == (*node).GetParent()->GetLeft()) {
                TreeNode* sibling = (*node).GetParent()->GetRight();   // Sibling of node
                if ((*sibling).GetColor() == false) {   // Case 1: node's sibling is red
                    (*sibling).SetColor(true);
                    (*node).GetParent()->SetColor(false);
                    RotateLeft((*node).GetParent());
                    sibling = (*node).GetParent()->GetRight();
                }
                if ((*sibling).GetLeft()->GetColor() == true && (*sibling).GetRight()->GetColor() == true) {
                    (*sibling).SetColor(false);
                    node = (*node).GetParent();
                }
                else {
                    if ((*sibling).GetRight()->GetColor() == true) {
                        (*sibling).GetLeft()->SetColor(true);
                        (*sibling).SetColor(false);
                        RotateRight(sibling);
                        sibling = (*node).GetParent()->GetRight();
                    }
                    (*sibling).SetColor((*node).GetParent()->GetColor());
                    (*node).GetParent()->SetColor(true);
                    (*sibling).GetRight()->SetColor(true);
                    RotateLeft((*node).GetParent());
                    node = root;
                }
            }
            else {
                TreeNode* sibling = (*node).GetParent()->GetLeft();
                if ((*sibling).GetColor() == false) {
                    (*sibling).SetColor(true);
                    (*node).GetParent()->SetColor(false);
                    RotateRight((*node).GetParent());
                    sibling = (*node).GetParent()->GetLeft();
                }
                if ((*sibling).GetRight()->GetColor() == true && (*sibling).GetLeft()->GetColor() == true) {
                    (*sibling).SetColor(false);
                    node = (*node).GetParent();
                }
                else {
                    if ((*sibling).GetLeft()->GetColor() == true) {
                        (*sibling).GetRight()->SetColor(true);
                        (*sibling).SetColor(false);
                        RotateLeft(sibling);
                        sibling = (*node).GetParent()->GetLeft();
                    }
                    (*sibling).SetColor((*node).GetParent()->GetColor());
                    (*node).GetParent()->SetColor(true);
                    (*sibling).GetLeft()->SetColor(true);
                    RotateRight((*node).GetParent());
                    node = root;
                }
            }
        }
        if (node != nullptr)
            (*node).SetColor(true);
    }
public:
    // When created, a tree should be empty where the root is NULL
    Tree() {
        root = nullptr;
    }
    // When destroyed, a tree should be emptied where each node is deleted.
    ~Tree() {
        while (root != nullptr) {
            RemoveNode((*root).GetValue());
        }
    }

    // Return the root of the tree
    TreeNode* GetRoot() {
        return root;
    }

    void AddValue(int value) {
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
        InsertFixup(traversalNode);
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
        TreeNode* traversalNode = GetNode(value);
        if (traversalNode == nullptr) {
            return;
        }
        TreeNode* node;
        TreeNode* y = traversalNode;
        bool yOriginalColor = (*y).GetColor();
        if ((*traversalNode).GetLeft() == nullptr) {
            node = (*traversalNode).GetRight();
            Transplant(traversalNode, (*traversalNode).GetRight());
        }
        else if ((*traversalNode).GetRight() == nullptr) {
            node = (*traversalNode).GetLeft();
            Transplant(traversalNode, (*traversalNode).GetLeft());
        }
        else {
            y = Minimum((*traversalNode).GetRight());
            yOriginalColor = (*y).GetColor();
            node = (*y).GetRight();
            if ((*y).GetParent() == traversalNode) {
                if (node != nullptr) {
                    (*node).SetParent(y);
                }
            }
            else {
                Transplant(y, (*y).GetRight());
                (*y).SetRight((*traversalNode).GetRight());
                (*y).GetRight()->SetParent(y);
            }
            Transplant(traversalNode, y);
            (*y).SetLeft((*traversalNode).GetLeft());
            (*y).GetLeft()->SetParent(y);
            (*y).SetColor((*traversalNode).GetColor());
        }
        if (yOriginalColor == true) {
            DeleteFixup(node);
        }
        delete traversalNode;
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
        ret.erase(ret.size() - 1);
        cout << ret;
    }
};

#endif
