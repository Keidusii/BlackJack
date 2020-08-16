#ifndef PACK_H
#define PACK_H

#include <iostream>
#include <fstream>
#include <ctime>
#include "Card.h"
using namespace std;

class Pack {
public:
	void importCards();

	void printDeck();

	void shuffle();

	Card getCard(int & cardsDealt);

private:
	Card cards[52];
};

#endif PACK_H