#ifndef _MAHJONG_
#define _MAHJONG_

#include "vector"
#include "Player.h"

void startGame();
void getCard();
void playGame();

static int playerNum;
static vector<int> cardHill;
static Player* playerList[4];
static vector<int> ronList;

#endif