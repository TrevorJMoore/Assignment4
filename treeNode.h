#ifndef TREE_NODE_H
#define TREE_NODE_H


using namespace std;


class TreeNode {
private:
    int value;                      // value of the instance node
    bool isBlack = false;           // color of the instance node (init red)
    TreeNode* parentNode;           // pointer to parent node
    TreeNode* leftNode;             // pointer to left child node
    TreeNode* rightNode;            // pointer to right child node

public:
    // Parameterized Constructor
    TreeNode(int value) {
        this->value = value;
        isBlack = false;    // by default, new nodes created are false
        parentNode = nullptr;
        leftNode = nullptr;
        rightNode = nullptr;
    }


    // Getters and Setters

    int GetValue() {
        return value;
    }

    void SetColor(bool color) {
        this->isBlack = color;
    }

    bool GetColor() {
        return isBlack;
    }

    TreeNode* GetParent() {
        return parentNode;
    }

    void SetParent(TreeNode* parent) {
        this->parentNode = parent;
    }

    TreeNode* GetLeft() {
        return leftNode;
    }

    void SetLeft(TreeNode* left) {
        this->leftNode = left;
    }

    TreeNode* GetRight() {
        return rightNode;
    }

    void SetRight(TreeNode* right) {
        this->rightNode = right;
    }
};

#endif
