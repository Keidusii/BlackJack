#ifndef DEALER_H
#define DEALER_H

#include <iostream>
#include "Player.h"
#include "Pack.h"
#include "Card.h"
using namespace std;

class Dealer {
public:
	Dealer();

	Dealer(int s, int numCards);

	~Dealer();

	void reset();

	bool getRoundOver();

	int getScore();

	Card getHand(int index);

	void setScore(int s);

	void setRoundOver(bool over);

	void setHand(Card card, int index);
	
	void hit(Card newCard);

	bool insurance(Player & player, int & bet, int & insuranceBet);

	bool checkBlackjack();

	friend void playTurn(Dealer & dealer, Pack deck, int & cardsDealt);

	void printCards();

	void printScore();

private:
	int score;
	int numCards;
	int lowScore;
	bool ace;
	bool roundOver;
	Card dHand[12];
};

#endif