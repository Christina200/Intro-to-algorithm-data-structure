#include "BinaryTree.h"
#include <iostream>
#include <vector>
using namespace std;

/* ================================== Node =================================== */

Node *BinaryTree::createFromVariant(const vector<nodeValue> &source, const int &rootIndex) {
    if (rootIndex >= source.size())
        return nullptr;
    auto rootValue = get_if<int>(&source[rootIndex]);
    if (!rootValue)
        return nullptr;
    int rightIndex = 2 * (rootIndex + 1);
    int leftIndex = rightIndex - 1;
    return new Node(*rootValue, createFromVariant(source, leftIndex), createFromVariant(source, rightIndex));
}

Node::Node(const int &val, Node *left, Node *right) : val(val),left(left),right(right){}
int Node::getVal() const {
    return val;
}
void Node::setVal(const int &newVal) {
    val = newVal;
}
Node * Node::getLeft() const {
    return left;
}
void Node::setLeft(const int &newVal) {
    if (!left){
        left = new Node(newVal);
    } else {
        left->setVal(newVal);
    }
}
Node * Node::getRight() const {
    return right;
}
void Node::setRight(const int &newVal) {
    if (!right){
        right = new Node(newVal);
    } else {
        right->setVal(newVal);
    }
}

/* =============================== Binary Tree =============================== */
void Destruct_helper(Node * tree_node);
//EFFECTS: destructor for root node of binary tree.
Node * find_helper(Node * root,const int &key);
//EFFECTS: return the node with {key} value given the root node.
string findPath_helper(Node * root,const int &value);
//EFFECTS: return path to the node with {value} value given the root node.
Node * VisitPath_helper(const std::string &path,int index,Node * terminal);
//EFFECTS: go through the path and return the terminal node.
int sum_helper(Node * root);
//EFFECTS: helper for sum. Return sum of all node values in a binary tree.
int height_helper(Node * root);
//EFFECTS: helper for height. Return height of a binary tree.
void preorder_helper(Node * root);
//EFFECTS: helper for preorder. print the preorder string of a binary tree.
void inorder_helper(Node * root);
//EFFECTS: helper for inorder. print the inorder string of a binary tree.
void postorder_helper(Node * root);
//EFFECTS: helper for postorder. print the postorder string of a binary tree.
bool allPathSumGreater_helper(const int &sum,Node * root);
//EFFECTS: helper for allPathSumGreater. Return whether the sum of all paths in a binary tree is greater than {sum}.
bool cover_helper(Node * root,Node * tree_root);
//EFFECTS: helper for operator<. Return whether binary tree with root node {root} can be covered by {tree_root}.
bool contain_helper(Node * root,Node * tree_root);
//EFFECTS: helper for operator<<. Return whether binary tree with root node {root} is contained by {tree_root}.
Node * copy_helper(Node * tree_root);
//EFFECTS: Deep copy helper for {tree_root} to construct a root node for a binary tree.

BinaryTree::BinaryTree(const int &rootValue) : root(new Node(rootValue)){}
BinaryTree::BinaryTree(Node *node) : root(node){}
BinaryTree::BinaryTree(const BinaryTree &tree) : root(copy_helper(tree.root)){}
BinaryTree::BinaryTree(std::vector<nodeValue> &source) : root(createFromVariant(source,0)){}
BinaryTree::~BinaryTree() {
    Destruct_helper(root);
}
void Destruct_helper(Node * tree_node){
    if (!tree_node) return;
    Destruct_helper(tree_node->getLeft());
    Destruct_helper(tree_node->getRight());
    delete tree_node;
}
bool BinaryTree::empty() const {
    return root == nullptr;
}
Node * BinaryTree::find(const int &key) const {
    return find_helper(root,key);
}
Node * find_helper(Node * root,const int &key){
    if (!root) return nullptr;
    if (root->getVal() == key) return root;
    else {
        Node * l = find_helper(root->getLeft(),key);
        if (l) return l;
        Node * r = find_helper(root->getRight(),key);
        if (r) return r;
    }
    return nullptr;
}
std::string BinaryTree::findPath(const int &value) const {
    if (!find_helper(root,value)) return "-1";
    return findPath_helper(root,value);
}
string findPath_helper(Node * root,const int &value){
    if (find_helper(root->getLeft(),value))
        return "0"+ findPath_helper(root->getLeft(),value);
    if (find_helper(root->getRight(),value))
        return "1"+ findPath_helper(root->getRight(),value);
    else return "";
}
Node * BinaryTree::visitThroughPath(const std::string &path) const {
    if (path.empty()) return root;
    return VisitPath_helper(path,0,root);
}
Node * VisitPath_helper(const std::string &path,int index,Node * terminal){
    if (index >= path.size() || !terminal) return terminal;
    if (path[index] == '0') {
        return VisitPath_helper(path,index+1,terminal->getLeft());
    }
    if (path[index] == '1') {
        return VisitPath_helper(path,index+1,terminal->getRight());
    } else return nullptr;
}
int BinaryTree::sum() const {
    return sum_helper(root);
}
int sum_helper(Node * root){
    if (!root)
        return 0;
    else return root->getVal() + sum_helper(root->getLeft()) + sum_helper(root->getRight());
}
int BinaryTree::height() const {
    return height_helper(root);
}
int height_helper(Node * root){
    if (!root) return 0;
    else return max(1 + height_helper(root->getLeft()),1 + height_helper(root->getRight()));
}
void BinaryTree::preOrder() const {
    preorder_helper(root);
    cout<<endl;
}
void preorder_helper(Node * root){
    if (!root) return;
    cout<<root->getVal()<<" ";
    preorder_helper(root->getLeft());
    preorder_helper(root->getRight());
}
void BinaryTree::inOrder() const {
    inorder_helper(root);
    cout<<endl;
}
void inorder_helper(Node * root){
    if (!root) return;
    inorder_helper(root->getLeft());
    cout<<root->getVal()<<" ";
    inorder_helper(root->getRight());
}
void BinaryTree::postOrder() const {
    postorder_helper(root);
    cout<<endl;
}
void postorder_helper(Node * root){
    if (!root) return;
    postorder_helper(root->getLeft());
    postorder_helper(root->getRight());
    cout<<root->getVal()<<" ";
}
bool BinaryTree::allPathSumGreater(const int &sum) const {
    return allPathSumGreater_helper(sum,root);
}
bool allPathSumGreater_helper(const int &sum,Node * root){
    if (!root) return sum<0;
    return allPathSumGreater_helper(sum - root->getVal(),root->getLeft()) && allPathSumGreater_helper(sum - root->getVal(),root->getRight());
}
bool BinaryTree::operator<(const BinaryTree &tree) const {
    return cover_helper(root,tree.root);
}
bool cover_helper(Node * root,Node * tree_root){
    if (!root) return true;
    if (!tree_root) return false;
    return (root->getVal() == tree_root->getVal()) && cover_helper(root->getLeft(),tree_root->getLeft()) && cover_helper(root->getRight(),tree_root->getRight());
}
bool BinaryTree::operator<<(const BinaryTree &tree) const {
    return contain_helper(root,tree.root);
}
bool contain_helper(Node * root,Node * tree_root){
    if (cover_helper(root,tree_root)) return true;
    if (!tree_root) return false;
    return contain_helper(root,tree_root->getLeft()) || contain_helper(root,tree_root->getRight());
}
BinaryTree & BinaryTree::operator=(const BinaryTree &tree) {
    root = copy_helper(tree.root);
    return *this;
}
Node * copy_helper(Node * tree_root){
    if (!tree_root) return nullptr;
    return new Node(tree_root->getVal(),copy_helper(tree_root->getLeft()),copy_helper(tree_root->getRight()));
}