#ifndef TREE_NODE_H
#define TREE_NODE_H


using namespace std;


class TreeNode {
private:
    int value;                      // value of the instance node
    bool isBlack = true;           // color of the instance node (init black)
    TreeNode* parentNode;           // pointer to parent node
    TreeNode* leftNode;             // pointer to left child node
    TreeNode* rightNode;            // pointer to right child node

public:
    // Parameterized Constructor
    TreeNode(int value) {
        this->value = value;
        isBlack = true;    // by default, new nodes created are black
        parentNode = nullptr;
        leftNode = nullptr;
        rightNode = nullptr;
    }

    TreeNode() {
        this->value = -1;
        isBlack = true;    // by default, new nodes created are black
        parentNode = nullptr;
        leftNode = nullptr;
        rightNode = nullptr;
    }


    // Getters and Setters

    int GetValue() {
        if (this == NULL) return NULL;
        else return value;
    }

    void SetColor(bool color) {
        this->isBlack = color;
    }

    bool GetColor() {
        return isBlack;
    }

    TreeNode* GetParent() {
        if (this == NULL) return NULL;
        else return parentNode;
    }

    void SetParent(TreeNode* parent) {
        this->parentNode = parent;
    }

    TreeNode* GetLeft() {
        if (this == NULL) return NULL;
        else return leftNode;
    }

    void SetLeft(TreeNode* left) {
        this->leftNode = left;
    }

    TreeNode* GetRight() {
        if (this == NULL) return NULL;
        else return rightNode;
    }

    void SetRight(TreeNode* right) {
        this->rightNode = right;
    }
};

#endif
