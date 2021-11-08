#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "BinaryTree.h"
#include "NodeInfo.h"
using namespace std;
void Compress(const std::string &filename){
//    REQUIRES: file can be opened. The input string is valid (only contains 0 and 1).
//    EFFECTS: compress the string of '0's and '1's to a binary tree and print the node information.
//    build a binary tree with root node value = 0.
    BinaryTree compress = BinaryTree(0);
    std::string longest_substr;
//    open the file.
    ifstream iFile;
    iFile.open(filename);
    char curr;
    int node_index = 1;
    NodeInfo ni;
    while (iFile.get(curr)){
//        read character from file one by one.
        string tmp = longest_substr + curr;
//        if {tmp} can be found in the binary tree, {longest_substr} = {tmp}.
        if (compress.visitThroughPath(tmp)) longest_substr = tmp;
        else {
//            add a child to the node with path {longest_substr} based on the current char
            if (curr == '0')
                compress.visitThroughPath(longest_substr)->setLeft(node_index);
            if (curr == '1')
                compress.visitThroughPath(longest_substr)->setRight(node_index);
//            print the node info of the node corresponding to {longest_substr}.
            ni = NodeInfo(compress.visitThroughPath(longest_substr)->getVal(),curr);
            cout << ni;
            node_index++;
//            clear {longest_substr}.
            longest_substr = "";
        }
    }
//    print the end node information.
    ni = NodeInfo(compress.visitThroughPath(longest_substr)->getVal(),'\0');
    cout << ni;
    iFile.close();
}

void Decompress(const string& filename){
//    REQUIRES: file can be opened. The input string is valid (satisfy the format in NodeInfo.h; only contains 0,1 and @).
//    EFFECTS: print the original string from node pairs.
//    build a binary tree with root node value = 0.
    BinaryTree decompress = BinaryTree(0);
//    open the file.
    ifstream iFile;
    iFile.open(filename);
    NodeInfo ni;
    int index = 1;
    while (iFile >> ni){
//        read the node info from file one by one. Add a child for parent node according to ni.c (c is 0 or 1 or @).
//        And print the path from root to this child.
        if (ni.c == '0'){
            decompress.find(ni.node_index)->setLeft(index);
            cout<<decompress.findPath(index);
        }
        if (ni.c == '1'){
            decompress.find(ni.node_index)->setRight(index);
            cout<<decompress.findPath(index);
        }
        if (ni.c == '@')
            cout<<decompress.findPath(ni.node_index);
        index++;
    }
//    close the file.
    iFile.close();
}

int main(int argc, char *argv[]){
    // TODO: implement your dbc program here!
    string command, filename;
    command = argv[1];
    filename = argv[2];
    if (command == "-x")
        Compress(filename);
    if (command == "-d")
        Decompress(filename);
    return 0;
}