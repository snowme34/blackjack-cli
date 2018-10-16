/*
 * Source for blackjack class
 * 
 * Responsible for the main functions of the game
 * 
 * This is a single-player version of the card game Blackjack
 * without betting
 */ 

#include "Blackjack.h"

/*
 * Calculate the score (closest to 21)
 * Parameter: isPlayer - true to calculate player's
 *                     - false to calculate dealer's
 * Return score of the person requested
 */
int Blackjack::getScore(bool isPlayer) const {
  unsigned int ace = (isPlayer) ? acePlayer : aceDealer;
  unsigned int score = (isPlayer) ? valPlayer : valDealer;

  // return the closest answer
  if(ace) {
    unsigned int aceNum = 1;
    // change the score of an Ace is same as increase
    // total score by 10 for this specific card
    while(aceNum++ <= ace && score + (ACE_SCORE-1) <= GOAL) {
      score += ACE_SCORE;
    }
  }
  return score;
}

/*
 * Reset the game
 * Parameter: None
 * Return: None
 */
void Blackjack::reset() {
  idx = idxDealer = idxPlayer = 0;
  valDealer = valPlayer = 0;
  aceDealer = acePlayer = 0;
  shuffle();
  std::fill(dealerHand.begin(),dealerHand.end(),0);
  std::fill(playerHand.begin(),playerHand.end(),0);
}

/*
 * Give a card to a person
 * Parameter: isPlayer - true if player
 *                       false if dealer
 * Return: true - success
 *         false - failure
 */
bool Blackjack::giveCard(bool isPlayer) {

  // set the reference
  unsigned int& idxPerson = (isPlayer) ? idxPlayer : idxDealer;
  unsigned int& idxOther = (isPlayer) ? idxDealer : idxPlayer;
  unsigned int& val = (isPlayer) ? valPlayer : valDealer;
  unsigned int& ace = (isPlayer) ? acePlayer : aceDealer;
  auto& hand = (isPlayer) ? playerHand : dealerHand;

  // range check
  if(idx+1 < DECK_SZ && idxPerson+1 < DECK_SZ-idxOther) {
    // remember the score and ace
    val += card::toScore(deck[idx]);
    if(deck[idx] == 1) ++ace;
    if(isPlayer) {
      std::cout << "Player received card: "
                << card::toString(deck[idx])
                << std::endl;
    }
    hand[idxPerson++] = deck[idx++];
    return true;
  }
  // card not enough
  return false;
}

/*
 * Give player and dealer 4 cards as beginning
 * Parameter: None
 * Return: 0 - continue the game
 *         1 - player has a natural
 *        -1 - delear has a natural
 *         2 - both have natural
 */
int Blackjack::deal() {

  printWelcome();

  for(int i = 0; i < INITIAL_CARDS; ++i) {
    if(i&1) { // player receives odd index cards
      playerGetCard();
    } else { // dealer receives even index cards
      dealerGetCard();
    }
  }

  printPlayer();
  printDealer(0);

  // naturals
  int pScore = getScore(1), dScore = getScore(0);
  if(pScore == GOAL || dScore == GOAL) {
    return (pScore == GOAL && dScore == GOAL) ? 2 : (pScore == GOAL) ? 1 : -1;
  }

  return 0;
}

/*
 * Player stand
 * Player stops to receive card and it's turn for dealer
 * Parameter: None
 * Return: true - success
 *         false - failure
 */
bool Blackjack::stand() {
  printDealer(1);
  // due to the algorithm in getScore()
  // Ace is automatically regarded as 11
  // only when it reaches DEALER_STAND
  while(getScore(0) < DEALER_STAND) {
    if(!dealerGetCard()) return false;
    std::cout << "Dealer received card: "
              << card::toString(dealerHand[idxDealer-1])
              << std::endl;
  }
  return true;
}

/*
 * Check if the player wins or loses
 * Parameter: stand - if player stands
 * Return: 0 - the game should continue or tie
 *         1 - player wins
 *        -1 - player loses
 */
int Blackjack::check(bool stand) const {
  int pScore = getScore(1), dScore = getScore(0);

  // if player hits and reaches higher than 21
  // player must lose
  // player can only win without 21 after stand
  if(pScore > GOAL) {
    return -1;
  }

  // if player stands
  if(stand) {
    // check the resulting dealer score
    // note pScore cannot exceed 21 here
    if(dScore > GOAL) return 1;

    // now both smaller than or equal to 21
    // calculate the difference
    pScore = GOAL - pScore;
    dScore = GOAL - dScore;

    // smaller difference means winner
    return (pScore == dScore) ? 0 :
           (pScore < dScore) ? 1 : -1;
  }

  // if player not stands
  // player can only win with exactly 21
  // we do not check dealer after the first deal
  if(pScore == GOAL) {
    return 1;
  }

  return 0;
}


/*
 * print the welcome
 * Parameter: None
 * Return: None
 */
void Blackjack::printWelcome() const {
  std::cout << "\n===================\n"
            << "Welcome to a new game.\n"
            << "Now we deal first 4 cards"
            << std::endl;
}


/*
 * print the prompt
 * Parameter: None
 * Return: None
 */
void Blackjack::printPrompt() const {
  std::cout << "\nWaiting for player...\n"
            << "Options: Status(t), View Dealer's card(d), View Player's card(p), "
            << "Hit(h), Stand(s)\n"
            << std::endl;
}

/*
 * print the current gaming status
 * format: player score - dealer hand - card used - card remaining
 * Parameter: None
 * Return: None
 */
void Blackjack::printStatus() const {
  std::cout << "\n* Player's score: "
            << getScore(1)
            << "\n* Dealer's face-up card: "
            << card::toString(dealerHand[0])
            << "\n\nCard used: "
            << idx
            << ", Card remaining: "
            << DECK_SZ - idx
            << std::endl;
}

/*
 * print the cards in dealer's hand
 * Parameter: None
 * Return: None
 */
void Blackjack::printDealer(bool stand) const {
  if(!stand) {
    std::cout << "Cards of Dealer: "
              << card::toString(dealerHand[0])
              << " and a hidden card."
              << std::endl;
  } else {
    std::cout << "Cards of Dealer: ";
    for(unsigned int i = 0; i < idxDealer-1; ++i) {
      std::cout << card::toString(dealerHand[i])
                << ", ";
    }
    std::cout << card::toString(dealerHand[idxDealer-1])
              << std::endl;
  }
}

/*
 * print the cards in player's hand
 * Parameter: None
 * Return: None
 */
void Blackjack::printPlayer() const {
  std::cout << "Cards of Player: ";
  for(unsigned int i = 0; i < idxPlayer-1; ++i) {
    std::cout << card::toString(playerHand[i])
              << ", ";
  }
  std::cout << card::toString(playerHand[idxPlayer-1])
            << std::endl;
}

/*
 * print the result
 * Parameter: None
 * Return: None
 */
void Blackjack::printResult() const {
  std::cout << "\nGame ends\n"; 
  printPlayer();
  std::cout << "Final score of player: " << getScore(1) << "\n";
  printDealer(1);
  std::cout << "Final score of dealer: " << getScore(0) << "\n";

  switch(check(1)) {
    case 1:
      std::cout << "Congratulations! Player won!"
                << std::endl;
      break;
    case -1:
      std::cout << "Sorry. Dealer won."
                << std::endl;
      break;
    case 0:
      std::cout << "Nice try but we got a tie."
                << std::endl;
      break;
    default:
      break;
  }

  std::cout << "====================" << std::endl;
}

/*
 * Run the game
 * Parameter: None
 * Return: 0 - tie
 *         1 - player won
 *        -1 - dealer won
 *         2 - error
 */
int Blackjack::run() {
  reset();
  int result = deal();

  switch(result) {
    case 1:
      std::cout << "Congratulations!"
                << " Player has a natural (Ace and a 10-score card) and won this game."
                << "\n==================="
                << std::endl;
      return 1;
      break;
    case -1:
      std::cout << "Sorry. Dealer has a natural (Ace and a 10-score card) and won this game."
                << "\n==================="
                << std::endl;
      return -1;
      break;
    case 2:
      std::cout << "Both player and dealer have a natural, tie."
                << "\n==================="
                << std::endl;
      return 0;
      break;
    default:
      break;
  }

  printStatus();

  // local variables
  std::string response;
  bool stand = false;
  char ans;

  // keep prompting the player until player stands
  while(!check(stand) && idx < DECK_SZ && !stand) {
    printPrompt();

    std::cin >> response;
    if(!response.size()) continue;
    ans = response[0];

    switch (ans) {
      case 't':
        printStatus();
        break;
      case 'd':
        printDealer(stand);
        break;
      case 'p':
        printPlayer();
        break;
      case 'h':
        hit();
        printStatus();
        break;
      case 's':
        this->stand();
        stand = true;
        break;
      default:
        break;
    }

    // if player used up the cards - impossible in reality
    if(idx == DECK_SZ - 1) { 
      std::cout << "Run out of cards\n";
      return 0;
    }
  }

  printResult();

  return check(stand);
}