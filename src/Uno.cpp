#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

#include "headers/Player.h"
#include "headers/GameState.h"
#include "headers/Deck.h"
#include "headers/CardUtils.h"
#include "headers/GameManager.h"
#include "headers/Command.h"
#include "Commands/DrawCommand.h"


// MACROS
#define Log(x) std::cout << x << std::endl
#define ClearBuffer() std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')

int const MIN_PLAYERS = 2;
int const MAX_PLAYERS = 10;

void ClearScreen() {
	// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
	std::cout << "\x1B[2J\x1B[H";
}

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

std::vector<std::unique_ptr<Player>> InitilizePlayers(int numberOfPlayers)
{
	std::vector<std::unique_ptr<Player>> players;
	for (int i = 0; i < numberOfPlayers; i++) {
		players.emplace_back(std::move(std::make_unique<Player>(i)));
	}
	return players;
}

// Convert each character in the string to lowercase
std::string toLowerCase(const std::string& input) 
{
	std::string result = input;
	for (char& c : result) {
		c = std::tolower(c);
	}
	return result;
}

bool GetPlayerInputCommand(std::unique_ptr<GameManager>& gameManager, std::unique_ptr<Player>& player, const std::string& input)
{
	std::istringstream iss(input);
	std::string commandType;
	iss >> commandType;

	if (toLowerCase(commandType) == "play") {
		int cardPositionInHand;
		iss >> cardPositionInHand;

		std::string unoWordCheck;
		std::string additionalCommand;

		iss >> additionalCommand;

		iss >> unoWordCheck;
		if (toLowerCase(unoWordCheck) == "uno") {
			// TODO treat uno word
		}

		if (cardPositionInHand >= player->Hand.size()) {
			Log("Invalid Card Selected.");
			return false;
		}

		PlayableCard* cardPtr = &player->Hand[cardPositionInHand];
		return gameManager->FetchTurnCommands(player.get(), cardPtr, additionalCommand);
	}
	if (toLowerCase(commandType) == "draw") {
		int numCards = 1;
		std::make_unique<DrawCommand>(gameManager.get(), player.get())->Execute();
		return true;
	}
	else {
		Log("Invalid command.");
		return false;
	}
}

int GetNumberOfPlayers()
{
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
			ClearBuffer();
		}
	}
	return numberOfPlayers;
}

bool CheckVictoryCondition(std::vector<std::unique_ptr<Player>>& players) {
	std::for_each(players.begin(), players.end(), [](const std::unique_ptr<Player>& ptr) {
		if (ptr->Hand.size() == 0) {
			std::cout << "Player " << ptr->Id << "Won!";
			return true;
		}
	});
	return false;
}

int main(int argc, char** argv)
{
	// Initialize Game Deck
	const char* filename = (argc > 1) ? argv[1] : "StandardDeck.txt";
	Deck deck { filename };
	if (!deck.IsValid) {
		return EXIT_FAILURE;
	}

	// Initialize Players
	int numberOfPlayers = GetNumberOfPlayers(); // <- Grabs input
	std::vector<std::unique_ptr<Player>> players = std::vector< std::unique_ptr<Player>>(InitilizePlayers(numberOfPlayers));

	// Initialize GameManager
	std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>(std::make_shared<Deck>(deck), players.size());

	// Game prep initialization
	gameManager->ShuffleDeck();
	gameManager->DistributeCards(players);
	gameManager->DiscardFirst(); 
	
	ClearBuffer();

	// Game Loop
	bool haveWinner = false;
	int turnPlayer = 0;
	while (!haveWinner) {
		std::string input;

		ClearScreen();
		std::cout << "Last Discard:";
		gameManager->PrintLastDiscard();
		Log("----------");
		Log("Player [" << players[turnPlayer]->Id << "] Turn:");
		players[turnPlayer]->PrintHand();
		Log("----------");
		std::getline(std::cin, input);

		bool validTurn = GetPlayerInputCommand(gameManager, players[turnPlayer], input);
		if (validTurn) {
			gameManager->ExecuteTurn();
			turnPlayer = gameManager->GetNextTurnPlayerIndex();
		}

		haveWinner = CheckVictoryCondition(players);
	}
	
	return EXIT_SUCCESS;
}
