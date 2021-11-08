//
// Created by WeiXiwen on 2021/7/16.
//

#include "BinaryTree.h"
#include <iostream>
#include <vector>


int main(){
    std::vector<nodeValue> source = {4, 2, 5, 7, 3, "$", "@", "hey", "xm", 8, 9};
    BinaryTree test1 = BinaryTree(source);
    test1.preOrder();
    return 0;
}