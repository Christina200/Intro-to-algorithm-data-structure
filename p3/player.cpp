//
// Created by WeiXiwen on 2021/7/1.
//
#include "player.h"
#include <iostream>
class SimplePlayer : public Player {
public:
    virtual int bet(unsigned int bankroll,unsigned int minimum){
        //Suzumiya Haruhi
        if (name==SOS_Name[0])
            return 2*(int)minimum;
        return (int)minimum;
    }
    bool draw(Card dealer,const Hand& player){
        if (!player.handValue().soft){
            if (player.handValue().count<=11) return true;
            if (player.handValue().count==12)
                return !(dealer.spot == FOUR || dealer.spot == FIVE || dealer.spot == SIX);
            if (player.handValue().count>=13&&player.handValue().count<=16)
                return !(dealer.spot >= TWO && dealer.spot <= SIX);
            else return false;
        }
        else {
            if (player.handValue().count<=17) return true;
            if (player.handValue().count==18) return !(dealer.spot==TWO||dealer.spot==SEVEN||dealer.spot==EIGHT);
            else return false;
        }
    }

    virtual void expose(Card c){};
    virtual void shuffled(){};
};

class CountingPlayer : public SimplePlayer{
    int count;
public:
    CountingPlayer():count(0){};
    virtual void expose(Card c){
        if (c.spot>=TEN&&c.spot<=ACE)
            --count;
        if (c.spot>=TWO&&c.spot<=SIX)
            ++count;
    }

    virtual void shuffled(){
        count = 0;
    }

    int bet(unsigned int bankroll,unsigned int minimum) override{
        //Asahina Mikuru
        if (name == SOS_Name[2]){
            if (count<=-2 && bankroll >= 2*minimum){
                return 2*(int)minimum;
            } else return (int)minimum;
        }
        //Kakyoin Noriaki
        if (name == SC_Name[3]){
            if (count>=4 && bankroll >= 2*minimum){
                return 2*(int)minimum;
            } else return (int)minimum;
        }
        if (count>=2 && bankroll >= 2*minimum){
            return 2*(int)minimum;
        } else return (int)minimum;
    }
};


void Player::setPlayer(Team tm, int id) {
    team=tm;
    ID=id;
    if (tm==StardustCrusaders)
        name = SC_Name[id-1];
    else name = SOS_Name[id-1];
}

Team Player::getTeam() {
    return team;
}

string Player::getName() {
    return name;
}

int Player::getID() {
    return ID;
}

static SimplePlayer simplePlayer = SimplePlayer();
static CountingPlayer countingPlayer = CountingPlayer();

extern Player* get_Player(string& dealerSide, string& playerType, int& ID){
    if (ID == 5){
        if (playerType == "simple"){
            if (dealerSide == "sc"){
                //player team is SOS.
                SimplePlayer * result = &simplePlayer;
                result->setPlayer(SOSBrigade,ID);
                return result;
            }
            else {
                //player team is SC.
                SimplePlayer * result = &simplePlayer;
                result->setPlayer(StardustCrusaders,ID);
                return result;
            }
        }
        else {
            //counting player.
            if (dealerSide == "sc"){
                //player team is SOS.
                CountingPlayer * result = &countingPlayer;
                result->setPlayer(SOSBrigade,ID);
                return result;
            }
            else {
                //player team is SC.
                CountingPlayer * result = &countingPlayer;
                result->setPlayer(StardustCrusaders,ID);
                return result;
            }
        }
    }
    else {
        if (dealerSide == "sc"){
            //player team is SOS.
            if (ID == 1||ID == 4){
                SimplePlayer * result = &simplePlayer;
                result->setPlayer(SOSBrigade,ID);
                return result;
            }
            else {
                CountingPlayer * result = &countingPlayer;
                result->setPlayer(SOSBrigade,ID);
                return result;
            }
        }
        else {
            //player team is SC.
            if (ID == 3){
                SimplePlayer * result = &simplePlayer;
                result->setPlayer(StardustCrusaders,ID);
                return result;
            }
            else {
                CountingPlayer * result = &countingPlayer;
                result->setPlayer(StardustCrusaders,ID);
                return result;
            }
        }
    }
}