#include <iostream>
#include <fstream>
#include "headers/Player.h"
#include "headers/GameState.h"
#include "headers/Deck.h"
#include "headers/CardUtils.h"

#define Log(x) std::cout << x << std::endl;

int const MIN_PLAYERS = 2;
int const MAX_PLAYERS = 10;

bool ValidPlayersClamp(int value)
{
	if (value < MIN_PLAYERS) {
		Log("The minimum number of Players to play is 2!");
		return false;
	}
	else if (value > MAX_PLAYERS) {
		Log("The maximum number of Players is 10!");
		return false;
	}
	else return true;
}

void StartGame(/*std::vector<Players>&, Deck deck*/)
{
	// TODO Implement
}

std::vector<Player> InitilizePlayers(int numberOfPlayers)
{
	std::vector<Player> players;
	for (int i = 0; i < numberOfPlayers; i++) {
		players.emplace_back(i);
		Log(players[i].Id);
	}
	return players;
}

int main(int argc, char** argv)
{
	// Initialize Game Deck

	const char* filename = (argc > 1) ? argv[1] : "StandardDeck.txt";
	Deck deck { filename };
	if (!deck.IsValid) {
		return EXIT_FAILURE;
	}

	deck.Shuffle();
	deck.DrawCard();
	deck.Discard(deck.Get().back());
	deck.ResetDeckFromDiscardPile();

	// Get the number of Players, clamped by MIN and MAX players
	bool validInput = false;
	int numberOfPlayers;
	while (!validInput) {
		Log("How Many Players? (2 - 10)\n");
		std::cin >> numberOfPlayers;

		if (ValidPlayersClamp(numberOfPlayers)) {
			validInput = true;
		}
		else {
			std::cin.clear();			
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	InitilizePlayers(numberOfPlayers);
	//StartGame();
	return EXIT_SUCCESS;
}
