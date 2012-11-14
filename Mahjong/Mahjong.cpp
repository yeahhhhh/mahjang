// Mahjong.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "iostream"
#include "vector"
#include "time.h"

#include "Mahjong.h"
#include "Player.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "==========================================================" << endl;
	cout << "                 Welcome to Mahjong world !               " << endl;
	cout << "==========================================================" << endl;
	cout << "\n\n\n" << endl;
	cout << "Press Q to Quit, any other key to Start." << endl;
	while(true){
		if(getchar() == 'q' || getchar() == 'Q')
			return 0;
		else 
			break;
	}
	while(true){
		int choice = getchar();
		switch(choice){
		case '1':
			playerNum = 1;
			break;
		case '2':
			playerNum = 2;
			break;
		case '3':
			playerNum = 3;
			break;
		case '4':
			playerNum = 4;
			break;
		default:
			playerNum = 1;
			break;
		}
	}
	startGame();
	return 0;
}

void startGame(){
	getCard();
}

void getCard(){
	cardHill();
	int a[44];
	srand(time(0));
	int random;
	for(int i = 0; i < 44; i++){
		a[i] = 4;
	}
	for(int i = 0; i < 136; i++){
		random = rand()%44;
		if( random <= 30 ){
			if( random % 10 == 0){
				i--;
				continue;
			}
		}
		else{
			if(random % 2 != 1){
				i--;
				continue;
			}
		}
		if(a[random] > 0){
			cardHill.push_back(random);
			a[random] --;
		}
		else i--;
	}
	for(int i = 0; i < playerNum; i++){
		playerList[i] = new Player(i);
	}
	for(int i = 0; i < 13; i++){
		for(int j = 0; i < playerNum; i++){
			playerList[i]->getCard();
		}
	}
}

void playGame(){
	int turn = 0;//玩家编号
	bool endFlag = false;
	while(cardHill.size() > 14){
		Player* player = playerList[turn];

		int card = player->getCard();//摸牌
		printf("Player %d get a %s", turn, card);
		int remain = cardHill.size();//牌堆剩余张数
		if(remain-14 >= 4){//剩余可摸张数>4（不是最后一巡）
			while(player->gan()){//杠
				player->getGanCard();//摸杠牌
				player->setRinshan(true);//岭上标志设为真
			}
		}
		else {//最后一巡
			for(int i = 0; i < playerNum; i++){
				playerList[i]->setHoutei(true);//所有人设河底标志为真
			}
			if(remain == 14){//最后一张
				player->setHoutei(false);//该玩家设海底标志为真
				player->setHaitei(true);//该玩家取消河底标志
			}				
		}
		if(player->ron()){//自摸胡牌，结束
			break;
		}
		else{
			player->setRinshan(false);//岭上标记设为假
		}
		int droppedCard = playerList[turn]->dropCard();//弃牌
		for(int i = 0; i < playerNum; i++){
			if( i == turn) 
				continue;
			if(playerList[i]->ron(droppedCard)){//是否放铳
				ronList.push_stack(i);
				endFlag = true;//放铳，结束
			}
			if(playerList[i]->gan(droppedCard)){
			}
		}
		if(endFlag)
			break;
		turn = (turn + 1) % playerNum;//换人
	}
}