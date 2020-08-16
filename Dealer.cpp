// Dealer.cpp

#include "Dealer.h"

Dealer::Dealer() {
	score = 0;
	numCards = 0;
	lowScore = 0;
	roundOver = false;
	ace = false;
}

Dealer::Dealer(int s, int numCards) {
	score = s;
	numCards = 0;
	lowScore = 0;
	roundOver = false;
	ace = false;
}

Dealer::~Dealer() {

}

void Dealer::reset() {
	score = 0;
	roundOver = false;
	for (int i = 0; i < 12; i++) {
		dHand[i].setRank("n");
		dHand[i].setSuit('n');
		dHand[i].setValue(0);
	}
	numCards = 0;
}

int Dealer::getScore() {
	return score;
}

bool Dealer::getRoundOver() {
	return roundOver;
}

Card Dealer::getHand(int index) {
	return dHand[index];
}

void Dealer::setScore(int s) {
	score = s;
}

void Dealer::setRoundOver(bool over) {
	roundOver = over;
}

void Dealer::setHand(Card card, int index) {
	dHand[index] = card;
}

void Dealer::hit(Card newCard) {
	dHand[numCards] = newCard;
	if (newCard.getRank() == "A") {
		if (score + 11 > 21) {
			if (lowScore + 11 > 21) {
				ace = false;
			}
			else {
				lowScore += 1;
			}
			score += 1;
		}
		else {
			ace = true;
			score += newCard.getValue();
			lowScore = score - 10;
		}
	}
	else {
		score += newCard.getValue();
		if (ace == true) {
			lowScore += newCard.getValue();
		}
		if (ace == true && score > 17 && lowScore < 17) {
			score = lowScore;
		}
		if (ace == true && score > 21 && lowScore < 21) {
			score = lowScore;
			ace = false;
		}
	}
	numCards++;
}

bool Dealer::insurance(Player & player, int & bet, int & insuranceBet) {
	insuranceBet = bet / 2;
	if (player.getMoney() - insuranceBet >= 0) {
		cout << "The dealer has an Ace." << endl;
		cout << "Would you like to buy insurance? ($" << insuranceBet << ")" << endl;
		cout << "1) Yes" << endl << "2) No" << endl;
		int choice;
		cin >> choice;
		choice = player.checkInput(2, choice);
		if (choice == 1) {
			player.setMoney(player.getMoney() - insuranceBet);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Dealer::checkBlackjack() {
	if (score == 21) {
		return true;
	}
	else {
		return false;
	}
}

void Dealer::printCards() {
	cout << "Dealer's cards:" << endl;
	for (int i = 0; i < numCards; i++) {
		cout << dHand[i].getSuit() << " " << dHand[i].getRank() << endl;
	}
}

void Dealer::printScore() {
	cout << "Dealer score: " << score << endl;
}
void playTurn(Dealer & dealer, Pack deck, int & cardsDealt) {
	dealer.setRoundOver(false);
	while (dealer.getRoundOver() == false) {
		if (dealer.getScore() < 17) {
			dealer.hit(deck.getCard(cardsDealt));
			dealer.printCards();
		}
		else {
			dealer.setRoundOver(true);
			system("cls");
		}
	}
}
