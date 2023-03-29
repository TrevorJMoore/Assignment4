#include <iostream>
#include "treeNode.h"
#include "tree.h"

using namespace std;


int main() {
    Tree tree;
    TreeNode treeNode;

    if (treeNode.GetRight() == NULL) {
        cout << "NULL\n";
    }
    else {
        cout << ":(\n";
    }

    tree.AddValue(5);
    tree.AddValue(6);


    if (tree.GetNode(5)->GetParent() == NULL) {
        cout << "NULL Parent\n";
    }

    /*tree.AddValue(1);
    tree.AddValue(2);
    tree.AddValue(3);
    tree.AddValue(4);
    tree.AddValue(5);

    tree.RemoveNode(1);

    //Should print 4, 2, 3, 5
    tree.PrintTreeWalk(2);*/
    tree.RemoveNode(2);

    cout << tree.GetRoot()->GetValue();

    tree.AddValue(2);
    tree.AddValue(3);
    tree.AddValue(4);
    tree.AddValue(5);
    tree.AddValue(6);
    tree.AddValue(7);
    tree.AddValue(8);
    tree.AddValue(9);
    tree.AddValue(10);
    tree.AddValue(11);
    tree.AddValue(12);
    tree.AddValue(13);
    tree.AddValue(14);
    tree.AddValue(15);



    tree.PrintTreeWalk(2);


    cout << "\n";

    tree.RemoveNode(10);

    tree.PrintTreeWalk(2);
}