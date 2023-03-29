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
        if (this == NULL) return NULL;
        else return value;
    }

    void SetValue(int value) {
        if (this == NULL) return;
        this->value = value;
    }

    void SetColor(bool color) {
        if (this == NULL) return;
        this->isBlack = color;
    }

    bool GetColor() {
        if (this == NULL) return true;
        else return isBlack;
    }

    TreeNode* GetParent() {
        if (this == NULL) return NULL;
        else return parentNode;
    }

    void SetParent(TreeNode* parent) {
        if (this == NULL) return;
        else this->parentNode = parent;
    }

    TreeNode* GetLeft() {
        if (this == NULL) return NULL;
        else return leftNode;
    }

    void SetLeft(TreeNode* left) {
        if (this == NULL) return;
        else this->leftNode = left;
    }

    TreeNode* GetRight() {
        if (this == NULL) return NULL;
        else return rightNode;
    }

    void SetRight(TreeNode* right) {
        if (this == NULL) return;
        else this->rightNode = right;
    }
};

#endif
