//
// Created by WeiXiwen on 2021/7/1.
//
#include "hand.h"
Hand::Hand() {
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::discardAll() {
    this->curValue.count = 0;
    this->curValue.soft = false;
}

void Hand::addCard(Card c) {
    if (c.spot==ACE){
        //impossible to have two ACE counted both as 11
        if (!curValue.soft&&(21-curValue.count)>=11){
            this->curValue.count+=11;
            this->curValue.soft = true;
        }
        else this->curValue.count+=1;
    }
    else if (c.spot>=TEN&&c.spot<=KING){
        if (curValue.soft&&curValue.count+10>21){
            this->curValue.soft = false;
        }
        else this->curValue.count+=10;
    }
    else {
        if (curValue.soft&&curValue.count+(c.spot+2)>21){
            this->curValue.soft = false;
            this->curValue.count=this->curValue.count+(c.spot+2)-10;
        } else this->curValue.count+=(c.spot+2);
    }
}

HandValue Hand::handValue() const {
    return curValue;
}
