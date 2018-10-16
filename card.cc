/*
 * Source for card namespace
 * 
 * helper functions to tackle the number
 * representing the cards
 */ 

#include "card.h"

/* basic const for cards */
#define SUIT_NUM 4  // 4 suits  in a deck
#define SUIT_SZ  13 // 13 cards in a suit

/*
 * card number note:
 *   1-13 clubs
 *   14-26 hearts
 *   27-39 diamonds
 *   40-52 spades
 * Ace's score is 1 or 11
 */
#define CLUBS 0
#define HEARTS 1
#define DIAMONDS 2
#define SPADES 3

#define CARD_ACE 1
#define CARD_JACK 11
#define CARD_QUEEN 12
#define CARD_KING 13

#define FACE_SCORE 10 // face cards are 10

namespace card {
  /*
   * Return the information about a card based on the index
   * Parameter: c - the number representing card
   * Return: pair of 2 int
   *         first - suit
   *         second - value on the card
   */
  std::pair<int, int> toPair(int c) {
    return std::make_pair((c-1) / SUIT_SZ, ((c-1) % SUIT_SZ) + 1);
  }

  /*
   * Calculate the value of card using its index
   * Parameter: c - the number representing card
   * Return: int - the value of a card in the game
   * Note: does not take Ace into account
   */
  int toScore(int c) {
    return (((c-1) % SUIT_SZ) + 1) > FACE_SCORE ? FACE_SCORE : 
                                                  (((c-1) % SUIT_SZ) + 1);
  }

  /*
   * Translate the number representing card to human friendly name
   * Parameter: c - the number representing card
   * Return: string - a name of a card
   */
  std::string toString(int c) {
    auto pair = card::toPair(c);
    if(!pair.second) return "Empty card"; // no 0 as a card

    std::string name = std::string();
     
    // add the number
    switch (pair.second) {
      case CARD_ACE:
        name += "Ace";
        break;
      case CARD_JACK:
        name += "Jack";
        break;
      case CARD_QUEEN:
        name += "Queen";
        break;
      case CARD_KING:
        name += "King";
        break;
      default:
        name += std::to_string(pair.second);
        break;
    }
  
    name += " of ";
    
    // add the suit
    switch (pair.first) {
      case CLUBS:
        name += "clubs";
        break;
      case HEARTS:
        name += "hearts";
        break;
      case DIAMONDS:
        name += "diamonds";
        break;
      case SPADES:
        name += "spades";
        break;
      default:
        std::cerr << pair.first 
                  << " cannot be successfully parsed"
                  << std::endl;
        return "ERROR";
        break;
    }
  
    // add the score
    name += " (";
    name += std::to_string(card::toScore(c)); 
  
    // Ace
    if(pair.second == CARD_ACE) {
      name += " or 11";
    }

    name += ")";
   
    return name;
  }
}