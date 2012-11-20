#ifndef _MAHJONG_
#define _MAHJONG_

#include "vector"
#include "Player.h"

void startGame();
void getCard();
void playGame();
char* cardName(int);
bool canGan();
bool lastCard();

static int playerNum;
static std::vector<int> cardHill;
static Player* playerList[4];
static std::vector<int> ronList;

#endif