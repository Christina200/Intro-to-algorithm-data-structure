//
// Created by WeiXiwen on 2021/7/1.
//

#include "deck.h"

Deck::Deck():next(0) {};

void Deck::reset() {
    Spot spot_arr[13]={TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,JACK, QUEEN, KING, ACE};
    Suit suit_arr[4]={SPADES, HEARTS, CLUBS, DIAMONDS};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            deck[13*i+j].suit=suit_arr[i];
            deck[13*i+j].spot=spot_arr[j];
        }
    }
    next = 0;
}

void Deck::shuffle(int n) {
    int left = n;
    int right = DeckSize-n;
    Card tmp[DeckSize];
    int index_left = 0;
    int index_right = n;
    int index = 0;
    while (left>0&&right>0){
        tmp[index++]=deck[index_right++];
        tmp[index++]=deck[index_left++];
        left--;right--;
    }
    if (left>0){
        for (int i = index_left; i < n; ++i) {
            tmp[index++]=deck[i];
        }
    }
    if (right>0){
        for (int j = index_right; j < DeckSize; ++j) {
            tmp[index++]=deck[j];
        }
    }

    for (int k = 0; k < DeckSize; ++k) {
        deck[k]=tmp[k];
    }
    next = 0;
}

Card Deck::deal() {
    if (next>=DeckSize){
        DeckEmpty deckEmpty;
        throw deckEmpty;
    }
    else {
        int curr = next;
        this->next++;
        return deck[curr];
    }
}

int Deck::cardsLeft() {
    return DeckSize-next;
}