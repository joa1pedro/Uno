#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <random>
#include <array>
#include "headers/PlayableCard.h"
#include "headers/Deck.h"
#include "headers/Card.h"
#include "headers/CardUtils.h"

std::string const GAMEDATA_PATH = "./GameData/GameData.txt";
std::string const GAMEDATA_FILE_PATH = "./GameData/";
int const MAX_CARDS_IN_DECK = 200;

// Shuffles the deck 
void Deck::Shuffle()
{   
	std::random_device rd;  // Use a random device to obtain a random seed
    std::mt19937 rng(rd());
	std::shuffle(std::begin(_cards), std::end(_cards), rng);
}

void Deck::ResetDeckFromDiscardPile()
{
	if (_discardPile.empty()) {
		throw std::runtime_error("No cards in discard pile to reset deck");
	}
	_cards.insert(_cards.end(), _discardPile.begin(), _discardPile.end());

	_discardPile.clear();
	Shuffle();
}

// Removes and returns the top card from the deck pile (last index of the vector).
PlayableCard Deck::DrawCard()
{
    if (_cards.empty()) {
		ResetDeckFromDiscardPile();
    } 

	PlayableCard card = _cards.back();
	_cards.pop_back();
	return card;
}

// Adds a card to the discard pile
void Deck::Discard(const PlayableCard& card)
{
	_discardPile.push_back(card);
}

PlayableCard Deck::LastDiscard()
{
	return _discardPile.back();
}

void Deck::Print()
{
	for (PlayableCard card : _cards)
	{
		card.Print();
	}
}

std::vector<PlayableCard> Deck::Get() {
	return _cards;
}

bool IsValidActions(std::array<CardAction, MAX_ACTIONS_PER_CARD> actions)
{
	for (int i = 0; i < MAX_ACTIONS_PER_CARD; i++) {
		if (actions[i] != CardAction::Undefined) {
			return true;  // Found at least one valid action
		}
	}
	return false;  // No valid action found
}

// Reads the GameData.txt file and creates a card for each defined, putting it on a map for latter adding it to a deck.
bool Deck::Validate()
{
	// Early exit if deck was validated previously
	if (IsValid) return true;

	std::ifstream inputFile(GAMEDATA_PATH);

	if (!inputFile.is_open()) {
		std::cerr << "Error opening file: " << GAMEDATA_PATH << std::endl;
		return IsValid = false;
	}

	std::string line;
	int i = 0;
		while (std::getline(inputFile, line)) {
		i++;
		//Ignoring empty lines and # commented lines
		if (!line.empty() && line[0] != '#') {
			std::istringstream iss(line);
			std::string id, type, value, actionstr;

			//':' as a delimiter to extract each part
			std::getline(iss, id, ':');
			std::getline(iss, type, ':');
			std::getline(iss, value, ':');
			std::getline(iss, actionstr, ':'); 

			// Try parse the values from GameData
			CardType parsedType = CardUtils::ParseStrToCardType(type);
			CardValue parsedValue = CardUtils::ParseStrToCardValue(value);	

			// Parsing the array of actions
			std::array<CardAction, MAX_ACTIONS_PER_CARD> actions {};
			int j = 0;
			if (actionstr.empty()) {
				std::cout << "Failed to validate line " << i << " " << line << " - No actions.\n";
				return IsValid = false;
			}

			for (char c : actionstr) {
				if (c == ' ') continue;
				if (j > MAX_ACTIONS_PER_CARD-1) {
					std::cout << "Failed to validate line " << i << " " << line << " - Too many actions.\n";
					return IsValid = false;
				}
				actions[j] = CardUtils::ParseCharToCardAction(c);
				j++;
			}

			// Validating if theres a Card Type, A CardValue and at least 1 valid CardAction
			if (parsedType == CardType::Undefined || parsedValue == CardValue::Undefined /*|| IsValidActions(actions))*/) {
				std::cout << "Failed to validate line " << i << " " << line << " - Invalid data.\n";
				return IsValid = false;
			}

			// Correctly parsed, adding it to a table for later use
			Card card {stoi(id), parsedType, parsedValue, actions};
			_cardMap.emplace(card.Id(), card);
		}
	}

	std::cout << "Game Data Validated Successfully\n";
	return IsValid = true;
}

// Created a deck based on structured .txt data like StandardDeck.txt, based on previously validated Game Data
void Deck::Create(const char* fileName) {
	_cards.clear();
	_cards.reserve(MAX_CARDS_IN_DECK);

	std::string filePath = GAMEDATA_FILE_PATH;
	std::ifstream inputFile(filePath.append(fileName));

	// Check if the file is open
	if (!inputFile.is_open()) {
		std::cerr << "Error opening file: " << filePath.append(fileName) << std::endl;
		return;
	}

	// Read and print the file content line by line
	std::string line;
	int i = 0;
	while (std::getline(inputFile, line)) {
		i++;
		if (i > MAX_CARDS_IN_DECK) {
			std::cout << "Max number of cards reached: " << MAX_CARDS_IN_DECK << "\n";
			return;
		}

		//Ignoring empty lines and # commented lines
		if (!line.empty() && line[0] != '#') {
			bool validCard = false;
			if (_cardMap.count(stoi(line))) {
				validCard = true;
				_cards.emplace_back(_cardMap[stoi(line)]);
			}
			if (validCard = false) {
				std::cout << "Invalid Card: " << line << i << "\n";
				return;
			}
		}
	}
	std::cout << "Deck Created Successfully: " << fileName << "\n";
	return;
}