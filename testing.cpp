//
// Created by Hannah Sheridan on 2/20/23.
//
#include "WheelOfFortune.h"
#include "Player.h"
#include "Wheel.h"
#include <vector>
bool testWheelOfFortune();
bool testPlayer();
bool testWheel();

int main() {
    if (testWheelOfFortune()) {
        cout << "PASSED ALL WHEEL OF FORTUNE TEST CASES" << endl;
    }
    if (testPlayer()) {
        cout << "PASSED ALL PLAYER TEST CASES" << endl;
    }
    if (testWheel()) {
        cout << "PASSED ALL WHEEL TEST CASES" << endl;
    }

    return 0;
}

bool testWheelOfFortune() {
    bool passed = true;
    WheelOfFortune test;

    // Test default constructor
    vector<Player> players;
    players = test.getPlayers();

    if (players.size() != 2) {
        cout << "FAILED default constructor test case 1" << endl;
        passed = false;
    }
    if (!(test.getCurrentPlayer() == players[0])) {
        cout << "FAILED default constructor test case 2" << endl;
        passed = false;
    }
    if (!(test.getCurrentPlayer() == "Player 1")) {
        cout << "FAILED default constructor test case 3" << endl;
        passed = false;
    }
    if (!(players[1] == "Player 2")) {
        cout << "FAILED default constructor test case 4" << endl;
        passed = false;
    }

    // Read file
    if (!(test.readFile("../WOFPhrases.csv"))) {
        cout << "FAILED readFile test case 1" << endl;
        passed = false;
    }

    test.readFile("../WOFTest.csv");
    if (test.getPhrases().size() != 3 || test.getCategories().size() != 3) {
        cout << "FAILED readFile test case 2" << endl;
        passed = false;
    }

    // Set random
    test.addGuessed('a');
    test.addGuessed('b');
    test.setRandom();
    if (test.getLettersGuessed().size() != 0) {
        cout << "FAILED setRandom test case 1" << endl;
        passed = false;
    }
    if (test.getCategory() != "Colors" && test.getCategory() != "Animals") {
        cout << "FAILED setRandom test case 2" << endl;
        passed = false;
    }
    if (test.getPhrase() != "Blue" && test.getPhrase() != "Dog" && test.getPhrase() != "Cat") {
        cout << "FAILED setRandom test case 3" << endl;
        passed = false;
    }

    // Solve puzzle
    test.setPhrase("Hello");
    test.setCategory("Thing");
    if (test.solvePuzzle("Bye")) {
        cout << "FAILED solvePuzzle test case 1" << endl;
        passed = false;
    }
    if (!(test.solvePuzzle("Hello"))) {
        cout << "FAILED solvePuzzle test case 2" << endl;
        passed = false;
    }
    for (char letter : "Hello") {
        if (find(test.getLettersGuessed().begin(), test.getLettersGuessed().end(), letter) == test.getLettersGuessed().end()) {
            passed = false;
            cout << "FAILED solvePuzzle test case 3" << endl;
        }
    }

    // Guessed phrase
    test.setPhrase("Bye");
    test.addGuessed('b');
    test.addGuessed('t');
    if (test.guessedPhrase()) {
        cout << "FAILED guessedPhrase test case 1" << endl;
        passed = false;
    }

    test.addGuessed('e');
    test.addGuessed('y');
    if (!(test.guessedPhrase())) {
        cout << "FAILED guessedPhrase test case 2" << endl;
        passed = false;
    }

    // Switch players
    test.switchPlayers();
    if (test.getCurrentPlayer() == players[0]) {
        cout << "FAILED switchPlayers test case 1" << endl;
        passed = false;
    }

    if (!(test.getCurrentPlayer() == players[1])) {
        cout << "FAILED switchPlayers test case 2" << endl;
        passed = false;
    }
    test.switchPlayers();
    if (test.getCurrentPlayer() == players[1]) {
        cout << "FAILED switchPlayers test case 3" << endl;
        passed = false;
    }

    // Set player names
    if (test.setPlayerNames("HAnNah", "haNNaH")) {
        cout << "FAILED setPlayerNames test case 1" << endl;
        passed = false;
    }
    if (!(test.setPlayerNames("Hannah", "Sheridan"))) {
        cout << "FAILED setPlayerNames test case 2" << endl;
        passed = false;
    }

    test.setPlayerNames("", "Hannah");
    players = test.getPlayers();
    if (!(players[0] == "Player 1")) {
        cout << "FAILED setPlayerNames test case 3" << endl;
    }

    test.setPlayerNames("Hannah", "");
    players = test.getPlayers();
    if (!(players[1] == "Player 2")) {
        cout << "FAILED setPlayerNames test case 4" << endl;
        passed = false;
    }

    cout << "----- Testing Wheel Of Fortune print functions -----" << endl;
    test.printRoundOptions(cout);

    // Should print vowel
    test.setCurrentPlayerBalance(250);
    test.printGameOptions(cout);

    // Shouldn't print vowel
    test.setCurrentPlayerBalance(0);
    test.printGameOptions(cout);

    test.setPhrase("Hello World");
    test.setCategory("Puzzle");
    test.addGuessed('w');
    test.addGuessed('o');
    // Should only print letters guessed
    test.printPhrase(cout);

    test.setCurrentPlayerBalance(250);
    test.printCurrentPlayer(cout);
    test.printCurrentPlayerBalance(cout);
    cout << endl;
    test.switchPlayers();
    test.setCurrentPlayerBalance(500);
    test.printCurrentPlayer(cout);
    test.printCurrentPlayerBalance(cout);
    cout << endl;

    test.printFinalStats(cout);

    cout << "----- End testing Wheel Of Fortune print functions -----" << endl;

    return passed;
}

bool testPlayer() {
    bool passed = true;

    // Default constructor
    Player player1;
    if (player1.getName() != "Current Player") {
        cout << "FAILED Player default constructor test case" << endl;
        passed = false;
    }
    if (player1.getBalance() != 0 || player1.getNumWins() != 0) {
        cout << "FAILED Player default constructor test case 2" << endl;
        passed = false;
    }
    if (player1.getPrize() != 200) {
        cout << "FAILED Player default constructor test case 3" << endl;
        passed = false;
    }

    // Constructor with name parameter
    Player player2("Hannah");
    if (player2.getName() != "Hannah") {
        cout << "FAILED Player constructor test case 1" << endl;
        passed = false;
    }
    if (player2.getBalance() != 0 || player2.getNumWins() != 0) {
        cout << "FAILED Player constructor test case 2" << endl;
        passed = false;
    }
    if (player2.getPrize() != 200) {
        cout << "FAILED Player constructor test case 3" << endl;
        passed = false;
    }

    // Guess consonant
    player1.setPrize(100);

    player1.guessConsonant(3);
    if (player1.getBalance() != 300) {
        cout << "FAILED guessConsonant test case 1" << endl;
        passed = false;
    }

    player1.guessConsonant(1);
    if (player1.getBalance() != 400) {
        cout << "FAILED guessConsonant test case 2" << endl;
        passed = false;
    }

    // Sufficient funds 1
    if (!(player1.sufficientFunds())) {
        cout << "FAILED sufficientFunds test case 1" << endl;
        passed = false;
    }

    // Buy vowel
    player1.buyVowel();
    if (player1.getBalance() != 150) {
        cout << "FAILED buyVowel test case 1" << endl;
        passed = false;
    }
    if (player1.buyVowel()) {
        cout << "FAILED cannot buy vowel test case" << endl;
        passed = false;
    }

    // Bankrupt
    player1.bankrupt();
    if (player1.getBalance() != 0) {
        cout << "FAILED bankrupt test case" << endl;
        passed = false;
    }

    // Sufficient funds 2
    if (player1.sufficientFunds()) {
        cout << "FAILED sufficientFunds test case 2" << endl;
        passed = false;
    }

    // Winner
    player1.winner();
    player1.winner();
    player2.winner();
    if (player1.getNumWins() != 2) {
        cout << "FAILED winner test case 1" << endl;
        passed = false;
    }
    if (player2.getNumWins() != 1) {
        cout << "FAILED winner test case 2" << endl;
        passed = false;
    }

    // Overloaded == operator
    player1.setName("jane doe");
    player2.setName("Jane Doe");
    if (!(player1 == player2)) {
        cout << "FAILED overloaded == operator test case 1" << endl;
        passed = false;
    }
    player2.setName("John doe");
    if (player1 == player2) {
        cout << "FAILED overloaded == operator test case 2" << endl;
        passed = false;
    }
    if (player2 == "Player 2") {
        cout << "FAILED overloaded == operator test case 3" << endl;
        passed = false;
    }
    if (!(player2 == "John Doe")) {
        cout << "FAILED overloaded == operator test case 4" << endl;
        passed = false;
    }

    // Overloaded << operator
    cout << "----- Testing Player overloaded print operator -----" << endl;
    cout << "Player 1: " << player1 << endl << "Player 2: " << player2 << endl;
    cout << "----- End testing Player overloaded print operator -----" << endl;

    return passed;
}

bool testWheel() {
    bool passed = true;

    Wheel wheel;

    // Default constructor
    if (wheel.getCurrentWedge() != 200) {
        cout << "FAILED Wheel default constructor test case 1" << endl;
        passed = false;
    }
    if (wheel.getWheel().size() == 0) {
        cout << "FAILED Wheel default constructor test case 2" << endl;
        passed = false;
    }

    // Constructor
    vector<int> testWheel = {300, 400, 500, 600};
    Wheel wheel2(testWheel);
    if (wheel2.getWheel().size() != 4) {
        cout << "FAILED Wheel constructor test case 1" << endl;
        passed = false;
    }
    if (wheel2.getCurrentWedge() != 300) {
        cout << "FAILED Wheel constructor test case 2" << endl;
        passed = false;
    }

    // Add wedge
    wheel2.addWedge(700);
    if (find(wheel2.getWheel().begin(), wheel2.getWheel().end(), 700) == wheel2.getWheel().end()) {
        cout << "FAILED addWedge test case 1" << endl;
        passed = false;
    }
    if (wheel2.getSize() != 5) {
        cout << "FAILED addWedge test case 2" << endl;
        passed = false;
    }
    if (wheel2.getCurrentWedge() != 700) {
        cout << "FAILED addWedge test case 3" << endl;
        passed = false;
    }

    // Remove wedge
    if (wheel2.removeWedge(800)) {
        cout << "FAILED cannot remove wedge test case" << endl;
        passed = false;
    }
    wheel2.removeWedge(300);
    if (find(wheel2.getWheel().begin(), wheel2.getWheel().end(), 300) == wheel2.getWheel().end()) {
        cout << "FAILED removeWedge test case 1" << endl;
        passed = false;
    }
    wheel2.removeWedge(400);
    if (wheel2.getSize() != 3) {
        cout << "FAILED removeWedge test case 2" << endl;
        passed = false;
    }

    // Fill wheel
    wheel2.fillWheel();
    if (wheel2.getSize() != 26) {
        cout << "FAILED fillWheel test case 1" << endl;
        passed = false;
    }
    if (wheel2.getCurrentWedge() != 200) {
        cout << "FAILED fillWheel test case 2" << endl;
        passed = false;
    }

    // Overloaded << operator
    cout << "----- Testing Wheel class overloaded print operator -----" << endl;
    cout << wheel2;
    cout << "----- End testing Wheel class overloaded print operator -----" << endl;

    return passed;
}