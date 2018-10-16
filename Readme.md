# Design Document for Blackjack-cli

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

## Design Choices

### Structure of the Code

This game has one class, Blackjack, several helper functions functioning like
the static class in Java and a main file.

The Blackjack was designed to encapsulate all the game-related functions.
Each function representing a specific module in this game except the
print functions since I believe it is more organized to separate
each different print statements to avoid duplications.

The card was originally designed to be another class but it was found
to be not worth it. Instead, using helper functions inside a namespace
and representing the cards with simply integers is more efficient.

### Data Structures and Algorithms

For simplicity, most data are stored in vectors.

When calculating the score of Ace (which can be either 1 or 11),
greedy algorithm was used to decide the best strategy to
calculate the answer.

### Tooling

The choice of C++ is because personal familiarity with its standard
libraries and grammars.

Because this game is simply, only the standard libraries were used.