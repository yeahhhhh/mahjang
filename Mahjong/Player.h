#ifndef _PLAYER_
#define _PLAYER_

class Player{
public:
	Player(int);
	int getCard();
	int getGanCard();
	int dropCard();
	bool pon(int);
	bool chi(int);
	bool gan();
	bool gan(int);
	bool ron();
	bool ron(int);
	void setRinshan(bool);
	void setHaitei(bool);
	void setHoutei(bool);
private:
	int cardArray[43];
	int currentCard;
	bool richiStatus;
	bool ipatuStatus;
	bool turnStatus;
	bool rinshanStatus;
	bool haiteiStatus;
	bool houteiStatus;
	int dir;
	bool _ron();
	bool _gan();

};

#endif