#ifndef PLAYER_H
#define PLAYER_H


#include <iostream>
#include "Pack.h"
#include "Card.h"
using namespace std;

class Player {
public:
	// Constructor
	Player();

	Player(string n);

	Player(string n, int hscore, int s, int games, int cash,
		bool round, int numCards, int cards, bool a, bool hasH, int ls, bool dd,
		bool splits, int ss);

	// Deconstructor
	~Player();

	void reset();

	// Setters and Getters
	string getName();

	int getHighScore();

	int getScore();

	int getGamesPlayed();

	int getMoney();

	bool getRoundOver();
	
	bool getHasHit();

	bool getSplit();

	int getSplitScore();
	
	Card getCard(int index);

	void setName(string n);

	void setHighScore(int hScore);

	void setScore(int s);

	void setGamesPlayed(int games);

	void setMoney(int cash);

	void setRoundOver(bool over);

	void setNumCards(int n);

	void setHand(Card c, int index);
	
	void setHasHit(bool hasH);

	void setSplitScore(int ss);

	
	// Game Functions
	int playTurn(Pack deck, int & cardsDealt, int &bet);

	void printScore();

	void hit(Card newCard);

	bool checkBlackjack();

	void doubleDown(Pack deck, int &cardsDealt, int &bet);

	void split(Pack deck, int &cardsDealt, int &bet);

	void printCards();

	void printHeader();

	int checkInput(int numChoices, int choice);
	
	void updateHighScore();
	
	void viewStats();

private:
	string name;
	int highScore;
	int score;
	int gamesPlayed;
	int money;
	bool roundOver;
	int numCards;
	bool ace;
	bool hasHit;
	bool doubleD;
	bool splits;
	Card myhand[12];
	int lowScore;
	int splitScore;
};

#endif //