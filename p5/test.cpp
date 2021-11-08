#include <iostream>
#include "Dlist.h"
using namespace std;

int main()
{
    int result = 0;

    Dlist<int> ilist;
    int *ip = new int(1);
    int *ip2 = new int(2);
    ilist.insertFront(ip);
    //cout<<ilist;
    ilist.insertBack(ip2);
    //cout<<ilist;
    //ilist.removeBack();
    //cout<<ilist;
    Dlist<int> list2;
    list2 = ilist;
    cout<<list2;
//    ip = ilist.removeFront();
//    if(*ip != 1)
//        result = -1;
    delete ip;
    delete ip2;
//
//    if(!ilist.isEmpty())
//        result = -1;
//
//    return result;
return 0;
}
