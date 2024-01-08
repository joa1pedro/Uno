#include <iostream>
#include "Player.h"
#include "Uno.h"
#include "GameState.h"

#define Log(x) std::cout << x << std::endl;

int MIN_PLAYERS = 2;
int MAX_PLAYERS = 10;

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


void InitializeAndValidateGameDeck()
{
	// TODO Implement
	// This will grab info about the game data and create the deck based in the decks you create
}

std::vector<Player> InitilizePlayers(int numberOfPlayers)
{
	std::vector<Player> players;
	for (int i = 0; i < numberOfPlayers; i++) {
		Player player {i};
		players.push_back(player);
		Log(player._id);
	}
	return players;	
}

int main()
{
	InitializeAndValidateGameDeck();

	// Get the number of Players, clamped by MIN and MAX players
	bool validInput = false;
	int numberOfPlayers;
	while (!validInput) {
		Log("How Many Players?\n");
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
}
