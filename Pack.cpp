// Pack.cpp

#include "Pack.h"

void Pack::importCards() {
	ifstream card;
	card.open("Cards.txt");
	char s;
	string r;
	int v;
	int i = 0;
	while(card >> s >> r >> v) {
		cards[i].setSuit(s);
		cards[i].setRank(r);
		cards[i].setValue(v);
		i++;
	}
	card.close();
}

void Pack::printDeck() {
	for (int i = 0; i < 52; i++) {
		cout << cards[i].getSuit() << " " << cards[i].getRank() << " " << cards[i].getValue() << endl;
	}
}

void Pack::shuffle() {
	srand(time(NULL));
	for (int i = 0; i < 52; i++) {
		int n = 0;
		n = rand() % 52;
		while (n == i) { 
			n = rand() % 52; 
		}
		Card temp;
		temp = cards[i];
		cards[i] = cards[n];
		cards[n] = temp;
	}
}

Card Pack::getCard(int  & cardsDealt) {
	Card newCard = cards[cardsDealt];
	cardsDealt++;
	return newCard;
}