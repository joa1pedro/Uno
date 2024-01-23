# Uno
Uno Game By João Pedro Campso. Software Engineer at Kokku Games

Uno Design Brief Documentation https://docs.google.com/document/d/1DE0XVD5ow9MUvyQOELAya3qO22uv0ZlD6QLS5TnFI0U/edit

## Installation
Download the repository.

## Running the Game
Run the .exe Uno. You can specify which deck you want to use passing it as arguments.
Not specifying is going to use the StandardDeck.txt file as default.
Deck files must be inside GameData Folder.

```bash
./Uno.exe MyCustomDeck.txt
```

## Possible Commands for playing
```bash
play [cardIndex] optionalTypeOverride optionalUnoYell
draw
```

## Playing the Game
![Playing Example](https://github.com/joa1pedro/Uno/tree/main/images/example.png?raw=true)

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

