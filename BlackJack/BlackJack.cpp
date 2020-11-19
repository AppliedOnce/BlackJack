#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>;

struct Card
{
	std::string type = "";
	int value = 0;
};

std::vector<Card> InitDeck(std::vector<Card> deck);
void PrintDeck(std::vector<Card> deck);
void PrintMenu();
void PrintOptions();
void PlayGame(std::vector<Card> deck);
void PrintStatus(std::vector<Card> playerHand, std::vector<Card> dealerHand, int currentBet, int currentMoney, int dealerMoney);
void DrawCard(std::vector<Card>& hand, std::vector<Card>& deck);

void PlayRound(int bet, std::vector<Card> deck);
int GetRandomInt(int max);
int SumOfCards(std::vector<Card> hand);

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	std::vector<Card> deck(52);
	deck = InitDeck(deck);
	std::random_shuffle(deck.begin(), deck.end());

	int playerChoice = 0;
	bool invalidChoice = false;

	do
	{
		PrintMenu();
		std::cin >> playerChoice;

		switch (playerChoice)
		{
		case 1:
			PlayGame(deck);
			invalidChoice = false;
			break;
		case 2:
			invalidChoice = false;
			break;
		default:
			std::cout << "Invalid choice. Try again." << std::endl;
			invalidChoice = true;
			break;
		}
	} while (invalidChoice);
}

void PlayGame(std::vector<Card> deck)
{
	bool gameOver = false;

	const int startMoney = 100;
	int currentMoney = startMoney;
	int dealerMoney = startMoney;
	int currentBet = 10;
	
	std::cout << "---------------------------------" << std::endl << std::endl;

	do
	{
		std::cout << "Current money: " << currentMoney << std::endl;
		std::cout << "Dealers money: " << dealerMoney << std::endl << std::endl;
		std::cout << "How much do you want to bet: ";
		std::cin >> currentBet;

		PlayRound(currentBet, deck);
	} while (!gameOver);

	std::cout << "---------------------------------" << std::endl << std::endl;
}

void PlayRound(int bet, std::vector<Card> deck)
{
	char playerInput = ' ';
	int playerCardSum = 0;
	int dealerCardSum = 0;
	bool stay = false;

	std::vector<Card> playerHand;
	std::vector<Card> dealerHand;

	do
	{
		std::cout << "Current sum of your cards: " << playerCardSum << std::endl << std::endl;
		PrintOptions();
		std::cin >> playerInput;
		playerInput = tolower(playerInput);
		switch (playerInput)
		{
		case 'd':
			DrawCard(playerHand, deck);
			break;
		case 's':
			break;
		case 'f':
			break;
		default:
			std::cout << "Invalid choice. Try again." << std::endl;
			break;
		}

	} while ((SumOfCards(playerHand) <= 21) || stay);
}

int SumOfCards(std::vector<Card> hand)
{
	int sumOfCards = 0;
	for (int i = 0; i < hand.size(); i++)
	{
		sumOfCards += hand.at(i).value;
	}
	return sumOfCards;
}

void PrintMenu()
{
	std::cout << "============================" << std::endl;
	std::cout << "|| Welcome to Black Jack! ||" << std::endl;
	std::cout << "============================" << std::endl << std::endl;
	std::cout << "       1. Play game         " << std::endl;
	std::cout << "       2. Quit game         " << std::endl;
}

void PrintOptions()
{
	std::cout << "D. Draw a card." << std::endl;
	std::cout << "S. Stay with current cards." << std::endl;
	std::cout << "F. Fold cards (lose round)." << std::endl;
}

void PrintStatus(std::vector<Card> playerHand, std::vector<Card> dealerHand, int currentBet, int currentMoney, int dealerMoney)
{
	int dealerValue = 0;
	int playerValue = 0;

	if (dealerHand.size() > 1)
	{
		for (int i = 0; i < dealerHand.size(); i++)
		{
			dealerValue += dealerHand.at(i).value;
		}
		std::cout << "Dealer has: " << dealerValue << std::endl;
	}

	if (playerHand.size() > 0)
	{
		for (int i = 0; i < playerHand.size(); i++)
		{
			playerValue += playerHand.at(i).value;
		}
		std::cout << "You got: " << playerValue << std::endl;
	}
}

void DrawCard(std::vector<Card>& hand, std::vector<Card>& deck)
{
	int randomNumber = GetRandomInt(deck.size() - 1);
	hand.push_back(deck.at(randomNumber));
	std::cout << "Drew card: " << deck.at(randomNumber).type << deck.at(randomNumber).value << std::endl;
	deck.erase(deck.begin() + randomNumber);
}

std::vector<Card> InitDeck(std::vector<Card> deck)
{
	for (int i = 0; i < deck.size(); i++)
	{
		// card 1-13
		if (i < (deck.size() + 1) / 4)
		{
			// 3 = hearts
			deck.at(i).type = 3;
			if (i % 13 < 10)
				deck.at(i).value = (i % 13) + 1;
			else
				deck.at(i).value = 10;
		}
		// card 14-26
		else if (i < (deck.size() + 1) / 4 * 2 && i >= (deck.size() + 1) / 4)
		{
			// 4 = diamonds
			deck.at(i).type = 4;
			if (i % 13 < 10)
				deck.at(i).value = (i % 13) + 1;
			else
				deck.at(i).value = 10;
		}
		// card 27-39
		else if (i < (deck.size() + 1) / 4 * 3 && i >= (deck.size() + 1) / 4 * 2)
		{
			// 5 = clubs
			deck.at(i).type = 5;
			if (i % 13 < 10)
				deck.at(i).value = (i % 13) + 1;
			else
				deck.at(i).value = 10;
		}
		// card 40-52
		else if (i < (deck.size() + 1) / 4 * 4 && i >= (deck.size() + 1) / 4 * 3)
		{
			// 6 = spades
			deck.at(i).type = 6;
			if (i % 13 < 10)
				deck.at(i).value = (i % 13) + 1;
			else
				deck.at(i).value = 10;
		}
	}

	return deck;
}

void PrintDeck(std::vector<Card> deck)
{
	for (int i = 0; i < deck.size(); i++)
	{
		std::cout << "Card " << (i + 1) << ": Type: " << deck.at(i).type << ", Value: " << deck.at(i).value << std::endl;
	}
}

int GetRandomInt(int max)
{
	int randomNumber = rand() % max + 1;
	return randomNumber;
}