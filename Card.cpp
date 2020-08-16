// Card.cpp

#include "Card.h"

Card::Card() {
	suit = ' ';
	rank = " ";
	value = 0;
}

Card::Card(char s, string r, int v) {
	suit = s;
	rank = r;
	value = v;
}

void Card::setSuit(char s) {
	suit = s;
}

void Card::setRank(string r) {
	rank = r;
}

void Card::setValue(int v) {
	value = v;
}

char Card::getSuit() {
	return suit;
}

string Card::getRank() {
	return rank;
}

int Card::getValue() {
	return value;
}
