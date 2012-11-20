#include "stdafx.h"
#include "vector"
#include "Player.h"
#include "Mahjong.h"

Player::Player(int cDir){
	dir = cDir;
	for(int i = 0; i < 44; i++){
		cardArray[i] = 0;
	}
}

int Player::getCard(std::vector<int> cardHill){
	int card = cardHill.back();
	cardArray[card] ++;
	currentCard = card;
	return card;
};

int Player::getGanCard(std::vector<int> cardHill){
	int card = cardHill[0];
	cardArray[card] ++;
	currentCard = card;
	return card;
}


void Player::breakIpatu(){
	ipatuStatus = false;
}

void Player::setRichi(){
	richiStatus = true;
}

void Player::setHoutei(){
	houteiStatus = true;
}

void Player::setHaitei(){
	haiteiStatus = true;
}

int Player::dropCard(){
	int card;
	rinshanStatus = false;
	if(ipatuStatus)
		ipatuStatus = false;
	return card;
}

bool Player::pon(int){
	return true;
}

bool Player::chi(int){
	return true;
}

bool Player::ron(int){
	return true;
}

int Player::angan(){
	for(int i = 0; i < 44; i++){
		if(cardArray[i] == 4){
			printf("Angan %s ? ", i);
			if(getchar() == 'y' || getchar() == 'Y'){
				cardArray[i] -= 4;
				for(int j = 0; j < 4; j++){
					if(anganArray[j] == 0){
						anganArray[j] = i;
						break;
					}
				}
				rinshanStatus = true;
				return i;
			}
		}
	}
	return 0;
}

bool Player::daimeigan(int ganCard){
	if(cardArray[ganCard] == 3){
		if(getchar() == 'y' || getchar() == 'Y'){
			cardArray[ganCard] -= 3;
			for(int j = 0; j < 4; j++){
				if(daimeiganArray[j] == 0){
					daimeiganArray[j] = ganCard;
					break;
				}
			}
			rinshanStatus = true;
			return true;
		}
	}
	return false;
}

int Player::gan(){
	int ganCard = 0;
	for(int i = 0; i < 4; i++){
		if(ponArray[i] != 0){
			if(cardArray[ponArray[i]] == 1){
				printf("Kagan %s ? ", ponArray[i]);
				if(getchar() == 'y' || getchar() == 'Y'){
					ganCard = ponArray[i];
					cardArray[ponArray[i]] --;
					ganArray[i] = ganCard;
					ponArray[i] = 0;
					rinshanStatus = true;
					return ganCard;
				}
			}
		}
	}
	return 0;
}

bool Player::richi(){
	return true;
}

bool Player::tumo(){
	return true;
}
