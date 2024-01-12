#include <iostream>
#include <fstream>
#include <sstream>
#include "headers/Player.h"
#include "headers/GameState.h"
#include "headers/Deck.h"
#include "headers/CardUtils.h"
#include "headers/GameManager.h"
#include "headers/Command.h"
#include "headers/PlayCommand.h"
#include "headers/DrawCommand.h"

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

void StartGame()
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

std::string toLowerCase(const std::string& input) {
	std::string result = input;

	// Convert each character in the string to lowercase
	for (char& c : result) {
		c = std::tolower(c);
	}

	return result;
}

std::unique_ptr<Command> parsePlayerInput(GameManager& gameManager, Player player, const std::string& input) {
	std::istringstream iss(input);
	std::string commandType;
	iss >> commandType;

	//if (toLowerCase(commandType) == "play") {
	//	std::string card;
	//	iss >> card;
	//	return std::make_unique<PlayCommand>(gameManager, card, player);
	//}
	if (toLowerCase(commandType) == "draw") {
		int numCards;
		iss >> numCards;
		return std::make_unique<DrawCommand>(numCards);
	}
	else {
		std::cout << "Invalid command." << std::endl;
		return nullptr;
	}
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
	deck.Print();
	Log("CardDrawn -----");
	deck.DrawCard().Print();
	Log("-----");

	Log("Discarded -----------");
	deck.Discard(deck.DrawCard());
	deck.Print();


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

	auto players = InitilizePlayers(numberOfPlayers);
	GameManager gameManager{};
	std::string input;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, input);
	parsePlayerInput(gameManager, players[0], input);
	return EXIT_SUCCESS;
}
