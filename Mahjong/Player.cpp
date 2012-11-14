#include "Player.h"
#include "Mahjong.h"

int Player::getCard(){
	int card = cardHill.back();
	cardHill.pop_back();
	cardArray[card] ++;
	currentCard = card;
	return card;
};

Player::Player(int cDir):richiStatus(0), ipatuStatus(0), turnStatus(0){
	dir = cDir;
	for(int i = 0; i < 44; i++){
		cardArray[i] = 0;
	}
}

void Player::setRinshan(bool status){
	rinshanStatus = status;
}