//
// Created by Hannah Sheridan on 2/21/23.
//

#ifndef M1OEP_HGSHERID_PLAYER_H
#define M1OEP_HGSHERID_PLAYER_H

#include <vector>
#include <string>
using namespace std;

/**
 * Player class represents someone who is playing the Wheel Of Fortune game.
 * It has the following fields:
 * balance: the amount of money amassed by the player
 * numWins: the amount of puzzles the player has correctly guessed
 * prize: the current prize to be added to the player's balance
 * name: the username or title of the player
 */
class Player {
private:
    int balance;
    int numWins;
    int prize;
    string name;

public:
    Player();
    Player(string name);

    // Getters
    int getBalance();
    int getNumWins();
    int getPrize();
    string getName() const;

    // Setters
    void setBalance(int bal);
    void setNumWins(int wins);
    void setPrize(int wedge);
    void setName(string playerName);

    /**
     * guessConsonant takes in number of correctly guessed consonants
     * and updates balance accordingly
     * @param numGuessed
     */
    void guessConsonant(int numGuessed);

    /**
     * buyVowels decrements the player's balance by $250
     */
    bool buyVowel();

    /**
     * bankrupt sets the player's balance to zero
     */
    void bankrupt();

    /**
     * winner increments the numWins variable by one
     */
    void winner();

    /**
     * sufficientFunds returns true if user has enough money to buy a vowel (>= $250)
     * @return boolean value
     */
    bool sufficientFunds();

    // Overloaded Operators
    friend bool operator == (const Player &lhs, const Player &rhs);
    friend bool operator == (const Player &lhs, const string &rhs);
    friend ostream& operator << (ostream& outs, Player rhs);

};


#endif //M1OEP_HGSHERID_PLAYER_H
