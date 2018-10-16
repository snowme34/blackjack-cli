/*
 * Header for card namespace
 * 
 * helper functions to tackle the number
 * representing the cards
 */ 

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <vector>

namespace card {
  /*
   * Return the information about a card based on the index
   * Parameter: c - the number representing card
   * Return: pair of 2 int
   *         first - suit
   *         second - value on the card
   */
  std::pair<int, int> toPair(int c);

  /*
   * Calculate the value of card using its index
   * Parameter: c - the number representing card
   * Return: int - the value of a card in the game
   * Note: does not take Ace into account
   */
  int toScore(int c);

  /*
   * Translate the number representing card to human friendly name
   * Parameter: c - the number representing card
   * Return: string - a name of a card
   */
  std::string toString(int c);
}

#endif