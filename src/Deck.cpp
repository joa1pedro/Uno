#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <random>
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
	_cards.insert(_cards.end(), std::make_move_iterator(_discardPile.begin()), std::make_move_iterator(_discardPile.end()));

	_discardPile.clear();
	Shuffle();
}

// Removes and returns the top card from the deck pile (last index of the vector).
Card Deck::DrawCard()
{
    if (_cards.empty()) {
		ResetDeckFromDiscardPile();
    } 

	Card card = std::move(_cards.back());
	_cards.pop_back();
	return card;
}

void Deck::Discard(Card card)
{
	_discardPile.push_back(std::move(card));
}

Card Deck::LastDiscard()
{
	return _discardPile.back();
}

void Deck::Print()
{
	for (Card card : _cards)
	{
		card.Print();
	}
}

std::vector<Card> Deck::Get() {
	return _cards;
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
	std::vector<CardAction> actions;
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
			actions.clear();
			for (char c : actionstr) {
				if (c == ' ') continue;
				actions.emplace_back(CardUtils::ParseCharToCardAction(c));
			}

			if (parsedType == CardType::Undefined || parsedValue == CardValue::Undefined || !IsValidActions(actions)) {
				std::cout << "Failed to validate line " << i << " " << line << "\n";
				return IsValid = false;
			}

			// Correctly parsed, adding it to a table for later use
			Card card {id, parsedType, parsedValue, actions};
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