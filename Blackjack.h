/*
 * Header for blackjack class
 * 
 * Responsible for the main functions of the game
 * 
 * This is a single-player version of the card game Blackjack
 * without betting
 */ 

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

#include "card.h" // helper functions for cards

/*
 * A class for a card game Blackjack
 */
class Blackjack {
  private:
  static const int DECK_SZ  = 52;     // 52 cards in our deck
  static const int DECK_BEG = 1;      // index begin with 1

  static const int GOAL = 21;         // 21 goal
  static const int DEALER_STAND = 17; // dealer must stand
  static const int ACE_SCORE = 11;    // can count ace as 11;

  static const int INITIAL_CARDS = 4; // start with 4 cards

  unsigned int idx, idxDealer, idxPlayer; // idx of current deck
  unsigned int valDealer, valPlayer;      // the value of the cards in hand
  unsigned int aceDealer, acePlayer;      // true if specific person has ace

  std::vector<int> deck;       // array storing the deck
  std::vector<int> dealerHand; // array storing the cards
  std::vector<int> playerHand; // array storing the cards

  /*
   * Use std library to shuffle the deck
   * Parameter: None
   * Return: None
   */
  void shuffle() {
    std::shuffle(deck.begin(), deck.end(), std::mt19937{std::random_device{}()});
  }

  /*
   * Calculate the score (closest to 21)
   * Parameter: isPlayer - true to calculate player's
   *                     - false to calculate dealer's
   * Return score of the person requested
   */
  int getScore(bool isPlayer) const;

  /*
   * Reset the game
   * Parameter: None
   * Return: None
   */
  void reset();

  /*
   * Give a card to a person
   * Parameter: isPlayer - true if player
   *                       false if dealer
   * Return: true - success
   *         false - failure
   */
  bool giveCard(bool isPlayer);

  /*
   * Give dealer a card
   * Parameter: None
   * Return: true - success
   *         false - failure
   */
  bool dealerGetCard() {
    return giveCard(0);
  }

  /*
   * Give player a card
   * Parameter: None
   * Return: true - success
   *         false - failure
   */
  bool playerGetCard() {
    return giveCard(1);
  }

  /*
   * Give player and dealer 4 cards as beginning
   * Parameter: None
   * Return: 0 - continue the game
   *         1 - player has a natural
   *        -1 - delear has a natural
   *         2 - both have natural
   */
  int deal();

  /*
   * Player hit
   * Give player one more card
   * Parameter: None
   * Return: true - success
   *         false - failure
   */
  bool hit() {
    return playerGetCard();
  }

  /*
   * Player stand
   * Player stops to receive card and see the result
   * Parameter: None
   * Return: true - success
   *         false - failure
   */
  bool stand();

  /*
   * Check if the player wins or loses
   * Parameter: stand - if player stands
   * Return: 0 - the game should continue
   *         1 - player wins
   *        -1 - player loses
   */
  int check(bool stand) const;

  /* print functions */

  /*
   * print the welcome
   * Parameter: None
   * Return: None
   */
  void printWelcome() const;

  /*
   * print the prompt
   * Parameter: None
   * Return: None
   */
  void printPrompt() const;

  /*
   * print the current gaming status
   * format: player score - dealer hand - card used - card remaining
   * Parameter: None
   * Return: None
   */
  void printStatus() const;

  /*
   * print the cards in dealer's hand
   * Parameter: stand - if player stands
   * Return: None
   */
  void printDealer(bool stand) const;

  /*
   * print the cards in player's hand
   * Parameter: None
   * Return: None
   */
  void printPlayer() const;

  /*
   * print the result
   * Parameter: None
   * Return: None
   */
  void printResult() const;

  /* end of print functions */

  public:
  /*
   * 0-art constructor
   * Parameter: None
   */
  Blackjack(): idx(0), idxDealer(0), idxPlayer(0),
               valDealer(0), valPlayer(0),
               aceDealer(0), acePlayer(0),
               deck(std::vector<int>(DECK_SZ)), 
               dealerHand(std::vector<int>(DECK_SZ,0)),
               playerHand(std::vector<int>(DECK_SZ,0))
  {
    std::iota(deck.begin(), deck.end(), DECK_BEG); // fill deck array with 1..52
  }

  /* use synthesized destructor since no dynamic memory */
  ~Blackjack() = default;

  /*
   * Disable copy constructor
   */
  Blackjack(const Blackjack& other) = delete;

  /*
   * Disable copy assignment
   */
  Blackjack& operator=(const Blackjack& other) = delete;

  /*
   * Run the game
   * Parameter: None
   * Return: 0 - tie
   *         1 - player won
   *        -1 - dealer won
   *         2 - error
   */
  int run();
};

#endif