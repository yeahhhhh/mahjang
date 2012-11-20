// Mahjong.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "iostream"
#include "vector"
#include "time.h"
#include "string"

#include "Mahjong.h"
#include "Player.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << endl;
	cout << "==========================================================" << endl;
	cout << "                 Welcome to Mahjong world !               " << endl;
	cout << "==========================================================" << endl;
	cout << "\n\n\n" << endl;
	cout << "Press Q to Quit, any other key to Start." << endl;
	//while(true){
	//	if(getchar() == 'q' || getchar() == 'Q')
	//		return 0;
	//	else 
	//		break;
	//}
	//{
	//	cout << "Enter player number ( 0 - 4 ): ";
	//	int choice = getchar();
	//	switch(choice){
	//	case '1':
	//		playerNum = 1;
	//		break;
	//	case '2':
			playerNum = 2;
	//		break;
	//	case '3':
	//		playerNum = 3;
	//		break;
	//	case '4':
	//		playerNum = 4;
	//		break;
	//	default:
	//		playerNum = 1;
	//		break;
	//	}
	//}
	startGame();
	return 0;
}

void startGame(){
	getCard();
//	playGame();
}

void getCard(){
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
		for(int j = 0; j < playerNum; j++){
			int card = playerList[j]->getCard(cardHill);
			printf("Player %d get a card %s \n", j, cardName(card));
			cardHill.pop_back();
		}
	}
}

void playGame(){
	int round = 0;//ѲĿ
	int turn = 0;//��ұ��
	bool endFlag = false;
	bool meihaiFlag = false;
	bool ganFlag = false;
	while(cardHill.size() > 14){
		round ++;
		Player* player = playerList[turn];
		if(!meihaiFlag){
			int card;
			if(!ganFlag){
				card = player->getCard(cardHill);//����
				cardHill.pop_back();
			}
			else{
				card = player->getGanCard(cardHill);//������
				cardHill.erase(cardHill.begin());
			}
			printf("Player %d get a %s \n", turn, cardName(card));
			int remain = cardHill.size();//�ƶ�ʣ������
			printf("Left card num: %d \n", remain);

			//���ܡ��Ӹ�
			if(canGan()){//ʣ���������>4���������һѲ��
				if(int ganCard = player->angan()){//����
					ganFlag = true;
					printf("Player %d angan %s", turn, cardName(ganCard));
					continue;
				}
				else { 
					if(int ganCard = player->gan()){//�Ӹ�
						for(int i = 0; i < playerNum; i++){
							if(i == turn)
								continue;
							else {
								playerList[i]->setChangan();//����
								if(playerList[i]->ron(ganCard)){
									ronList.push_back(i);
									endFlag = true;
									continue;
								}
							}
						}
					}
				}
			}
			else if(lastCard()){//���һ��
				for(int i = 0; i < playerNum; i++){
					if(i != turn)
						playerList[i]->setHoutei();//��������ӵױ�־Ϊ��
					else
						playerList[i]->setHaitei();//������躣�ױ�־Ϊ��
				}				
			}
			if(player->tumo()){//�������ƣ�����
				break;
			}
		}
		if(endFlag)
			break;
		meihaiFlag = false;
		ganFlag = false;
		if(player->richi()){
			player->preRichiStatus = true;
		}
		int droppedCard = player->dropCard();//����
		for(int i = 0; i < playerNum; i++){
			if(i == turn) 
				continue;
			if(playerList[i]->ron(droppedCard)){//�Ƿ���
				ronList.push_back(i);
				endFlag = true;//��北�����
				continue;
			}
		}
		if(endFlag){
			player->preRichiStatus = false;
			break;
		}
		if(player->preRichiStatus){
			player->setRichi();
			if(round == 1){
				//wrichi
			}
			player->preRichiStatus = false;
		}
		for(int i = 0; i < playerNum; i++){
			if(i == turn) 
				continue;
			if(playerList[i]->daimeigan(droppedCard)){
				ganFlag = true;
				turn = i;
				break;
			}
			else if(playerList[i]->pon(droppedCard)){
				meihaiFlag = true;
				turn = i;
				break;
			}
		}
		if(ganFlag){
			for(int i = 0; i < playerNum; i++)
				playerList[i]->breakIpatu();
			continue;
		}
		if(playerList[++turn]->chi(droppedCard)){
			meihaiFlag = true;
			for(int i = 0; i < playerNum; i++)
				playerList[i]->breakIpatu();
			continue;
		}
		turn = (turn + 1) % playerNum;//����
	}
}

char* cardName(int card){
	char* name = new char[4];
	if(card > 43 || card < 0 || card % 10 == 0){
		return name;
	}
	switch(card){
		case 31:
			name = "��";
			break;
		case 33:
			name = "��";
			break;
		case 35:
			name = "��";
			break;
		case 37:
			name = "��";
			break;
		case 39:
			name = "��";
			break;
		case 41:
			name = "��";
			break;
		case 43:
			name = "��";
			break;
		default:
			break;
	}
	if(card < 30){
		int num = card % 10;
		switch(card / 10){
		case 0:
			sprintf(name, "%d��", num);
			break;
		case 1:
			sprintf(name, "%dͲ", num);
			break;
		case 2:
			sprintf(name, "%d��", num);
			break;
		}
	}
	else{ 
		if(card % 2 == 0) 
			name = "";
	}
	return name;
}

bool canGan(){
	return cardHill.size() > 14;
}

bool lastCard(){
	return cardHill.size() == 14;
}