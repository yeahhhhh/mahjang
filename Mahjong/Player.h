#ifndef _PLAYER_
#define _PLAYER_

class Player{
public:
	Player(int);
	int getCard(std::vector<int>);
	int getGanCard(std::vector<int>);
	int dropCard();
	bool pon(int);
	bool chi(int);
	int angan();
	bool kagan();
	bool daimeigan(int);
	int gan();
	bool ron(int);
	bool tumo();
	bool richi();
	void breakIpatu();
	void setRichi();
	void setHaitei();
	void setHoutei();
	void setChangan();
	bool isRichi();

	bool preRichiStatus;
private:
	int cardArray[43];
	int anganArray[4];
	int daimeiganArray[4];
	int ganArray[4];
	int ponArray[4];
	int chiArray[4];
	int currentCard;
	bool monseiStatus;
	bool richiStatus;
	bool ipatuStatus;
	bool rinshanStatus;
	bool haiteiStatus;
	bool houteiStatus;
	
	int dir;
	bool ron();
};

#endif