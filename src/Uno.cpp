#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

#include "headers/Player.h"
#include "headers/Deck.h"
#include "headers/GameManager.h"
#include "headers/CardUtils.h"
#include "headers/IOHelper.h"

#define Log(x) std::cout << x << std::endl
#define ClearBuffer() std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')

int const MIN_PLAYERS = 2;
int const MAX_PLAYERS = 10;
const char* STANDARD_DECK = "StandardDeck.txt";

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

bool ParsePlayerInput(
	std::shared_ptr<GameManager> gameManagerPtr,
	std::shared_ptr<Player> playerPtr,
	const std::string& input)
{
	std::istringstream iss(input);
	std::string commandType;
	iss >> commandType;

	if (IOHelper::ToLowerCase(commandType) == "play") {
		int cardPositionInHand;
		iss >> cardPositionInHand;

		std::string additionalCommand;
		iss >> additionalCommand;

		std::string unoWordCheck;
		iss >> unoWordCheck;

		return gameManagerPtr->FetchTurnCommands(playerPtr, cardPositionInHand,
			IOHelper::ToLowerCase(additionalCommand), IOHelper::ToLowerCase(unoWordCheck));
	}
	if (IOHelper::ToLowerCase(commandType) == "draw") {
		gameManagerPtr->DrawRequest(playerPtr);
		return true;
	}
	if (IOHelper::ToLowerCase(commandType) == "challenge") {
		//gameManagerPtr->ChallengeRequest(playerPtr);
		return true;
	}
	else {
		IOHelper::AddWarning("Invalid Command. Use Play [cardIndex] or Draw");
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
			ClearBuffer(); 
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
			Log("Player " << playerPtr->Id << " Won!\n");
			return true;
		}
	};
	return false;
}

int main(int argc, char** argv)
{
	// Initialize Game Deck
	const char* filename = (argc > 1) ? argv[1] : STANDARD_DECK;
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
	gameManager->StartGame();

	ClearBuffer();

	// Game Loop
	bool haveWinner = false;
	int turnPlayer = 0;
	while (!haveWinner) {
		IOHelper::Clear();
		IOHelper::ShowWarnings();

		gameManager->PrintLastDiscard();

		IOHelper::SeparationLine();

		Log("Player [" << players[turnPlayer]->Id << "] Turn:");
		players[turnPlayer]->PrintHand();

		IOHelper::SeparationLine();

		std::string input;
		IOHelper::GetLine(input);

		bool validTurn = ParsePlayerInput(gameManager, players[turnPlayer], input);
		if (validTurn) {
			gameManager->ExecuteTurn();
		}

		turnPlayer = gameManager->GetCurrentPlayer();
		haveWinner = CheckVictoryCondition(players);
	}
	std::cout << "Press Enter to exit...";
	std::cin.get();

	return EXIT_SUCCESS;
}
