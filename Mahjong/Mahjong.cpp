// Mahjong.cpp : �������̨Ӧ�ó������ڵ㡣
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
	int turn = 0;//��ұ��
	bool endFlag = false;
	while(cardHill.size() > 14){
		Player* player = playerList[turn];

		int card = player->getCard();//����
		printf("Player %d get a %s", turn, card);
		int remain = cardHill.size();//�ƶ�ʣ������
		if(remain-14 >= 4){//ʣ���������>4���������һѲ��
			while(player->gan()){//��
				player->getGanCard();//������
				player->setRinshan(true);//���ϱ�־��Ϊ��
			}
		}
		else {//���һѲ
			for(int i = 0; i < playerNum; i++){
				playerList[i]->setHoutei(true);//��������ӵױ�־Ϊ��
			}
			if(remain == 14){//���һ��
				player->setHoutei(false);//������躣�ױ�־Ϊ��
				player->setHaitei(true);//�����ȡ���ӵױ�־
			}				
		}
		if(player->ron()){//�������ƣ�����
			break;
		}
		else{
			player->setRinshan(false);//���ϱ����Ϊ��
		}
		int droppedCard = playerList[turn]->dropCard();//����
		for(int i = 0; i < playerNum; i++){
			if( i == turn) 
				continue;
			if(playerList[i]->ron(droppedCard)){//�Ƿ���
				ronList.push_stack(i);
				endFlag = true;//��北�����
			}
			if(playerList[i]->gan(droppedCard)){
			}
		}
		if(endFlag)
			break;
		turn = (turn + 1) % playerNum;//����
	}
}