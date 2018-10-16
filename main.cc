/*
 * Driver of the executable
 * prompts the user and controls the Blackjack object
 */

#include <iostream>
#include <string>
#include <vector>

#include "Blackjack.h"

/* print the prompt */
bool prompt() {
  std::cout << "Options: \n"
            << "  s: Start the game\n"
            << "  q: Quit\n";
  return true;
}

/* driver of the executable */
int main() {
  // local variables
  std::string response;
  char ans;
  bool quit = false;
  Blackjack bj;

  // welcome prompt
  std::cout << "Welcome to simplified Blackjack in cli.\n";

  // keep prompting until user type q
  while (!quit && prompt() && std::cin >> response){ 
    // keep reading until user type something
    if(!response.length()) continue; 
    ans = response[0];
    switch (ans) {
      case 's':
        bj.run();
        break;
      case 'q':
        quit = true;
        break;
      default:
        continue;
        break;
    }
  }

  std::cout << "Bye" << std::endl;
  return 0;
}