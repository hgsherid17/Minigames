//
// Created by Hannah Sheridan on 1/29/23.
//

#ifndef M1OEP_HGSHERID_WHEELOFFORTUNE_H
#define M1OEP_HGSHERID_WHEELOFFORTUNE_H

#include <string>
#include <vector>
#include <functional>
#include <random>
#include <ostream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include "Player.h"
#include "Wheel.h"

using namespace std;
/**
 * The Wheel of Fortune class represents functions of the wheel of fortune game.
 * It holds three objects from the Player and Wheel classes
 * It has the following fields:
 * phrase: the current puzzle to be guessed by the user
 * category: the topic of the given puzzle
 * letterGuessed: a vector to hold each letter the user has guessed
 * phrases: a vector to hold all possible phrases
 * categories: a vector to hold all possible categories
 * lastGuessed: holds the last letter to be guessed by the user
 * wheel: an object of the "Wheel" class to represent the wheel and its prizes
 * players: a vector holding two "Player" objects
 * currentPlayer: the index of the player who is currently guessing letters
 * vowelsGuessed: the number of vowels guessed by both players
 * vowels: a constant vector to hold vowels
 */
class WheelOfFortune {
private:
    string phrase, category;
    vector<char> lettersGuessed;
    vector<string> categories, phrases;
    char lastGuessed;
    Wheel wheel;
    vector<Player> players;
    int currentPlayer, vowelsGuessed;
    const vector<char> vowels = {'A', 'E', 'I', 'O', 'U'};
public:
    /**
     * Default constructor initializes fields
     */
    WheelOfFortune();

    // Getters
    string getPhrase();
    string getCategory();
    vector<string> getCategories();
    vector<string> getPhrases();
    char getLastGuessed();
    vector<char> getLettersGuessed();
    vector<Player> getPlayers();
    Player getCurrentPlayer();

    // Setters
    void setPhrase (string p);
    void setCategory(string c);
    void setPlayers(Player player1, Player player2);
    void setCurrentPlayer(int index);
    void setCurrentPlayerBalance(int bal);

    /**
     * adds given letter to the lettersGuessed vector field
     * @param letter
     */
    void addGuessed(char letter);

    /**
     * Table of options
     * @param outs
     */
    void printGameOptions(ostream& outs);

    /**
     * getOption() prompts user to choose a game option and validates their choice.
     * The function returns the option once it is validated.
     * @param outs
     * @param ins
     * @return option
     */
    char getOption(ostream& outs, istream& ins);

    /**
    * Prints the options that are offered between rounds
    * @param outs
    */
    void printRoundOptions(ostream& outs);

    /**
     * activePlayer() checks if the player would like to continue a new round by prompting
     * the user to spin the wheel or exit the game and validates their choice.
     * If the user chooses to spin, the function returns true.
     * If the user chooses to exit, the function returns false.
     * @param outs
     * @param ins
     * @return boolean value true or false
     */
    bool activePlayer(ostream& outs, istream& ins);

    /**
     * readFile() reads through a given file and passes values to vectors
     * representing phrases and categories. The function returns true
     * if the file is successfully opened and read.
     * @param filename
     * @return boolean value
     */
    bool readFile(string filename);

    /**
     * setRandom() sets the phrase and category variables to a random
     * value from their respective vectors.
     *
     * @param categories
     * @param phrases
     */
    void setRandom();

    /**
     * guessConsonant() prompts a user to guess a consonant and validates their response.
     * If validated, the consonant will be searched for in the phrase. The current
     * player's balance is updated according to the amount of consonants guessed.
     * The function will return the amount of that specific consonant found in the phrase.
     * @param outs
     * @param ins
     * @return guessed // The number of consonants correctly guessed
     */
    int guessConsonant(ostream& outs, istream& ins);

    /**
     * guessVowel() prompts a user to guess a vowel and validates their response.
     * If validated, the vowel will be searched for in the phrase. The current player's
     * balance will be decremented by $250. The function will
     * return the amount of that specific vowel found in the phrase.
     * @param outs
     * @param ins
     * @return guessed // The number of correctly guessed vowels
     */
    int guessVowel(ostream& outs, istream& ins);


    /**
     * printPhrase() prints a formatted version of the given phrase. The function will only
     * print the letters that the user has correctly guessed. If a letter has not yet been
     * guessed, the function will print an underscore. Punctuation is printed normally.
     * @param outs
     */
    void printPhrase(ostream& outs);

    /**
     * Prints each letter in the alphabet except for those correctly guessed
     * by the players.
     * @param outs
     */
    void printLettersGuessed(ostream& outs);

    /**
     * solvePuzzle takes in a string and compares it with the current phrase.
     * If the string matches the phrase, the function returns true. Otherwise,
     * the function returns false.
     * @param guess
     * @return boolean value
     */
    bool solvePuzzle(string guess);

    /**
     * This function returns true if the user has guessed every letter in the phrase.
     * If every letter in the phrase is not in the lettersGuessed vector, the
     * function returns false
     * @return boolean value
     */
    bool guessedPhrase();

    /**
     * playAgain() asks the user if they wish to play again and validates the input.
     * If the user chooses to play again, the function returns true.
     * @param outs
     * @param ins
     * @return boolean value
     */
    bool playAgain(ostream& outs, istream& ins);

    /**
     * switchPlayers() switches the current player and spins the wheel to set a new prize value
     */
    void switchPlayers();

    /**
     * This function prints a formatted string displaying the balance of the current player
     * @param outs
     */
    void printCurrentPlayerBalance(ostream& outs);

    /**
     * This function prints each player's balance and number of wins
     * @param outs
     */
    void printFinalStats(ostream& outs);

    /**
     * setPlayerNames() takes in two strings representing the name of each player.
     * If the names are the same, the function does not update the player names and
     * returns false. If they are different, the function updates each player's name
     * and returns true.
     * @param player1
     * @param player2
     * @return boolean value
     */
    bool setPlayerNames(string player1, string player2);

    /**
     * This function prints the name of the current player
     * @param outs
     */
    void printCurrentPlayer(ostream& outs);

    /**
     * This function calls the wheel object's spin() method to get
     * a random prize value. The function will update the current player object's
     * prize field according to the value returned.
     * @return prize value
     */
    int spinWheel();



};



#endif //M1OEP_HGSHERID_WHEELOFFORTUNE_H
