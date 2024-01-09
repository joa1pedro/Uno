#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include "Deck.h"
#include "Card.h"

std::string const GAMEDATA_PATH = "./GameData/GameData.txt";
std::string const GAMEDATA_FILE_PATH = "./GameData/";

// Shuffles the deck 
void Deck::Shuffle()
{   
	std::random_device rd;  // Use a random device to obtain a random seed
    std::mt19937 rng(rd());
	std::shuffle(std::begin(_cards), std::end(_cards), rng);
}

// Removes and returns the top card from the deck pile (last index of the vector).
Card Deck::DrawCard()
{
    if (!_cards.empty()) {
        Card card = _cards.back();
        _cards.pop_back();
        return card;
    } else {
		//TODO handle drawing on empty decks
    }
}

// Reads the GameData.txt file and creates a card for each defined, putting it on a map for latter adding it to a deck.
bool Deck::Validate()
{
	std::ifstream inputFile(GAMEDATA_PATH);

	if (!inputFile.is_open()) {
		std::cerr << "Error opening file: " << GAMEDATA_PATH << std::endl;
		return _isValid = false;
	}

	// Read and print the file content line by line
	std::string line;
	int i = 0;
	while (std::getline(inputFile, line)) {
		i++;
		//Ignoring empty lines and # commented lines
		if (!line.empty() && line[0] != '#') {
			if (ParseCharToCardType(line[0]) == CardType::Undefined ||
				ParseCharToCardValue(line[6]) == CardValue::Undefined) {
				std::cout << "Failed to validate line " << i << " " << line << "\n";
				return _isValid = false;
			}
			Card card {line.substr(0,5), ParseCharToCardType(line[0]), ParseCharToCardValue(line[6])};
			_cardMap.emplace(card.GetId(), card);
		}
	}

	std::cout << "Game Data Validated Successfully\n";
	return _isValid = true;
}

void Deck::Print()
{
	for (Card card : _cards)
	{
		card.Print();
	}
}

// Created a deck based on structured .txt data like StandardDeck.txt, based on previously validated Game Data
void Deck::Create(const char* fileName) {

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
		//Ignoring empty lines and # commented lines
		if (!line.empty() && line[0] != '#') {
			bool validCard = false;
			if (_cardMap.count(line)) {
				validCard = true;
				_cards.emplace_back(_cardMap[line]);
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

std::vector<Card> Deck::Get() {
	return _cards;
}