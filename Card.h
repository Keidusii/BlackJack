#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
using namespace std;

class Card {
public:
	Card();

	Card(char s, string r, int v);

	void setSuit(char s);

	void setRank(string r);

	void setValue(int v);

	char getSuit();

	string getRank();

	int getValue();

private:
	char suit;
	string rank;
	int value;
	
};


#endif
