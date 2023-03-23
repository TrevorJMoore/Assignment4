#include <iostream>
#include "treeNode.h"
#include "tree.h"

using namespace std;


int main() {
    Tree tree;
    tree.AddValue(1);
    tree.AddValue(2);
    tree.AddValue(3);
    tree.AddValue(4);

    tree.RemoveNode(2);


    tree.PrintTreeWalk(3);
}