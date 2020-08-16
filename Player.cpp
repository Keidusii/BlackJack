// Player.cpp

#include "Player.h"

Player::Player() {
	name = "Player 1";
	highScore = 0;
	score = 0;
	gamesPlayed = 0;
	money = 1000;
	roundOver = false;
	numCards = 0;
	ace = false;
	hasHit = false;
	doubleD = false;
	splits = false;
	lowScore = 0;
	splitScore = 0;
}

Player::Player(string n) {
	name = n;
	highScore = 0;
	score = 0;
	gamesPlayed = 0;
	money = 1000;
	roundOver = false;
	numCards = 0;
	ace = false;
	hasHit = false;
	doubleD = false;
	splits = false;
	lowScore = 0;
	splitScore = 0;
}

Player::Player(string n, int hscore, int s, int games, int cash, bool round, 
	int numCards, int cards, bool a, bool hasH, int ls, bool dd, bool split, 
	int ss) {
	name = n;
	highScore = hscore;
	score = s;
	gamesPlayed = games;
	money = cash;
	roundOver = round;
	numCards = cards;
	ace = a;
	hasHit = hasH;
	doubleD = dd;
	splits = split;
	lowScore = ls;
	splitScore = ss;
}

Player::~Player() {

}

void Player::reset() {
	score = 0;
	lowScore = 0;
	splitScore = 0;
	roundOver = false;
	for (int i = 0; i < 12; i++) {
		myhand[i].setRank("");
		myhand[i].setSuit('n');
		myhand[i].setValue(0);

	}
	numCards = 0;
	ace = false;
	hasHit = false;
	splits = false;
}

string Player::getName() {
	return name;
}

int Player::getHighScore() {
	return highScore;
}

int Player::getScore() {
	return score;
}

int Player::getGamesPlayed() {
	return gamesPlayed;
}

int Player::getMoney() {
	return money;
}

bool Player::getRoundOver() {
	return roundOver;
}

bool Player::getHasHit() {
	return hasHit;
}

bool Player::getSplit() {
	return splits;
}

int Player::getSplitScore() {
	return splitScore;
}

Card Player::getCard(int index) {
	return myhand[index];
}

void Player::setName(string n) {
	name = n;
}

void Player::setHighScore(int hScore) {
	highScore = hScore;
}

void Player::setScore(int s) {
	score = s;
}

void Player::setGamesPlayed(int games) {
	gamesPlayed = games;
}

void Player::setMoney(int cash) {
	money = cash;
}

void Player::setRoundOver(bool over) {
	roundOver = over;
}

void Player::setNumCards(int n) {
	numCards = n;
}

void Player::setHand(Card c, int index) {
	myhand[index] = c;
}

void Player::setHasHit(bool hasH) {
	hasHit = hasH;
}

void Player::setSplitScore(int ss) {
	splitScore = ss;
}
void Player::hit(Card newCard) {
	myhand[numCards] = newCard;
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
		if (ace == true && score > 21 && lowScore < 21) {
			score = lowScore;
			ace = false;
		}
	}
	numCards++;
}

bool Player::checkBlackjack() {
	if (score == 21) {
		return true;
	}
	else {
		return false;
	}
}

void Player::doubleDown(Pack deck, int &cardsDealt, int &bet) {
	doubleD = true;
	money -= bet;
	bet *= 2;
	hit(deck.getCard(cardsDealt));
}

void Player::split(Pack deck, int &cardsDealt, int &bet) {
	system("cls");
	splits = true;
	money -= bet; 
	score = 0;
	Card temp = myhand[0];
	Player hand2;
	hand2.setName("Split hand");
	hand2.hit(myhand[1]);
	for (int i = 0; i < 2; i++) {
		myhand[i].setRank("");
		myhand[i].setSuit(' ');
		myhand[i].setValue(0);
	}
	numCards = 0;
	hit(temp);
	hit(deck.getCard(cardsDealt));
	hand2.hit(deck.getCard(cardsDealt));
	playTurn(deck, cardsDealt, bet);
	hand2.playTurn(deck, cardsDealt, bet);

	splitScore = hand2.getScore();
}

void Player::printCards() {
	if (name[name.length() - 1] == 's' || name[name.length() - 1] == 'S') {
		cout << name << "' cards:" << endl;
	}
	else {
		cout << name << "'s cards:" << endl;
	}
	for (int i = 0; i < numCards; i++) {
		cout << myhand[i].getSuit() << " " << myhand[i].getRank() << endl;
	}
}

void Player::printHeader() {
	if (splits == true) {
		cout << "Score: ";
		printScore();
	}
	else {
		cout << "Money: " << money << " Score: ";
		printScore();
	}
}

void Player::printScore() {
	if (ace == false || score == 21) {
		cout << getScore() << endl;
	}
	else {
		if (doubleD == true) {
			cout << getScore() << endl;
		}
		else {
			cout << lowScore << "/" << getScore() << endl;
		}
	}
}

void Player::viewStats() {
	cout << "Stats for " << name << endl;
	cout << "Games Played: " << gamesPlayed << endl << "High Score: " << highScore << endl;
	system("pause");
	system("cls");
}

int Player::checkInput(int numChoices, int choice) {
	// Initial check to make sure choice is valid
	while (!cin) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error. Please try again!" << endl;
		cin >> choice;
	}
	// Check to make sure choice is between valid values
	while (choice > numChoices || choice < 1) {
		cout << "Invalid Choice. Please enter a choice between 1 and " <<
			numChoices << endl;
		cin >> choice;
		while (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error. Please try again!" << endl;
			cin >> choice;
		}
	}
	return choice;
}

void Player::updateHighScore() {
	if (money > highScore) {
		highScore = money;
	}
}

int Player::playTurn(Pack deck, int & cardsDealt, int &bet) {
	while (getRoundOver() == false) {
		printHeader();
		printCards();
		cout << "1) Hit" << endl << "2) Stay" << endl;
		if (getHasHit() == false && money > bet) {
			cout << "3) Double Down" << endl;
		}
		if (getCard(0).getRank() == getCard(1).getRank() &&
			getHasHit() == false) {
			cout << "4) Split" << endl;
		}
	
		int choice;
		cin >> choice;
		if (getHasHit() == false && getCard(0).getRank() == getCard(1).getRank() &&
			getHasHit() == false) {
			choice = checkInput(4, choice);
		}
		else if (getHasHit() == false || getCard(0).getRank() == getCard(1).getRank() &&
			getHasHit() == false) {
			choice = checkInput(3, choice);
		}
		else {
			choice = checkInput(2, choice);
		}

		int numCards = 2;
		if (choice == 1) {
			hit(deck.getCard(cardsDealt)); 
			setHasHit(true);
			if (getScore() >= 21) {
				setRoundOver(true);
			}
		}
		else if (choice == 2) {
			setRoundOver(true);
		}
		else if (choice == 3) {
			doubleDown(deck, cardsDealt, bet);
			system("cls");
			setRoundOver(true);
		}
		else if (choice == 4) {
			split(deck, cardsDealt, bet);
			system("cls");
			setRoundOver(true);
		}
		system("cls");
	}
	printHeader();
	return cardsDealt;
}



/*
 Things to do:
 1. Check for any errors during testing
*/
