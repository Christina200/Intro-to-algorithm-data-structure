//
// Created by 吴佳遥 on 2021/7/7.
//
#include <iostream>
#include "BinaryTree.h"
#include <vector>

using namespace std;

void treeCheck(const BinaryTree &tree) {
    cout << tree.height() << endl;
    cout << tree.sum() << endl;
    cout << tree.empty() << endl;
    tree.preOrder();
    tree.inOrder();
    tree.postOrder();
}

void nodePrint(Node *x) {
    if (x == nullptr)
        cout << "nullptr" << endl;
    else
        cout << x->getVal() << endl;
}

int main() {
//    constructor test
//    vector<nodeValue> source = {4, 2, 5, 7, 3, "$", "@", "hey", "xm", 8, 9};
//    vector<nodeValue> source = {0,1,2,3,"","",6,7};
//    BinaryTree tree(source);
//    treeCheck(tree);
//    BinaryTree waste = tree;
//    treeCheck(waste);
//    BinaryTree test1 = BinaryTree(tree);
//    treeCheck(test1);
//    Node * root1 = new Node(1);
//    root1->setLeft(2);
//    root1->setRight(3);
//    root1->getLeft()->setLeft(4);
//    root1->getLeft()->setRight(6);
//    root1->getRight()->setLeft(5);
//    root1:
//        1
//       /   \
//      2     3
//     / \   /  \
//    4   6 5
//    BinaryTree test2 = BinaryTree(root1);
//    treeCheck(test2);
//    BinaryTree test3 = BinaryTree(78);
//    treeCheck(test3);
//    BinaryTree test4 = BinaryTree();
//    treeCheck(test4);
//
//    test1.~BinaryTree();
//    test2.~BinaryTree();
//    test3.~BinaryTree();
//    test4.~BinaryTree();

//    Node *x = tree.find(9);
//    nodePrint(x);
//    x->setLeft(100);
//    cout << tree.findPath(1) << endl;

//    treeCheck(tree);
//    treeCheck(waste);
//
//    x = tree.visitThroughPath("");
//    nodePrint(x);
//
//    x = tree.visitThroughPath("001");
//    nodePrint(x);
//
//    x = tree.find(7);
//    x->setRight(101);
//
//    x = tree.visitThroughPath("001");
//    nodePrint(x);
//    treeCheck(waste);
//    treeCheck(tree);
//
//    vector<nodeValue> coveredVec = {4, 2};
//    vector<nodeValue> uncoveredVec = {5};
//    vector<nodeValue> coveredTargetVec = {4, 2, 5, "", 3};
//    BinaryTree covered(coveredVec);
//    BinaryTree uncovered(uncoveredVec);
//    BinaryTree coveredTarget(coveredTargetVec);
//    BinaryTree coveredTarget = BinaryTree();
//    cout << (covered < coveredTarget) << endl;
//    cout << (uncovered < coveredTarget) << endl;
//
//    vector<nodeValue> containedVec = {3, 6, 7};
//    vector<nodeValue> notContainedVec = {4, 2, 5, "", 3, 7, 8};
//    vector<nodeValue> containedTargetVec = {4, 2, 5, "", 3, "", 8, "", "", 6, 7};
//    vector<nodeValue> containedTargetVec = {};
//    BinaryTree contained(containedVec);
//    BinaryTree notContained(notContainedVec);
//    BinaryTree containedTarget(containedTargetVec);
//    cout << (contained << containedTarget) << endl;
//    cout << (notContained << containedTarget) << endl;
//
//    vector<nodeValue> sumGreaterVec = {4, 1, 5, 3, 6};
//    vector<nodeValue> sumGreaterVec = {};
    vector<nodeValue> sumGreaterVec = {};
    BinaryTree sumGreater(sumGreaterVec);
//       4
//      /  \
//     1    5
//    / \
//   3   6
    cout << sumGreater.allPathSumGreater(-1) << endl;
    cout << sumGreater.allPathSumGreater(7) << endl;

    return 0;
}
