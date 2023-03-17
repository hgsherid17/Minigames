/*
 * Created by Hannah Sheridan
 * CS 120 Section B
 * Open-Ended Project
 *
 */
#include "WheelOfFortune.h"
#include <ostream>
#include <iostream>
#include <string>
using namespace std;

/*
 * Main uses the WheelOfFortune class to build a user interface for the Wheel of Fortune game.
 * */
 int main() {
     bool solved = false;
     bool playing, round;
     int consonants, vowels, prize;
     char option = 'C';
     string letter;
     string player1;
     string player2;

     // Create WOF object and get puzzle from file
     WheelOfFortune player;
     player.readFile("../WOFPhrases.csv");
     player.setRandom();

     // Welcome message
     cout << "Welcome to Wheel of Fortune!" << endl;

     // Get and set player names
     cout << "Please enter the name of Player 1: ";
     getline(cin, player1);
     cout << "Please enter the name of Player 2: ";
     getline(cin, player2);

     // Players cannot have the same name
     bool diff = player.setPlayerNames(player1, player2);
     while (!diff) {
         cout << "You may not use the same name as another player!" << endl << "Please enter a different name: ";
         getline(cin, player2);
         diff = player.setPlayerNames(player1, player2);
     }

     // Print game puzzle and start Player 1's turn
     player.printCurrentPlayer(cout);
     player.printPhrase(cout);

     cout << player.getPhrase() << endl;

     // Prompt user to spin wheel or exit
     playing = player.activePlayer(cout, cin);

     while(playing){
         player.printCurrentPlayer(cout);

         // Spin wheel
         cout << endl << "Spinning the wheel..." << endl;
         prize = player.spinWheel();

         // Switch players if player lands on bankrupt or lose a turn
         while (prize == -1 || prize == 0) {
             if (prize == -1) {
                 cout << "Sorry, " << player.getCurrentPlayer() << ", you lost a turn!" << endl;
                 player.switchPlayers();
             }
             else {
                 cout << "Sorry, " << player.getCurrentPlayer() << ", you've gone bankrupt!" << endl;
                 player.switchPlayers();
             }
             player.printCurrentPlayer(cout);
             cout << endl << "Spinning the wheel..." << endl;
             prize = player.spinWheel();
         }

         player.printPhrase(cout);
         cout << endl << "Prize: $" << prize << endl;
         player.printCurrentPlayerBalance(cout);

         // Prompt user to guess a consonant
         consonants = player.guessConsonant(cout, cin);
         player.printPhrase(cout);

         // Display output and update balance based on number of consonants guessed
         if (consonants > 1) {
             cout << "There are " << consonants << " " << player.getLastGuessed() << "'s!" << endl;
             //balance += (consonants * prize);
             player.printCurrentPlayerBalance(cout);
             round = true;
         }
         else if (consonants == 1) {
             cout << "There is " << consonants << " " << player.getLastGuessed() << "!" << endl;
             //balance += prize;
             player.printCurrentPlayerBalance(cout);
             round = true;
         }
         else {
             cout << "Sorry, there are no " << player.getLastGuessed() << "'s in this puzzle!" << endl;
            // cout << "Balance: $" << balance << endl;
             round = false;
         }

         if (player.guessedPhrase()) {
             player.printPhrase(cout);
             cout << "Congratulations, " << player.getCurrentPlayer() << ", you solved the puzzle!" << endl;
             solved = true;
             round = false;
             option = 'E';
         }
         // If user guesses a consonant correctly, allow them more game options
         while (round) {
             option = player.getOption(cout, cin);
             switch(option) {
                 // User chose to guess a consonant
                 case 'C': {
                     // Jump out of loop and spin the wheel again
                     round = false;
                     break;
                 }

                 // User chose to buy a vowel
                 case 'V': {
                     // Prompt user to guess a vowel
                     vowels = player.guessVowel(cout, cin);
                     player.printPhrase(cout);

                     if (vowels > 1) {
                         cout << "There are " << vowels << " " << player.getLastGuessed() << "'s!" << endl;
                     }
                     else if (vowels == 1) {
                         cout << "There is " << vowels << " " << player.getLastGuessed() << "!" << endl;
                     }
                     else {
                         cout << "Sorry, there are no " << player.getLastGuessed() << "'s in this puzzle!" << endl;
                         round = false;
                     }
                     player.printCurrentPlayerBalance(cout);
                     break;
                 }
                 // User chose to solve the puzzle
                 case 'P': {
                     string guess;
                     cout << "Solve the puzzle: ";
                     getline(cin, guess);
                     while (guess == "") {
                         cout << "No input. Please try to solve the puzzle: ";
                         cin.clear();
                         getline(cin, guess);
                     }

                     // Jump out of loop if user guesses correctly
                     if ((player.solvePuzzle(guess))) {
                         player.printPhrase(cout);
                         cout << "Congratulations, " << player.getCurrentPlayer() << ", you solved the puzzle!" << endl;
                         round = false;
                         solved = true;
                     }
                     // Start another round if user guesses wrong
                     else {
                         cout << "Sorry, you did not solve the puzzle. Your turn has ended." << endl;
                         round = false;
                         break;
                     }
                 }
                 // User chooses to exit game
                 case 'E' : {
                     // Quit program
                     round = false;
                     playing = false;
                     option = 'C';
                 }
             }
             // Worried. Will this mess up numWins ?
             if (player.guessedPhrase()) {
                 player.printPhrase(cout);
                 cout << "Congratulations, " << player.getCurrentPlayer() << ", you solved the puzzle!" << endl;
                 solved = true;
             }

         }
         // If the player has solved the puzzle
         if (solved){
             // Ask if they would like to play again
             option = 'C';
             playing = player.playAgain(cout, cin);

             // Get new phrase if user chooses to play again
             // Otherwise, leave program
             if (playing) {
                 solved = false;
                 player.setRandom();
                 player.setCurrentPlayer(0);
             }
             else {
                 round = false;
             }
         }

         // If user guesses incorrectly, start a new round
         if (option != 'C' || consonants == 0) {
             player.switchPlayers();
             player.printCurrentPlayer(cout);
             playing = player.activePlayer(cout, cin);
         }

     }
     // Goodbye message for end of game
     cout << "Thank you for playing! See you later :)" << endl;
     player.printFinalStats(cout);

     return 0;
 }




