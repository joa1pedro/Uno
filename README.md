## Uno
Uno Game By João Pedro Campos. Software Engineer at Kokku Games

![Uno!](https://raw.githubusercontent.com/joa1pedro/Uno/main/images/unoBackground.png?raw=true)

# Installation
Download the repository.

# Running the Game
Run Uno.exe in the Solution build folder. You can specify which deck you want to use passing it as arguments.
Not specifying is going to use the StandardDeck.txt file as default.
Deck files must be inside GameData Folder.

```bash
./Uno.exe MyCustomDeck.txt
```

# Creating a Custom Deck
You can create a fully custom deck with cards. Check [Game Data](https://github.com/joa1pedro/Uno/blob/main/GameData/GameData.txt)
and create a full deck with the corresponding card IDs listed there. You can also modify that file to make cards works differently.
The deck file must be inside the GameData folder together with the others. Use [Standard Deck](https://github.com/joa1pedro/Uno/blob/main/GameData/StandardDeck.txt) as example.
## Playing the Game
![Example](https://raw.githubusercontent.com/joa1pedro/Uno/main/images/example.png)

# Commands for playing
- For Playing a card `play [cardIndex] optional[Color] optional[uno]`.
- For Drawing a new card `draw`.

For playing a card in your hand you can just type play 
Ex.:
```bash
play [1]
```
If your card is a Wild Card. You are going to need tell the next color also. just specify the color after the card
Ex.:
```bash
play [2] yellow
```
If you have just 2 card in your hand, playing the next card will make you stay with just 1 card in hand.
In that case, if you don't want to be forced to draw 2 cards next turn, you need to say UNO! in the console too
Ex.:
```bash
play [3] uno
```
or
```bash
play [4] red uno
```
