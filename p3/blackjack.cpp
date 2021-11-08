//
// Created by WeiXiwen on 2021/7/4.
//

#include "player.h"
#include "card.h"
#include "deck.h"
#include "rand.h"
#include "hand.h"
#include <iostream>
using namespace std;

#define MIN_BET 5
void RoundShuffle(Deck &deck);
//MODIFIES: deck
//EFFECTS: do the shuffling before every round/when cards are used up.
Card DealCard(Player * player,Deck &deck,Hand &hand,bool isUp,bool isPlayer,const string& Dealer_Fullname);
//EFFECTS: deal card in each hand. Print certain messages and expose() if necessary.
int BankrollInitialize(Player * player,int ini_bankroll);
//EFFECTS: initialize the bankroll for player.
bool isEscape(int normal_bankroll, int curr_bankroll,Player * player);
//EFFECTS: return true if Joseph Joestar is to escape and print message.
Card KujoDeal(Hand &hand,Player * player,bool isPlayer,Deck &deck,int curr_num_card);
//EFFECTS: Deal with card when the player/dealer is Kujo.

int main(int argc, char * argv[]){
    int ini_bankroll = atoi(argv[1]);
    int max_hands = atoi(argv[2]);
    string player_type = argv[3];
    string dealer_side = argv[4];
    /*
    int ini_bankroll = 5;
    int max_hands = 1;
    string player_type = "counting";
    string dealer_side = "sos";
*/
    Deck deck = Deck();
    deck.reset();
    int this_round_player = 1;
    int this_round_dealer = 1;
    Player * round_player = get_Player(dealer_side,player_type,this_round_player);
    int bankroll = BankrollInitialize(round_player,ini_bankroll);
    //check whether can start a new round.
    while (this_round_dealer<=5 && this_round_player<=5){
        round_player = get_Player(dealer_side,player_type,this_round_player);
        RoundShuffle(deck);
        round_player->shuffled();
        int this_hand = 1;
        Hand player_hand, dealer_hand;
        string Dealer_Fullname;
        if (dealer_side == "sc")
            Dealer_Fullname = SC_Name[this_round_dealer-1];
        else  Dealer_Fullname=SOS_Name[this_round_dealer-1];
        //check whether can start a new hand.
            while (bankroll>=MIN_BET && this_hand<=max_hands&&!isEscape(ini_bankroll,bankroll,round_player)){
                try {
                    cout << "Hand " << this_hand << " bankroll " << bankroll << endl;
                    ++this_hand;
                    if (deck.cardsLeft()<20) RoundShuffle(deck);
                    int bet = round_player->bet(bankroll,MIN_BET);
                    cout << "Player: " << round_player->getName() << " bets " << bet << endl;
                    player_hand.discardAll();
                    dealer_hand.discardAll();
                    DealCard(round_player,deck,player_hand,true,true,Dealer_Fullname);
                    Card dealer_up = DealCard(round_player,deck,dealer_hand, true, false,Dealer_Fullname);
                    DealCard(round_player,deck,player_hand, true, true,Dealer_Fullname);
                    Card hole = DealCard(round_player,deck,dealer_hand, false, false,Dealer_Fullname);
                    int player_num_card = 2;int dealer_num_card = 2;
                    //natural 21
                    if (player_hand.handValue().count==21){
                        bankroll+=(3*bet/2);
                        cout << "Player: " << round_player->getName() << " dealt natural 21" << endl;
                        continue;
                    }
                    while (round_player->draw(dealer_up,player_hand)){
                        if (round_player->getName()==SC_Name[1]){
                            //Kujo deal when he's a player.
                            KujoDeal(player_hand,round_player,true,deck,player_num_card);
                        }
                        else DealCard(round_player,deck,player_hand, true,true,Dealer_Fullname);
                        player_num_card++;
                    }
                    cout << "Player: " << round_player->getName() << "'s total is " << player_hand.handValue().count << endl;
                    //if the player busts
                    if (player_hand.handValue().count>21){
                        cout << "Player: " << round_player->getName() << " busts" << endl;
                        bankroll-=bet;
                        continue;
                    }
                    else {
                        //the player doesn't bust
                        round_player->expose(hole);
                        cout<<"Dealer: "<< Dealer_Fullname <<"'s hole card is "<< SpotNames[hole.spot] <<" of "<< SuitNames[hole.suit] << endl;
                        //deal begin to hit.
                        while (dealer_hand.handValue().count<17){
                            if (Dealer_Fullname == SC_Name[1]){
                                //Kujo deal when he's a dealer.
                                Card next_card = KujoDeal(dealer_hand,round_player,false,deck,dealer_num_card);
                                round_player->expose(next_card);
                            }
                            else DealCard(round_player,deck,dealer_hand,true,false,Dealer_Fullname);
                            dealer_num_card++;
                        }
                        cout << "Dealer: " << Dealer_Fullname << "'s total is " << dealer_hand.handValue().count << endl;
                        if (dealer_hand.handValue().count>21){
                            //the dealer busts.
                            cout << "Dealer: " << Dealer_Fullname << " busts" << endl;
                            bankroll+=bet;
                            continue;
                        }
                        //neither player nor dealer busts.
                        if (player_hand.handValue().count<dealer_hand.handValue().count){
                            cout << "Dealer: " << Dealer_Fullname << " wins this hand" << endl;
                            bankroll-=bet;
                        }
                        else if (player_hand.handValue().count>dealer_hand.handValue().count){
                            cout << "Player: " << round_player->getName() << " wins this hand" << endl;
                            bankroll+=bet;
                        }
                        else cout << "Push" << endl;
                    }
                }
                catch (DeckEmpty deckEmpty) {
                    cout << "Hand " << --this_hand << " card used up, this hand will start again" << endl;
                    RoundShuffle(deck);
                    round_player->shuffled();
                    player_hand.discardAll();
                    dealer_hand.discardAll();
                    continue;
                }
            }
        cout << "Player: " << round_player->getName() << " has " << bankroll << " after " << this_hand-1 << " hands" << endl;
            if (isEscape(ini_bankroll,bankroll,round_player)){
                cout<<"Player: Joseph Joestar: \"Ni Ge Run Da Yo\""<<endl;
                cout << "Player: " << round_player->getName()
                     << " has been kicked out. The winner of this round is " << Dealer_Fullname << "." << endl;
                ++this_round_player;
                bankroll = BankrollInitialize(get_Player(dealer_side, player_type, this_round_player),ini_bankroll);
            }
            else {
                if (this_hand > max_hands && bankroll >= MIN_BET) {
                    //dealer kicked out.
                    cout << "Dealer: " << Dealer_Fullname << " has been kicked out. The winner of this round is "
                         << round_player->getName() << "." << endl;
                    if (round_player->getName()==SC_Name[0]) cout<<"Player: Joseph Joestar: \"Nice!\""<<endl;
                    if (round_player->getName()==SC_Name[3]) cout<<"Player: Kakyoin Noriaki: \"rerorerorero rerorerorero\""<<endl;
                    ++this_round_dealer;
                } else if (bankroll < MIN_BET) {
                    cout << "Player: " << round_player->getName()
                         << " has been kicked out. The winner of this round is " << Dealer_Fullname << "." << endl;
                    if (Dealer_Fullname==SC_Name[0]) cout<<"Dealer: Joseph Joestar: \"Nice!\""<<endl;
                    if (Dealer_Fullname==SC_Name[3]) cout<<"Dealer: Kakyoin Noriaki: \"rerorerorero rerorerorero\""<<endl;
                            ++this_round_player;
                    bankroll = BankrollInitialize(get_Player(dealer_side, player_type, this_round_player),ini_bankroll);
                }
            }
    }
    bool scWin = false;
    bool sosWin = false;
    if (this_round_player>5){
        //dealer team wins.
        if (dealer_side == "sc")
            scWin = true;
        else sosWin = true;
    }
    else {
        //player team wins.
        if (dealer_side == "sos")
            scWin = true;
        else sosWin = true;
    }
    if (sosWin)
        cout<<"Game over. The winner is SOS Brigade. SOS Brigade got four computers and Stardust Crusaders become an affiliate group of SOS Brigade"<<endl;
    if (scWin)
        cout<<"Game over. The winner is Stardust Crusaders. SOS Brigade will return the computer to Joseph Joestar and Suzumiya Haruhi will become a member of Stardust Crusaders"<<endl;
}

void RoundShuffle(Deck &deck){
    //shuffle the deck
    cout << "Shuffling the deck" << endl;
    for (int i = 0; i < 7; ++i) {
        int cut_point=get_cut();
        cout << "cut at " << cut_point << endl;
        deck.shuffle(cut_point);
    }
}
Card DealCard(Player * player,Deck &deck,Hand &hand,bool isUp,bool isPlayer,const string& Dealer_Fullname){
        Card curr = deck.deal();
        hand.addCard(curr);
        if (isUp) {
            player->expose(curr);
            if (isPlayer)
                cout<<"Player: "<< player->getName() <<" dealt "<< SpotNames[curr.spot] <<" of "<< SuitNames[curr.suit] <<endl;
            else
                cout<<"Dealer: "<< Dealer_Fullname <<" dealt "<< SpotNames[curr.spot] <<" of "<< SuitNames[curr.suit] <<endl;
        }
        return curr;
}

int BankrollInitialize(Player * player,int ini_bankroll){
    //bankroll initialize.
    int bankroll = ini_bankroll;
    if (player->getName()==SC_Name[0])
        bankroll*=2;
    return bankroll;
}


bool isEscape(int normal_bankroll, int curr_bankroll,Player * player) {
    if (player->getName()==SC_Name[0])
        return curr_bankroll < normal_bankroll / 2;
    else return false;
}


Card KujoDeal(Hand &hand,Player * player,bool isPlayer,Deck &deck,int curr_num_card){
    //check whether thw next card will make Kujo busts.
    Card next_card = deck.deal();
    hand.addCard(next_card);
    if (isPlayer){
        //Kujo is player.
        player->expose(next_card);
        while  (hand.handValue().count>21){
            hand.discardAll();
            cout<<"Player: Kujo Jotaro: \"Star Platinum, Za Warudo\""<<endl;
            for (int i = 0; i < curr_num_card+1; ++i){
                next_card = deck.deal();
                hand.addCard(next_card);
                player->expose(next_card);
            }
        }
        cout<<"Player: Kujo Jotaro dealt "<< SpotNames[next_card.spot] <<" of "<< SuitNames[next_card.suit] <<endl;
    }
    else {
        //Kujo is dealer.
        while  (hand.handValue().count>21){
            hand.discardAll();
            cout<<"Dealer: Kujo Jotaro: \"Star Platinum, Za Warudo\""<<endl;
            for (int i = 0; i < curr_num_card+1; ++i){
                next_card = deck.deal();
                hand.addCard(next_card);
            }
        }
        cout<<"Dealer: Kujo Jotaro dealt "<< SpotNames[next_card.spot] <<" of "<< SuitNames[next_card.suit] <<endl;
    }
    return next_card;
}
