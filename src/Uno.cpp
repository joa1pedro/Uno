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

std::vector<std::shared_ptr<Player>> InitilizePlayers(int numberOfPlayers)
{
	std::vector<std::shared_ptr<Player>> players;
	for (int i = 0; i < numberOfPlayers; i++) {
		players.emplace_back(std::move(std::make_shared<Player>(i)));
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

bool GetPlayerInputCommand(
	std::shared_ptr<GameManager> gameManagerPtr,
	std::shared_ptr<Player> playerPtr,
	const std::string& input)
{
	std::istringstream iss(input);
	std::string commandType;
	iss >> commandType;

	if (toLowerCase(commandType) == "play") {
		int cardPositionInHand;
		iss >> cardPositionInHand;

		std::string additionalCommand;
		iss >> additionalCommand;

		std::string unoWordCheck;
		iss >> unoWordCheck;
		
		if (toLowerCase(unoWordCheck) == "uno") {
			// TODO treat uno word
		}

		if (cardPositionInHand >= playerPtr->Hand.size()) {
			Log("Invalid Card Selected.");
			return false;
		}

		PlayableCard* cardPtr = &playerPtr->Hand[cardPositionInHand];
		return gameManagerPtr->FetchTurnCommands(playerPtr.get(), cardPtr, additionalCommand);
	}
	if (toLowerCase(commandType) == "draw") {
		int numCards = 1;
		DrawCommand drawCommand { gameManagerPtr, playerPtr };
		drawCommand.Execute();
		return true;
	}
	else {
		Log("Invalid command.");
		return false;
	}
}

// Grabs input for the number of players, clamped by MIN_PLAYERS - MAX_PLAYERS 
int GetNumberOfPlayers() {
	int numberOfPlayers;
	bool validInput = false;

	while (!validInput) {
		std::cout << "How Many Players? (2 - 10)\n";
		std::cin >> numberOfPlayers;

		if (std::cin.fail() || !ValidPlayersClamp(numberOfPlayers)) {
			std::cin.clear(); // Clear error flag
			ClearBuffer(); // Discard invalid input
			std::cout << "Invalid input. Please enter a valid number between 2 and 10.\n";
		}
		else {
			validInput = true;
		}
	}

	return numberOfPlayers;
}

bool CheckVictoryCondition(std::vector<std::shared_ptr<Player>>& players) {
	for (const std::shared_ptr<Player>& playerPtr : players)
	{
		if (playerPtr->Hand.size() == 0) {
			std::cout << "Player " << playerPtr->Id << " Won!";
			return true;
		}
	};
	return false;
}

int main(int argc, char** argv)
{
	// Initialize Game Deck
	const char* filename = (argc > 1) ? argv[1] : "StandardDeck.txt";
	std::shared_ptr<Deck> deckPtr = std::make_shared<Deck>( filename );
	if (!deckPtr->IsValid()) {
		return EXIT_FAILURE;
	}

	// Initialize Players
	int numberOfPlayers = GetNumberOfPlayers(); 
	std::vector<std::shared_ptr<Player>> players { InitilizePlayers(numberOfPlayers) };

	// Initialize GameManager
	std::shared_ptr<GameManager> gameManager = std::make_shared<GameManager>(deckPtr, players);

	// Game prep initialization
	gameManager->ShuffleDeck();
	gameManager->DistributeCards();
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
			turnPlayer = gameManager->PassTurn();
		}

		haveWinner = CheckVictoryCondition(players);
	}
	
	return EXIT_SUCCESS;
}
