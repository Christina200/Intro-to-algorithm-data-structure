//
// Created by WeiXiwen on 2021/7/24.
//

#ifndef P5_DLISTIMPL_H
#define P5_DLISTIMPL_H

#include "Dlist.h"
#include <iostream>
template <class T>
bool Dlist<T>::isEmpty()const
{
return first == NULL&&last == NULL;
}
template <class T>
void Dlist<T>::insertFront(T *op) {
    node * new_node = new node;
    new_node->op = op;
    new_node->prev = NULL;
    new_node->next = first;
    if (isEmpty()){
        first = new_node;
        last = new_node;
    }
    else {
        first->prev = new_node;
        first = new_node;
    }
}
template <class T>
void Dlist<T>::insertBack(T *op) {
    node * new_node = new node;
    new_node->op = op;
    new_node->prev = last;
    new_node->next = NULL;
    if (isEmpty()){
        first = new_node;
        last = new_node;
    }
    else {
        last->next = new_node;
        last = new_node;
    }
}

template <class T>
T * Dlist<T>::removeFront() {
    if (isEmpty()){
        EmptyList error;
        throw error;
    }
    if (!first->next){
        T * result = first->op;
        node * tmp = first;
        first = NULL;last = NULL;
        delete tmp;
        return result;
    }
    node * del = first;
    T * res = first->op;
    first->next->prev = NULL;
    first = first->next;
    delete del;
    return res;
}
template <class T>
T * Dlist<T>::removeBack() {
    if (isEmpty()){
        EmptyList error;
        throw error;
    }
    if (!last->prev){
        T * result = last->op;
        node * tmp = last;
        first = NULL;last = NULL;
        delete tmp;
        return result;
    }
    node * del = last;
    T * res = last->op;
    last->prev->next = NULL;
    last = last->prev;
    delete del;
    return res;
}

template <class T>
Dlist<T>::Dlist():first(NULL),last(NULL){}
template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l) {
    if (!isEmpty())
        removeAll();
    node * curr = l.first;
    while (curr){
        T * curr_node = new T(*curr->op);
        insertBack(curr_node);
        curr = curr->next;
    }
}
template <class T>
Dlist<T>::Dlist(const Dlist<T> &l): first(NULL),last(NULL) {
    copyAll(l);
}
template<class T>
Dlist<T> & Dlist<T>::operator=(const Dlist<T> &l) {
    if (this != &l)
        copyAll(l);
    return * this;
}
template<class T>
Dlist<T>::~Dlist() {
    removeAll();
}
template<class T>
void Dlist<T>::removeAll() {
    while (!isEmpty())
        removeFront();
}
#endif //P5_DLISTIMPL_H
