# Blackjack-cli

A single-player simplified Blackjack game running in terminal.

## Build

Under the directory of source codes,

```bash
make all
```

With all dependencies installed, `make` should build an
executable called "Blackjack"

## Usage

In the same directory of executable,

```bash
./Blackjack
```

Follow the instruction printed and type the single letter
corresponding to the specific option.

The main menu:
```
Welcome to simplified Blackjack in cli.
Options:
  s: Start the game
  q: Quit
```

This is the main menu of this game. After starting the
game or finishing one round, player will be prompted with
this menu.

Type "s" or "q" and press "Enter" for each option.

The game:
```
Welcome to a new game.
Now we deal first 4 cards
Player received card: 7 of spades (7)
Player received card: Jack of clubs (10)
Cards of Player: 7 of spades (7), Jack of clubs (10)
Cards of Dealer: 10 of diamonds (10) and a hidden card.

* Player's score: 17
* Dealer's face-up card: 10 of diamonds (10)

Card used: 4, Card remaining: 48

Waiting for player...
Options: Status(t), View Dealer's card(d), View Player's card(p), Hit(h), Stand(s)
```

This is how game looks like. Player has 5 different options for each step.

## Rule (Simplified Blackjack)

The rule is same as the one of the famous Blackjack game except
this game does not support betting, doubling, splitting
considering it is only a single-player game.
