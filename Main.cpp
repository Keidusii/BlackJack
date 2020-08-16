#include <iostream>
#include "Player.h"
#include "Card.h"
#include "Dealer.h"
#include "Pack.h"
#include <string>
#include <iomanip>
using namespace std;

string setup();
void game(string name);
int validateBet(Player & player, int bet);
void reset(Player & player, Dealer & dealer, int & cardsDealt);
void resetStats(Player & player, Dealer & Dealer, int & cardsDealt);
void compareScores(Player & p1, Dealer & dealer, bool blackjack, bool insurance,
	bool dealerBJ, int bet, int insuranceBet, int score);

int main() {
	string name = setup();
	game(name);
	return 0;
}

string setup() {
	cout << "Welcome to Blackjack!" << endl << "Enter Name: " << endl;
	string name;
	cout << "Name: ";
	cin >> name;
	cout << endl;
	while (!cin) {
		cin.clear();
		cin.ignore();
		cout << "Invalid Input, Please try again" << endl;
		cin >> name;
	}
	system("cls");
	return name;
}

void game(string name) {
	Player p1;
	Dealer dealer;
	p1.setName(name);
	Pack deck;
	deck.importCards();
	bool gameOver = false;

	//play game
	while (gameOver == false) {
		cout << "Money: " << p1.getMoney() << endl << "Bet: " << endl;
		// Setting the Bet
		int bet;
		cin >> bet;
		bet = validateBet(p1, bet);
		p1.setMoney(p1.getMoney() - bet);
		deck.shuffle();

		// Intialization of game variables
		int cardsDealt = 0;
		bool blackjack = false;
		bool insurance = false;
		bool dealerBJ = false;
		int insuranceBet = 0;

		// Intial Dealing of cards
		for (int i = 0; i < 2; i++) {
			p1.hit(deck.getCard(cardsDealt));
			dealer.hit(deck.getCard(cardsDealt));
		}

		// Checking for Blackjack and Insurance
		blackjack = p1.checkBlackjack();
		if (blackjack == false && dealer.getHand(1).getRank() == "A") {
			insurance = dealer.insurance(p1, bet, insuranceBet);
			dealerBJ = dealer.checkBlackjack();
			if (dealerBJ == false && insurance == true) {
				cout << "Dealer does not have Blackjack. Insurance Bet lost." << endl;
				system("pause");
				system("cls");
			}
		}
		
		// Dealer and Player play turns
		if (blackjack == false && dealerBJ == false) {
			p1.playTurn(deck, cardsDealt, bet);
			playTurn(dealer, deck, cardsDealt);
		}
		p1.printHeader();
		p1.printCards();
		dealer.printCards();
		dealer.printScore();
		
		if (p1.getSplit() == true) {
				compareScores(p1, dealer, blackjack, insurance,
					dealerBJ, bet, insuranceBet, p1.getScore());
				compareScores(p1, dealer, blackjack, insurance,
					dealerBJ, bet, insuranceBet, p1.getSplitScore());

		}
		else {
			compareScores(p1, dealer, blackjack, insurance,
				dealerBJ, bet, insuranceBet, p1.getScore());
		}

		// Updating stats and High Score
		p1.updateHighScore();
		p1.setGamesPlayed(p1.getGamesPlayed() + 1);
		system("pause");
		system("cls");
		p1.printHeader();
		if (p1.getMoney() == 0) {
			cout << "GAME OVER! You ran out of money." << endl;
			p1.viewStats();
			int playAgain;
			cout << "Play Again?" << endl << "1) Yes" << endl << "2) No" << endl;
			cin >> playAgain;
			playAgain = p1.checkInput(2, playAgain);
			if (playAgain == 1) {
				resetStats(p1, dealer, cardsDealt);
			}
			else {
				gameOver = true;
			}
		}
		else {
			cout << "1) Play again" << endl << "2) View Stats " << endl << "3) Quit" << endl;
			int restart;
			cin >> restart;
			restart = p1.checkInput(3, restart);
			if (restart == 2) {
				while (restart == 2) {
					p1.viewStats();
					p1.printHeader();
					cout << "1) Play again" << endl << "2) View Stats " << endl << "3) Quit" << endl;
					cin >> restart;
					restart = p1.checkInput(3, restart);
				}
			}
			if (restart == 1) {
				reset(p1, dealer, cardsDealt);
			}
			else {
				gameOver = true;
			}
		}
		system("cls");
	}
}

int validateBet(Player & player, int bet) {
	while (!cin) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error. Please try again!" << endl;
		cin >> bet;
	}
	while (bet > player.getMoney()) {
		cout << "Invalid bet. Please enter a bet less than $" <<
			player.getMoney() << endl;
		cin >> bet;
		while (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error. Please try again!" << endl;
			cin >> bet;
		}
	}
	return bet;
}

void reset(Player & player, Dealer & dealer, int & cardsDealt) {
	player.reset();
	dealer.reset();
	cardsDealt = 0;
}

void resetStats(Player & player, Dealer & dealer, int & cardsDealt) {
	reset(player, dealer, cardsDealt);
	player.setMoney(1000);
}

void compareScores(Player & p1, Dealer & dealer, bool blackjack, bool insurance,
	bool dealerBJ, int bet, int insuranceBet, int score) {
	// Comparing Scores and paying bets
	int winnings = 0;
	if (blackjack == true && dealer.checkBlackjack() == false) {
		system("cls");
		p1.printCards();
		dealer.printCards();
		dealer.printScore();
		cout << "BLACKJACK! You Win. You had 21. The dealer had " << dealer.getScore() << endl;
		winnings = 2.5 * (double)bet;
		cout << "You win $" << winnings << endl;
		p1.setMoney(p1.getMoney() + winnings);
	}
	else if (insurance == true && dealerBJ == true) {
		cout << "Dealer has a BlackJack. You made an insurance bet." << endl
			<< "You win $" << bet << endl;
		winnings = 2 * insuranceBet + insuranceBet;
		p1.setMoney(p1.getMoney() + winnings);
	}
	else if (score > 21) {
		cout << "BUST! You lose. You had " << score << ". The dealer had " << dealer.getScore() << endl;
	}
	else if (score > dealer.getScore()) {
		cout << "You Win. You had " << score << ". The dealer had " << dealer.getScore() << endl;
		winnings = 2 * bet;
		cout << "You win $" << winnings << endl;
		p1.setMoney(p1.getMoney() + winnings);
	}
	else if (dealer.getScore() > 21) {
		cout << "You Win. You had " << score << ". The dealer had " << dealer.getScore() << endl;
		winnings = 2 * bet;
		cout << "You win $" << winnings << endl;
		p1.setMoney(p1.getMoney() + winnings);
	}
	else if (score < dealer.getScore()) {
		cout << "You Lose. You had " << p1.getScore() << ". The dealer had " << dealer.getScore() << endl;
	}
	else {
		cout << "Push. Both you and the dealer had " << score << endl;
		p1.setMoney(p1.getMoney() + bet);
	}
}