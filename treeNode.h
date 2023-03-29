#ifndef TREE_NODE_H
#define TREE_NODE_H


using namespace std;

class TreeNode {
private:
    int value = NULL;                      // value of the instance node
    bool isBlack = false;           // color of the instance node (init red)
    TreeNode* parentNode = NULL;           // pointer to parent node
    TreeNode* leftNode = NULL;             // pointer to left child node
    TreeNode* rightNode = NULL;            // pointer to right child node

    //Find if the tree is one node
    bool isOne() {
        //The tree is one node if the current node is surrounded by nil
        


        // Not initialized
        if (parentNode == nullptr) {
            return true;
        }
        if (parentNode->value == NULL && leftNode->value == NULL && rightNode->value == NULL) {
            return true;
        }
        return false;
    }

    
    bool hasParent() {
        if (parentNode != nullptr && parentNode->value != NULL) {
            return true;
        }
        return false;
    }



public:
    // Parameterized Constructor
    TreeNode(int value) {
        this->value = value;
        isBlack = false;    // by default, new nodes created are false
        parentNode = NULL;
        leftNode = NULL;
        rightNode = NULL;
    }

    // Nil value construct
    TreeNode() {
        this->value = NULL;
        isBlack = false;
        parentNode = nullptr;
        leftNode = nullptr;
        rightNode = nullptr;
    }


    // Getters and Setters

    int GetValue() {
        if (this == NULL) return NULL;
        return value;
    }

    void SetColor(bool color) {
        if (this == nullptr) return;
        else this->isBlack = color;
    }

    bool GetColor() {
        if (this == NULL) return true;
        return isBlack;
    }

    TreeNode* GetParent() {
        if (!this) return NULL;
        else return parentNode;
    }

    void SetParent(TreeNode* parent) {
        if (this == nullptr) return;
        else this->parentNode = parent;
    }

    TreeNode* GetLeft() {
        if (!this) return NULL;
        if (this->isOne()) return NULL;
        else return leftNode;
    }

    void SetLeft(TreeNode* left) {
        if (!this) return;
        else this->leftNode = left;
    }

    TreeNode* GetRight() {
        if (!this) return NULL;
        if (this->isOne()) return NULL;
        else return rightNode;
    }

    void SetRight(TreeNode* right) {
        if (!this) return;
        else this->rightNode = right;
    }
};

#endif